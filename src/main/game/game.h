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

#ifndef CARRIERCONQUEST_GAME_GAME_H_
#define CARRIERCONQUEST_GAME_GAME_H_

#include <cstdint>
#include <memory>
#include <thread>
#include <variant>

#include "util/exceptions/loadException.h"

namespace carrier_conquest::game {
class GameState final {
 public:
  static void generate(std::stop_token const &token,
                       uint32_t difficulty) noexcept;
  static void load(std::stop_token const &token) noexcept;

  GameState(GameState const &) noexcept = delete;
  GameState(GameState &&) noexcept = delete;

  ~GameState() noexcept;

  GameState &operator=(GameState const &) noexcept = delete;
  GameState &operator=(GameState &&) noexcept = delete;

 private:
  GameState();
};

extern std::variant<std::unique_ptr<GameState>, util::exceptions::LoadException>
    gameState;
}  // namespace carrier_conquest::game

#endif  // CARRIERCONQUEST_GAME_GAME_H_
