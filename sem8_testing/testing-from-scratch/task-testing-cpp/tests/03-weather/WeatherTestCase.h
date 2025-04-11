
#pragma once

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <cpr/response.h>

#include "WeatherMock.h"

// class WeatherTestCase : public ::testing::Test {
// };

// cpr library (wrapper over libcurl):
// https://github.com/libcpr/cpr

class WeatherTestCase : public ::testing::Test { // NOLINT
protected:
  WeatherMock weather_mock_;
  WeatherMock2 weather_mock2_;

  inline static const cpr::Url kBaseUrl =
      cpr::Url{"http://dataservice.accuweather.com/currentconditions/v1/"};
  inline static const cpr::Url kForecastUrl =
      cpr::Url{"http://dataservice.accuweather.com/forecasts/v1/daily/5day/"};
  inline static const cpr::Url kLocationUrl =
      cpr::Url{"http://dataservice.accuweather.com/locations/v1/cities/search"};

  inline static const std::filesystem::path kFolder =
      std::filesystem::path(__FILE__).parent_path();
  inline static const std::filesystem::path kDataFolder = kFolder / "data";

  static std::string GetFileContent(const std::string &filename) {
    std::string res;
    std::ifstream file(kDataFolder / filename);

    std::stringstream buffer;
    buffer << file.rdbuf();
    res = buffer.str();

    return res;
  }

  static cpr::Response GetInvalidResp() {
    cpr::Response resp;
    resp.status_code = 404; // Not Found

    return resp;
  }

  static cpr::Response GetMoscowResp() {
    cpr::Response resp;
    resp.status_code = 200;
    resp.text = GetFileContent("moscow_get_response_for_city.json");

    return resp;
  }
  inline static std::string moscow_city = "Moscow";
  inline static cpr::Url moscow_url = kLocationUrl;
  inline static std::string moscow_key = "294021";
};


