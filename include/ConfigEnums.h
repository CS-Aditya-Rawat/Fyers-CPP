#pragma once
#include <string>
#include <unordered_map>

class ConfigEnums {
 public:
  static const std::unordered_map<std::string, std::string>& getUrlMap();
  static const std::string& getUrl(const std::string& key);
};

inline const std::unordered_map<std::string, std::string>&
ConfigEnums::getUrlMap() {
  static const std::unordered_map<std::string, std::string> urlMap = {
      {"FUND_URL", "https://api-t1.fyers.in/api/v3/funds"},
      {"PROFILE_URL", "https://api-t1.fyers.in/api/v3/profile"},
      {"HOLDING_URL", "https://api-t1.fyers.in/api/v3/holdings"},
      {"QUOTE_URL", "https://api-t1.fyers.in/data/quotes"},
  };
  return urlMap;
}

inline const std::string& ConfigEnums::getUrl(const std::string& key) {
  const auto& urlMap = getUrlMap();
  auto it = urlMap.find(key);
  return (it != urlMap.end())
             ? it->second
             : getUrlMap().at(
                   "UNKNOWN_URL");
}
