// steam_api.cc
// Copyright (C) averysumner
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "steam_api.h"

#include "keys.h"

namespace score_process {
  
SteamAPI::SteamAPI() {
  client_ = new httplib::Client(base_url_.c_str());
}

SteamAPI::~SteamAPI() {
  delete client_;
}

nlohmann::json SteamAPI::Request(std::string url, std::map<std::string, std::string> arguments) {
  url += "?key=" + std::string(STEAM_API_KEY); // add key argument
  for (std::pair<std::string, std::string> argument : arguments) {
    url += "&" + argument.first + "=" + argument.second;
  }

  if (auto response = client_->Get(url.c_str())) {
    if (response->status == 200) {
      return nlohmann::json::parse(response->body);
    }
  }

  return nlohmann::json();
}

nlohmann::json SteamAPI::GetUsers(std::vector<std::string> ids) {
  std::string ids_string = "";
  for (std::string id : ids) {
    ids_string += id + ",";
  }

  std::map<std::string, std::string> arguments;
  arguments.insert({"steamids", ids_string});

  return Request("/ISteamUser/GetPlayerSummaries/v0002/", arguments);
}

} // namespace score_process