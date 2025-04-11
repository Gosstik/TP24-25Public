
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Weather.h"

namespace urls {

const cpr::Url kLocationUrl =
    cpr::Url{"http://dataservice.accuweather.com/locations/v1/cities/search"};
const std::filesystem::path kFolder =
    std::filesystem::path(__FILE__).parent_path();
const std::filesystem::path kDataFolder = kFolder / "data";

} // namespace urls

std::string GetApiKey() {
  std::string api_key;

  auto api_key_file_path = urls::kFolder / ".api_key";
  if (!std::filesystem::exists(api_key_file_path)) {
    std::cerr << ".api_key file does not exist, exiting\n";
    std::abort();
  }

  std::ifstream in(api_key_file_path.string());
  in >> api_key;
  return api_key;
}

void CallLocation(Weather &weather) {
  auto out_file = urls::kDataFolder / "moscow_get_response_for_city.json";
  std::ofstream out(out_file.string());

  auto resp = weather.GetResponseForCity("Moscow", urls::kLocationUrl);
  std::cout << resp;

  out << resp;
}

int main() {
  Weather weather;

  auto api_key = GetApiKey();
  weather.SetApiKey(api_key);

  CallLocation(weather);
}
