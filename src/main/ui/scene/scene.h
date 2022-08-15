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

#ifndef CARRIERCONQUEST_UI_SCENE_SCENE_H_
#define CARRIERCONQUEST_UI_SCENE_SCENE_H_

#include <functional>
#include <optional>

namespace carrier_conquest::ui::scene {
struct NextScene {
 public:
  template <typename T>
  NextScene(T &&next) noexcept : value(next) {}
  NextScene(NextScene const &) noexcept = default;
  NextScene(NextScene &&) noexcept = default;

  ~NextScene() noexcept = default;

  NextScene &operator=(NextScene const &) noexcept = default;
  NextScene &operator=(NextScene &&) noexcept = default;

  operator bool() const noexcept;
  NextScene operator()() const noexcept;

  std::optional<std::function<NextScene()>> value;
};
}  // namespace carrier_conquest::ui::scene

#endif  // CARRIERCONQUEST_UI_SCENE_SCENE_H_
