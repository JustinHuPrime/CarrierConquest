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

#include "ui/scene/loading.h"

#include <SDL2/SDL.h>

#include "ui/components.h"
#include "ui/window.h"

using namespace carrier_conquest::util;
using namespace std;

namespace carrier_conquest::ui::scene {
class Loading final {
 public:
  Loading() noexcept : background(resources->loadingBackground) {}
  Loading(Loading const &) noexcept = delete;
  Loading(Loading &&) noexcept = delete;

  ~Loading() noexcept = default;

  Loading &operator=(Loading const &) noexcept = delete;
  Loading &operator=(Loading &&) noexcept = delete;

  void draw() noexcept { background.draw(); }

 private:
  Background2D background;
};

void loading(LoadingThread loader, function<void()> const &next) noexcept {
  Loading loading;

  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT: {
          return;
        }
      }
    }

    if (!loader.isRunning()) {
      return next();
    }

    loading.draw();
    window->render();
  }
}
}  // namespace carrier_conquest::ui::scene
