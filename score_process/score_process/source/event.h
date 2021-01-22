// event.h
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

#ifndef EVENT_H_
#define EVENT_H_

#include "json.hpp"

namespace score_process {

enum class EventType {
  kNone,
  kUpdateScoreMessage,
  kKillLogUI,
  kBombDefused
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

/*
class BaseRotationCommand : public BaseCommand {
protected:
  BaseRotationCommand(ObjectID target_id, CommandID command_id, float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : BaseCommand(target_id, command_id), x_(x), y_(y), z_(z), w_(w) {};
public:
  float x_;
  float y_;
  float z_;
  float w_;
};

class BasePhysicsUpdate : public BaseCommand {
protected:
  BasePhysicsUpdate(ObjectID target_id, CommandID command_id, Vector3 vector, Quaternion quaternion) : BaseCommand(target_id, command_id), vector_(vector), quaternion_(quaternion) {};
public:
  Vector3 vector_;
  Quaternion quaternion_;
};


class Event {
 public:
  EventType type = EventType::kNone;
};

class UpdateScoreMessageEvent : public Event {
 public:
  EventType type = EventType::kUpdateScoreMessage;
};

class KillLogUIEvent : public Event {
 public:
  EventType type = EventType::kKillLogUI;
  std::string killer;
  std::string victim;
};

class BombDefusedEvent : public Event {
 public:
  EventType type = EventType::kBombDefused;
};*/

} // namespace score_process

#endif // EVENT_H_