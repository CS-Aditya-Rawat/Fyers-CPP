#pragma once
#include <ConfigEnums.h>
#include <cpprest/http_client.h>
#include <cpprest/http_headers.h>
#include <map>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class RESTClientObject {
 private:
  std::string URL;
  json Config;

 public:
  RESTClientObject() {}

  web::http::http_response request(
      const std::string& method, const std::string& url,
      const std::map<std::string, std::string>& query_params = {},
      const std::map<std::string, std::string>& headers = {},
      const json& body = {}) {

    const std::string& URL = ConfigEnums::getUrl(url);
    std::cout << URL << "\n";
    web::http::client::http_client client(URL);
    web::http::http_request request;

    if (method == "GET") {
      request.set_method(web::http::methods::GET);
    } else if (method == "POST") {
      request.set_method(web::http::methods::POST);
    }

    // set headers
    for (const auto& header : headers) {
      request.headers().add(header.first, header.second);
    }

    // Set query Parameters
    web::uri_builder builder;
    for (const auto& param : query_params) {
      builder.append_query(param.first, param.second);
    }
    request.set_request_uri(builder.to_uri());

    if (!body.is_null()) {
      request.headers().set_content_type(U("application/json"));
      request.set_body(body.dump());
    }
    return client.request(request).get();
  }
};
