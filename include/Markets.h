#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include "Request.h"
#include "User.h"

using json = nlohmann::json;

class MarketsApi {
 private:
  const std::map<std::string, std::string>& header_params;
  RESTClientObject rest_client;

 public:
  MarketsApi(const std::map<std::string, std::string>& header_params)
      : header_params(header_params) {}

  json symbol(const std::vector<std::string>& symbols) {
    if (symbols.size() > 50) {
      return json{
          {"data",
           {{"Code", "404"},
            {"Message",
             "More than 50 symbols are not allowed in singl Request."}}}};
    }
    std::ostringstream oss;
    std::copy(symbols.begin(), symbols.end(),
              std::ostream_iterator<std::string>(oss, ","));
    std::string symbol = oss.str();
    symbol = symbol.substr(0, symbol.size() - 1);

    std::map<std::string, std::string> query_params = {{"symbols", symbol}};
    web::http::http_response response = rest_client.request(
        "GET", "QUOTE_URL", query_params, header_params, {});
    std::cout << response.to_string() << "\n";
    if (static_cast<int>(response.status_code()) == 200) {
      try {
        json res = json::parse(response.extract_json().get().serialize());
        return res;
      } catch (json::parse_error& e) {
        return json{{"data",
                     {{"Code", static_cast<int>(response.status_code())},
                      {"Message", "Error in Parsing the Response."}}}};
      }
    } else {
      return json{{"data",
                   {{"Code", static_cast<int>(response.status_code())},
                    {"Message", "Error occurred to get Fund Details."}}}};
    }
  }

  // json historical_data(const std::string& symbol, const std::string& resolution,
  //                      const std::string& date_format,
  //                      const std::string& range_from,
  //                      const std::string& range_to,
  //                      const std::string& cnt_flag) {
  //   const std::map<std::string, std::string> query_params =
  //   { {"symbols", symbol} } web::http::http_response response =
  //       rest_client.request("GET", "HISTORY", query_params, header_params, {});
  // }
};
