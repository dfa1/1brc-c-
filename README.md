# 1️⃣🐝🏎️ The One Billion Row Challenge

- Challenge blog post: https://www.morling.dev/blog/one-billion-row-challenge/
- Challenge repository: https://github.com/gunnarmorling/1brc

The challenge: **compute simple floating-point math over 1 billion rows. As fast as possible, without dependencies.**

Implemented in C++ 20, with GCC 10 (that's why there is a copy of fast_float.h)

## Running the challenge

Tested on Debian Linux 11 with GCC 10:

```
make benchmark
```

Creating the file for the first time is really time consuming :-)
