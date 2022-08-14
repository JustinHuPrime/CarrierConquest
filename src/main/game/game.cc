// Copyright 2022 Justin Hu
//
// This file is part of Carrier Conquest.
//
// Carrier Conquest is free software: you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// Carrier Conquest is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public
// License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Carrier Conquest. If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "game/game.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include "util/paths.h"

using namespace std;
using namespace std::filesystem;
using namespace carrier_conquest::util;
using namespace carrier_conquest::util::exceptions;
using namespace nlohmann;

namespace carrier_conquest::game {
void GameState::generate(std::stop_token const &token,
                         uint32_t difficulty) noexcept {
  // TODO
}
void GameState::load(std::stop_token const &token) noexcept {
  try {
    gameState = unique_ptr<GameState>(new GameState);
  } catch (LoadException const &e) {
    gameState = e;
  }
}

void to_json(json &j, GameState const &s) {}

void from_json(json const &j, GameState &s) {}

GameState::GameState() {
  path savePath = getSavePath() / "save.json";

  try {
    ifstream fin;
    fin.exceptions(ifstream::failbit | ifstream::badbit);
    fin.open(savePath, ios_base::in | ios_base::binary);

    json j;
    j.get_to(*this);
  } catch (ios_base::failure const &e) {
    throw LoadException("Could not read save file", e.what());
  } catch (json::exception const &e) {
    throw LoadException("Could not read save file", e.what());
  }
}

GameState::~GameState() noexcept {
  try {
    ofstream fout;
    fout.exceptions(ofstream::failbit | ofstream::badbit);
    fout.open(getSavePath() / "save.json", ios_base::out | ios_base::binary);
    json j(*this);
    fout << setw(2) << j;
  } catch (...) {
    // swallow exceptions - this is a destructor
  }
}

std::variant<std::unique_ptr<GameState>, util::exceptions::LoadException>
    gameState;
}  // namespace carrier_conquest::game
