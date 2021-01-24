// event_scanner.h
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

#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include <string>
#include <regex>

#include "event.h"
#include "game_objects.h"

namespace score_process {

class EventScanner {
 public:
  EventScanner();
  void ProcessLine(std::string line);
  void HandleEvent(BaseEvent* event);
  void HandleJSONDump(nlohmann::json json_data);
 private:
  Match* match_;
  std::string log_sub_path_ = "\\..\\LocalLow\\Giant Enemy Crab\\Due Process\\Player.log"; // TODO: don't use a relative path here
  std::string update_score_message_string_ = "NewMatchmakingManager::HandleUpdateMatchScoreMessage\\( (.*) \\)";
  std::regex update_score_message_regex_;
  std::string kill_log_ui_string_ = "KillLogUI :: Entry :: <color=#(27DBFFFF|FF083AEB)><noparse>(.{0,32})<\\/noparse><\\/color> (WASTED|NEUTRALIZED|DISHONORABLY DISCHARGED|DOUBLE-CROSSED) <color=#(27DBFFFF|FF083AEB)><noparse>(.{0,32})<\\/noparse><\\/color>";
  std::regex kill_log_ui_regex_;
  std::string bomb_defuse_string_ = "GameStatusSimulator :: Bomb \\[[0-9]*\\] DEFUSED";
  std::regex bomb_defuse_regex_;
  std::string current_round_string_ = "MatchStatus :: Current Round: ([0-9]{1,})";
  std::regex current_round_regex_;
  std::string in_game_string_ = "MatchStatus :: Switch State from isMatched to isInGame";
  std::regex in_game_regex_;
  std::string join_match_in_progress_message_string_ = "NewMatchmakingManager::HandleJoinMatchInProgressMessage\\( (.*) \\)";
  std::regex join_match_in_progress_message_regex_;
  std::string json_dump_string_ = "(\\{.*\\})";
  std::regex json_dump_regex_;
};

} // namespace score_process

#endif // SCOREBOARD_H_