#pragma once
#include "Markets.h"
#include "Request.h"
#include "User.h"
#include <vector>

class Fyers {
 private:
  User Profile;
  MarketsApi MarketData;

 protected:
  const std::string& ACCESS_TOKEN;
  // const std::string& PIN;
  const std::string& CLIENT_ID;
  // RESTClientObject rest_client;
  std::map<std::string, std::string> header_params = {
      {"Authorization", CLIENT_ID + ":" + ACCESS_TOKEN}};

 public:
  Fyers(const std::string& ENV_ACCESS_TOKEN, const std::string& PIN,
        const std::string& CLIENT_ID)
      : Profile(header_params),
        MarketData(header_params),
        ACCESS_TOKEN(ENV_ACCESS_TOKEN),
        CLIENT_ID(CLIENT_ID) {}

  json getProfile() { return Profile.profileLink(); }

  json getFunds() { return Profile.fundLink(); }

  json getSymbol(const std::vector<std::string>& symbols) {
    return MarketData.symbol(symbols);
  }
};
