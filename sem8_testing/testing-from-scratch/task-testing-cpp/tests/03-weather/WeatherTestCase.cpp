//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"

#include <json.hpp>

#include "WeatherMock.h"

using ::testing::Return;

////////////////////////////////////////////////////////////////////////////////

TEST_F(WeatherTestCase, GetResponseForCityNotFound) {
  auto url = cpr::Url(kBaseUrl + "invalid_url");
  cpr::Response resp = GetInvalidResp();

  EXPECT_CALL(weather_mock_, Get(moscow_city, url))
      .Times(1)
      .WillOnce(Return(resp));

  EXPECT_THROW(weather_mock_.GetResponseForCity(moscow_city, url),
               std::invalid_argument);
}

TEST_F(WeatherTestCase, GetResponseForCityMoscow) {
  cpr::Response resp = GetMoscowResp();

  EXPECT_CALL(weather_mock_, Get(moscow_city, moscow_url))
      .Times(1)
      .WillOnce(Return(resp))
      // .WillRepeatedly(Return(resp)) // All calls to function will return resp
  ;

  auto expected = json::parse(resp.text);
  auto actual = weather_mock_.GetResponseForCity(moscow_city, moscow_url);

  EXPECT_EQ(actual, expected);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(WeatherTestCase, GetDifferenceString) {}

TEST_F(WeatherTestCase, GetDifferenceStringWarmer) {
    EXPECT_CALL(weather_mock2_, GetTemperature(testing::_))
        .Times(2)
        .WillOnce(testing::Return(15))
        .WillOnce(testing::Return(10));

    ASSERT_EQ(weather_mock2_.GetDifferenceString("London", "Moscow"), "Weather in London is warmer than in Moscow by 5 degrees");
}

TEST_F(WeatherTestCase, GetDifferenceStringColder) {
    EXPECT_CALL(weather_mock2_, GetTemperature(testing::_))
        .Times(2)
        .WillOnce(testing::Return(5))
        .WillOnce(testing::Return(10));

    ASSERT_EQ(weather_mock2_.GetDifferenceString("London", "Moscow"), "Weather in London is colder than in Moscow by 5 degrees");
}
