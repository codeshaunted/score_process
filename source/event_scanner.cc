// event_scanner.cc
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

#include "event_scanner.h"

#include <iostream>
#include <fstream>

#include "json/single_include/nlohmann/json.hpp"

namespace score_process {

EventScanner::EventScanner() {
  // somehow make this regex initialization more dynamic? maybe an std::map?
  update_score_message_regex_ = std::regex(update_score_message_string_);
  kill_log_ui_regex_ = std::regex(kill_log_ui_string_);
  bomb_defuse_regex_ = std::regex(bomb_defuse_string_);
  current_round_regex_ = std::regex(current_round_string_);
  in_game_regex_ = std::regex(in_game_string_);
  join_match_in_progress_message_regex_ = std::regex(join_match_in_progress_message_string_);
  json_dump_regex_ = std::regex(json_dump_string_);

  std::string roaming_path = getenv("APPDATA"); // gets path to AppData\\Roaming, TODO: maybe use the "safe" version?

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

  match_ = new Match();
}

void EventScanner::ProcessLine(std::string line) {
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
  else if (std::regex_search(line, match, current_round_regex_)) {
    event = new CurrentRoundEvent(std::stoi(match.str(1)));
  }
  else if (std::regex_search(line, match, join_match_in_progress_message_regex_)) {
    event = new JoinMatchInProgressMessageEvent(nlohmann::json::parse(match.str(1)));
  }
  else if (std::regex_search(line, match, json_dump_regex_)) {
    event = new JSONDumpEvent(nlohmann::json::parse(match.str(1)));
  }

  if (event) HandleEvent(event);
}

void EventScanner::HandleEvent(BaseEvent* event) {
  switch (event->event_type_) {
    case EventType::kNone: // this should never happen
      break;
    case EventType::kUpdateScoreMessage: {
      UpdateScoreMessageEvent* cast_event = static_cast<UpdateScoreMessageEvent*>(event);
      std::cout << "ROUND ENDED, SCORE IS: " << cast_event->json_data_["AttackerScore"] << "-" << cast_event->json_data_["DefenderScore"] << std::endl;
      break;
    }
    case EventType::kKillLogUI: {
      KillLogUIEvent* cast_event = static_cast<KillLogUIEvent*>(event);
      //std::cout << cast_event->killer_ << " killed " << cast_event->victim_ << std::endl;
      break;
    }
    case EventType::kBombDefused:
      std::cout << "BOMB DEFUSED" << std::endl;
      break;
    case EventType::kCurrentRound: {
      CurrentRoundEvent* cast_event = static_cast<CurrentRoundEvent*>(event);
      break;
    }
    case EventType::kJoinMatchInProgressMessage: {
      JoinMatchInProgressMessageEvent* cast_event = static_cast<JoinMatchInProgressMessageEvent*>(event);
      std::cout << cast_event->json_data_ << std::endl;
      break;
    }
    case EventType::kJSONDump: {
      JSONDumpEvent* cast_event = static_cast<JSONDumpEvent*>(event);
      HandleJSONDump(cast_event->json_data_);
      break;
    }
  }

  delete event;
}

void EventScanner::HandleJSONDump(nlohmann::json json_data) {

}

} // namespace score_process
