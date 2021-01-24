// event.h
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

#ifndef EVENT_H_
#define EVENT_H_

#include "json/single_include/nlohmann/json.hpp"

namespace score_process {

enum class EventType {
  kNone,
  kUpdateScoreMessage,
  kKillLogUI,
  kBombDefused,
  kCurrentRound,
  kJoinMatchInProgressMessage,
  kJSONDump
};

class BaseEvent {
 protected:
  BaseEvent(EventType event_type) : event_type_(event_type) {};
 public:
  EventType event_type_;
};

class UpdateScoreMessageEvent : public BaseEvent {
 public:
  UpdateScoreMessageEvent(nlohmann::json json_data) : BaseEvent(EventType::kUpdateScoreMessage), json_data_(json_data) {};
  nlohmann::json json_data_;
};

class KillLogUIEvent : public BaseEvent {
 public:
  KillLogUIEvent(std::string killer, std::string victim) : BaseEvent(EventType::kKillLogUI), killer_(killer), victim_(victim) {};
  std::string killer_;
  std::string victim_;
};

class BombDefusedEvent : public BaseEvent {
 public:
  BombDefusedEvent() : BaseEvent(EventType::kBombDefused) {};
};

class CurrentRoundEvent : public BaseEvent {
 public:
  CurrentRoundEvent(int round) : BaseEvent(EventType::kCurrentRound), round_(round) {};
  int round_;
};

class JoinMatchInProgressMessageEvent : public BaseEvent {
 public:
  JoinMatchInProgressMessageEvent(nlohmann::json json_data) : BaseEvent(EventType::kJoinMatchInProgressMessage), json_data_(json_data) {};
  nlohmann::json json_data_;
};

class JSONDumpEvent : public BaseEvent {
 public:
  JSONDumpEvent(nlohmann::json json_data) : BaseEvent(EventType::kJSONDump), json_data_(json_data) {};
  nlohmann::json json_data_;
};

} // namespace score_process

#endif // EVENT_H_