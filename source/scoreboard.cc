// scoreboard.cc
// Copyright (C) 2020 averysumner
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

#include "scoreboard.h"

#include <iostream>
#include <fstream>

#include "json/single_include/nlohmann/json.hpp"

namespace score_process {

Scoreboard::Scoreboard() {
  update_score_message_regex_ = std::regex(update_score_message_string_);
  kill_log_ui_regex_ = std::regex(kill_log_ui_string_);
  bomb_defuse_regex_ = std::regex(bomb_defuse_string_);

  std::string roaming_path = getenv("APPDATA"); // gets path to AppData\\Roaming

  std::ifstream log_file(roaming_path + log_sub_path_);

  if (log_file.is_open())
  {
    std::string line;
    while (true)
    {
      while (std::getline(log_file, line)) {
        ProcessLine(line);
      }
      if (!log_file.eof()) break;
      log_file.clear();
    }
  }
}

void Scoreboard::ProcessLine(std::string line) {
  BaseEvent* event = nullptr;
  std::smatch match;

  if (std::regex_search(line, match, kill_log_ui_regex_)) {
    event = new KillLogUIEvent(match.str(2), match.str(5));
  }
  else if (std::regex_search(line, match, update_score_message_regex_)) {
    event = new UpdateScoreMessageEvent(nlohmann::json::parse(match.str(1)));
  }
  else if (std::regex_search(line, match, bomb_defuse_regex_)) {
    event = new BombDefusedEvent();
  }

  if (event) HandleEvent(event);
}

void Scoreboard::HandleEvent(BaseEvent* event) {
  switch (event->event_type_) {
    case EventType::kNone: // this should never happen
      break;
    case EventType::kUpdateScoreMessage: {
      UpdateScoreMessageEvent* cast_event = static_cast<UpdateScoreMessageEvent*>(event);
      //std::cout << cast_event->json_data_["AttackerScore"] << "-" << cast_event->json_data_["DefenderScore"] << std::endl;
      break;
    }
    case EventType::kKillLogUI: {
      KillLogUIEvent* cast_event = static_cast<KillLogUIEvent*>(event);
      //std::cout << cast_event->killer_ << " killed " << cast_event->victim_ << std::endl;
      break;
    }
    case EventType::kBombDefused:
      std::cout << "BOMB DEFUSED!!!" << std::endl;
      break;
  }

  delete event;
}

} // namespace score_process
