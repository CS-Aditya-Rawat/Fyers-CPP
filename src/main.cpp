#include <iostream>
#include "Fyers.h"

int main() {
  const std::string& access = std::getenv("FYERS_ACCESS_TOKEN");
  const std::string& pin = std::getenv("FYERS_PIN");
  const std::string& client_id = std::getenv("FYERS_CLIENT_ID");
  nlohmann::json Config;

  // Check File Exists or Not
  // std::ifstream config_file("../include/config.json");
  // if (!config_file.is_open()) {
  //   std::cerr << "Error opening config file." << std::endl;
  //   return 1;
  // }
  // config_file >> Config;

  Fyers user = Fyers(access, pin, client_id);
  std::cout << user.getProfile() << "\n";
  std::cout << user.getFunds() << "\n";
  std::cout << user.getSymbol({"NSE:SBIN-EQ", "NSE:RELIANCE-EQ"}) << "\n";
  return 0;
}
