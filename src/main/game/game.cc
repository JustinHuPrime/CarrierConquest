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

using namespace std;

namespace carrier_conquest::game {
void GameState::generate(std::stop_token const &token,
                         uint32_t difficulty) noexcept {}
void GameState::load(std::stop_token const &token) noexcept {}

GameState::GameState() {}

GameState::~GameState() {}

unique_ptr<GameState> gameState;
}  // namespace carrier_conquest::game
