// For mmap and munmap, tested only on Debian/Linux
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <string_view>
#include <unordered_map>

#include "fast_float.h"

inline float parse_float(const char *start, const char *end) {
  float result;
  fast_float::from_chars(start, end, result, fast_float::chars_format::fixed);
  // TODO: check for errors if (result.ec != std::errc())
  return result;
}

class Temperature {
  float min_ = 9999;
  float max_ = -9999;
  float sum_ = 0;
  int count_ = 0;

 public:
  void merge(const float value) {
    min_ = std::min(value, min_);
    max_ = std::max(value, max_);
    sum_ += value;
    count_ += 1;
  }

  float min() const { return min_; }
  float max() const { return max_; }
  float avg() const { return sum_ / count_; }
};

// hide some specific UNIX code + RAII for open/close
class ScopedFile {
  int fd_;

 public:
  ScopedFile(const std::string_view file, int flags) {
    fd_ = ::open(file.data(), flags);
    if (fd_ == -1) {
      throw std::runtime_error("cannot open file");
    }
  }

  ~ScopedFile() noexcept { ::close(fd_); }

  ScopedFile(const ScopedFile &) = delete;
  ScopedFile &operator=(const ScopedFile &) = delete;

  int fd() const { return fd_; }
};

// hide some specific UNIX code + RAII for mmap/munmap
class MemorySegment {
  void *data_;
  size_t size_;

 public:
  MemorySegment(int fd) {
    struct stat statbuf;
    if (fstat(fd, &statbuf) == -1) {
      throw std::runtime_error("Error getting file size");
    }
    size_ = statbuf.st_size;

    data_ = mmap(nullptr, size_, PROT_READ, MAP_SHARED, fd, 0);
    if (data_ == MAP_FAILED) {
      throw std::runtime_error("Error mapping file");
    }
  }

  ~MemorySegment() noexcept { ::munmap(data_, size_); }

  MemorySegment(const MemorySegment &) = delete;
  MemorySegment &operator=(const MemorySegment &) = delete;

  const std::string_view view() const {
    return std::string_view(static_cast<const char *>(data_), size_);
  }
};

int main() {
  const ScopedFile file("measurements.txt", O_RDONLY);
  const MemorySegment segment(file.fd());

  std::unordered_map<std::string, Temperature> by_city;
  std::string_view current = segment.view();

  while (current.size() > 0) {
    const auto newline = current.find_first_of('\n');
    // Handle the case where the last line doesn't have a newline
    const auto size =
        newline != std::string_view::npos ? newline : current.size();
    // Extract the line (excluding newline character)
    const std::string_view line = current.substr(0, size);
    // Parse the city;temperature
    const auto semicolon = line.find_first_of(';');
    if (semicolon != std::string_view::npos) {
      const std::string city(line, 0, semicolon);
      const float value =
          parse_float(line.data() + semicolon + 1, line.data() + line.size());
      by_city[city].merge(value);
    } else {
      throw std::runtime_error("Cannot parse line");
    }
    // Move to the next line (skip newline)
    current = current.substr(newline + 1);
  }

  std::map<std::string, Temperature> sorted_by_city;
  for (const auto &[city, temperature] : by_city) {
    sorted_by_city[city] = temperature;
  }
  for (const auto &[city, temperature] : sorted_by_city) {
    std::cout << city << ";" << temperature.min() << ";" << temperature.max()
              << ";" << temperature.avg() << "\n";
  }
}
