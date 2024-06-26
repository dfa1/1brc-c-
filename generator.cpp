#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

constexpr size_t lines = 1'000'000'000;

const std::vector<std::string> cities{
    "Abha",
    "Abidjan",
    "Abéché",
    "Accra",
    "Addis Ababa",
    "Adelaide",
    "Aden",
    "Ahvaz",
    "Albuquerque",
    "Alexandra",
    "Alexandria",
    "Algiers",
    "Alice Springs",
    "Almaty",
    "Amsterdam",
    "Anadyr",
    "Anchorage",
    "Andorra la Vella",
    "Ankara",
    "Antananarivo",
    "Antsiranana",
    "Arkhangelsk",
    "Ashgabat",
    "Asmara",
    "Assab",
    "Astana",
    "Athens",
    "Atlanta",
    "Auckland",
    "Austin",
    "Baghdad",
    "Baguio",
    "Baku",
    "Baltimore",
    "Bamako",
    "Bangkok",
    "Bangui",
    "Banjul",
    "Barcelona",
    "Bata",
    "Batumi",
    "Beijing",
    "Beirut",
    "Belgrade",
    "Belize City",
    "Benghazi",
    "Bergen",
    "Berlin",
    "Bilbao",
    "Birao",
    "Bishkek",
    "Bissau",
    "Blantyre",
    "Bloemfontein",
    "Boise",
    "Bordeaux",
    "Bosaso",
    "Boston",
    "Bouaké",
    "Bratislava",
    "Brazzaville",
    "Bridgetown",
    "Brisbane",
    "Brussels",
    "Bucharest",
    "Budapest",
    "Bujumbura",
    "Bulawayo",
    "Burnie",
    "Busan",
    "Cabo San Lucas",
    "Cairns",
    "Cairo",
    "Calgary",
    "Canberra",
    "Cape Town",
    "Changsha",
    "Charlotte",
    "Chiang Mai",
    "Chicago",
    "Chihuahua",
    "Chișinău",
    "Chittagong",
    "Chongqing",
    "Christchurch",
    "City of San Marino",
    "Colombo",
    "Columbus",
    "Conakry",
    "Copenhagen",
    "Cotonou",
    "Cracow",
    "Da Lat",
    "Da Nang",
    "Dakar",
    "Dallas",
    "Damascus",
    "Dampier",
    "Dar es Salaam",
    "Darwin",
    "Denpasar",
    "Denver",
    "Detroit",
    "Dhaka",
    "Dikson",
    "Dili",
    "Djibouti",
    "Dodoma",
    "Dolisie",
    "Douala",
    "Dubai",
    "Dublin",
    "Dunedin",
    "Durban",
    "Dushanbe",
    "Edinburgh",
    "Edmonton",
    "El Paso",
    "Entebbe",
    "Erbil",
    "Erzurum",
    "Fairbanks",
    "Fianarantsoa",
    "Flores Petén",
    "Frankfurt",
    "Fresno",
    "Fukuoka",
    "Gabès",
    "Gaborone",
    "Gagnoa",
    "Gangtok",
    "Garissa",
    "Garoua",
    "George Town",
    "Ghanzi",
    "Gjoa Haven",
    "Guadalajara",
    "Guangzhou",
    "Guatemala City",
    "Halifax",
    "Hamburg",
    "Hamilton",
    "Hanga Roa",
    "Hanoi",
    "Harare",
    "Harbin",
    "Hargeisa",
    "Hat Yai",
    "Havana",
    "Helsinki",
    "Heraklion",
    "Hiroshima",
    "Ho Chi Minh City",
    "Hobart",
    "Hong Kong",
    "Honiara",
    "Honolulu",
    "Houston",
    "Ifrane",
    "Indianapolis",
    "Iqaluit",
    "Irkutsk",
    "Istanbul",
    "İzmir",
    "Jacksonville",
    "Jakarta",
    "Jayapura",
    "Jerusalem",
    "Johannesburg",
    "Jos",
    "Juba",
    "Kabul",
    "Kampala",
    "Kandi",
    "Kankan",
    "Kano",
    "Kansas City",
    "Karachi",
    "Karonga",
    "Kathmandu",
    "Khartoum",
    "Kingston",
    "Kinshasa",
    "Kolkata",
    "Kuala Lumpur",
    "Kumasi",
    "Kunming",
    "Kuopio",
    "Kuwait City",
    "Kyiv",
    "Kyoto",
    "La Ceiba",
    "La Paz",
    "Lagos",
    "Lahore",
    "Lake Havasu City",
    "Lake Tekapo",
    "Las Palmas de Gran Canaria",
    "Las Vegas",
    "Launceston",
    "Lhasa",
    "Libreville",
    "Lisbon",
    "Livingstone",
    "Ljubljana",
    "Lodwar",
    "Lomé",
    "London",
    "Los Angeles",
    "Louisville",
    "Luanda",
    "Lubumbashi",
    "Lusaka",
    "Luxembourg City",
    "Lviv",
    "Lyon",
    "Madrid",
    "Mahajanga",
    "Makassar",
    "Makurdi",
    "Malabo",
    "Malé",
    "Managua",
    "Manama",
    "Mandalay",
    "Mango",
    "Manila",
    "Maputo",
    "Marrakesh",
    "Marseille",
    "Maun",
    "Medan",
    "Mek'ele",
    "Melbourne",
    "Memphis",
    "Mexicali",
    "Mexico City",
    "Miami",
    "Milan",
    "Milwaukee",
    "Minneapolis",
    "Minsk",
    "Mogadishu",
    "Mombasa",
    "Monaco",
    "Moncton",
    "Monterrey",
    "Montreal",
    "Moscow",
    "Mumbai",
    "Murmansk",
    "Muscat",
    "Mzuzu",
    "N'Djamena",
    "Naha",
    "Nairobi",
    "Nakhon Ratchasima",
    "Napier",
    "Napoli",
    "Nashville",
    "Nassau",
    "Ndola",
    "New Delhi",
    "New Orleans",
    "New York City",
    "Ngaoundéré",
    "Niamey",
    "Nicosia",
    "Niigata",
    "Nouadhibou",
    "Nouakchott",
    "Novosibirsk",
    "Nuuk",
    "Odesa",
    "Odienné",
    "Oklahoma City",
    "Omaha",
    "Oranjestad",
    "Oslo",
    "Ottawa",
    "Ouagadougou",
    "Ouahigouya",
    "Ouarzazate",
    "Oulu",
    "Palembang",
    "Palermo",
    "Palm Springs",
    "Palmerston North",
    "Panama City",
    "Parakou",
    "Paris",
    "Perth",
    "Petropavlovsk-Kamchatsky",
    "Philadelphia",
    "Phnom Penh",
    "Phoenix",
    "Pittsburgh",
    "Podgorica",
    "Pointe-Noire",
    "Pontianak",
    "Port Moresby",
    "Port Sudan",
    "Port Vila",
    "Port-Gentil",
    "Portland OR",
    "Porto",
    "Prague",
    "Praia",
    "Pretoria",
    "Pyongyang",
    "Rabat",
    "Rangpur",
    "Reggane",
    "Reykjavík",
    "Riga",
    "Riyadh",
    "Rome",
    "Roseau",
    "Rostov-on-Don",
    "Sacramento",
    "Saint Petersburg",
    "Saint-Pierre",
    "Salt Lake City",
    "San Antonio",
    "San Diego",
    "San Francisco",
    "San Jose",
    "San José",
    "San Juan",
    "San Salvador",
    "Sana'a",
    "Santo Domingo",
    "Sapporo",
    "Sarajevo",
    "Saskatoon",
    "Seattle",
    "Ségou",
    "Seoul",
    "Seville",
    "Shanghai",
    "Singapore",
    "Skopje",
    "Sochi",
    "Sofia",
    "Sokoto",
    "Split",
    "St. John's",
    "St. Louis",
    "Stockholm",
    "Surabaya",
    "Suva",
    "Suwałki",
    "Sydney",
    "Tabora",
    "Tabriz",
    "Taipei",
    "Tallinn",
    "Tamale",
    "Tamanrasset",
    "Tampa",
    "Tashkent",
    "Tauranga",
    "Tbilisi",
    "Tegucigalpa",
    "Tehran",
    "Tel Aviv",
    "Thessaloniki",
    "Thiès",
    "Tijuana",
    "Timbuktu",
    "Tirana",
    "Toamasina",
    "Tokyo",
    "Toliara",
    "Toluca",
    "Toronto",
    "Tripoli",
    "Tromsø",
    "Tucson",
    "Tunis",
    "Ulaanbaatar",
    "Upington",
    "Ürümqi",
    "Vaduz",
    "Valencia",
    "Valletta",
    "Vancouver",
    "Veracruz",
    "Vienna",
    "Vientiane",
    "Villahermosa",
    "Vilnius",
    "Virginia Beach",
    "Vladivostok",
    "Warsaw",
    "WashingtonD.C.",
    "Wau",
    "Wellington",
    "Whitehorse",
    "Wichita",
    "Willemstad",
    "Winnipeg",
    "Wrocław",
    "Xi'an",
    "Yakutsk",
    "Yangon",
    "Yaoundé",
    "Yellowknife",
    "Yerevan",
    "Yinchuan",
    "Zagreb",
    "Zanzibar City",
    "Zürich",
};

int main() {
  std::ios::sync_with_stdio(false);

  // great presentation from
  // https://learn.microsoft.com/en-us/shows/goingnative-2013/rand-considered-harmful
  std::mt19937 mt{42};  // make this completely reproducible in another machine
  std::uniform_int_distribution<> random_city{
      0, static_cast<int>(cities.size() - 1)};  // TODO: use std::sample
  std::normal_distribution<> random_temp{0, 40};
  std::ofstream outfile("measurements.txt");

  std::cout << "creating " << lines << " lines ... ☕ time" << std::endl;

  for (size_t i = 0; i < lines; i++) {
    outfile << cities[random_city(mt)] << ";"
            << std::roundf(random_temp(mt) * 10) / 10 << "\n";
  }
}
