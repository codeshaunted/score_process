// game_objects.h
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

#ifndef GAME_OBJECTS_H_
#define GAME_OBJECTS_H_

#include <vector>
#include <string>

namespace score_process {

struct Player {
  std::string name;
  int kills;
  int deaths;
};

struct Team {
  std::vector<Player> players;
  int score;
};

enum class GameMode {
  kCasual = 1,
  kRanked = 2
};

enum class WinCondition {
  kBombDefused,
  kBombExploded,
  kAttackersEliminated
};

struct Match {
  GameMode game_mode;
  Team attacker_team;
  Team defender_team;
  std::vector<WinCondition> rounds;
};

}

#endif // GAME_OBJECTS_H_