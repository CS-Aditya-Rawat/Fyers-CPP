#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include "Request.h"

using json = nlohmann::json;

class User {
 private:
  const std::map<std::string, std::string>& header_params;
  RESTClientObject rest_client;

 public:
  User(const std::map<std::string, std::string>& authorization_header)
      : header_params(authorization_header) {}

  json profileLink() {
    web::http::http_response response =
        rest_client.request("GET", "PROFILE_URL", {}, header_params, {});
    if (static_cast<int>(response.status_code()) == 200) {
      try {
        json res = json::parse(response.extract_json().get().serialize());
        return res["data"];
      } catch (json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return json{{"data",
                     {{"Code", static_cast<int>(response.status_code())},
                      {"Message", "Error in Parsing the Response"}}}};
      }
    } else {
      return json{{"data",
                   {{"Code", static_cast<int>(response.status_code())},
                    {"Message", "Error occurred getting Profile data."}}}};
    }
  }

  json fundLink() {
    web::http::http_response response =
        rest_client.request("GET", "FUND_URL", {}, header_params, {});
    if (static_cast<int>(response.status_code()) == 200) {
      try {

        json res = json::parse(response.extract_json().get().serialize());
        return res;
      } catch (json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return json{{"data",
                     {{"Code", static_cast<int>(response.status_code())},
                      {"Message", "Error in Parsing the Response"}}}};
      }
    } else {

      return json{{"data",
                   {{"Code", static_cast<int>(response.status_code())},
                    {"Message", "Error occurred to get Fund Details."}}}};
    }
  }
};
