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

#include "ui/scene/newCampaign.h"

#include <SDL2/SDL.h>

#include "game/game.h"
#include "ui/components.h"
#include "ui/scene/loading.h"
#include "ui/scene/mainMenu.h"
#include "ui/window.h"
#include "util/loadingThread.h"

using namespace carrier_conquest::util;
using namespace std;
using namespace carrier_conquest::game;

namespace carrier_conquest::ui::scene {
class NewCampaign final {
 public:
  ButtonManager<Button2D> buttonManager;

  NewCampaign() noexcept
      : background(resources->newCampaignBackground),
        title(
            Image2D::centered(resources->newCampaignTitle, 0.5f, layout(0, 7))),
        difficulty75(Button2D::centered(resources->difficulty75On,
                                        resources->difficulty75Off, 0.5f,
                                        layout(1, 7))),
        difficulty90(Button2D::centered(resources->difficulty90On,
                                        resources->difficulty90Off, 0.5f,
                                        layout(2, 7))),
        difficulty100(Button2D::centered(resources->difficulty100On,
                                         resources->difficulty100Off, 0.5f,
                                         layout(3, 7))),
        difficulty110(Button2D::centered(resources->difficulty110On,
                                         resources->difficulty110Off, 0.5f,
                                         layout(4, 7))),
        difficulty125(Button2D::centered(resources->difficulty125On,
                                         resources->difficulty125Off, 0.5f,
                                         layout(5, 7))),
        back(Button2D::centered(resources->backOn, resources->backOff, 0.5,
                                layout(6, 7))),
        buttonManager({difficulty75, difficulty90, difficulty100, difficulty110,
                       difficulty125, back}) {}
  NewCampaign(NewCampaign const &) noexcept = delete;
  NewCampaign(NewCampaign &&) noexcept = delete;

  ~NewCampaign() noexcept = default;

  NewCampaign &operator=(NewCampaign const &) noexcept = delete;
  NewCampaign &operator=(NewCampaign &&) noexcept = delete;

  void draw() noexcept {
    background.draw();
    title.draw();
    difficulty75.draw();
    difficulty90.draw();
    difficulty100.draw();
    difficulty110.draw();
    difficulty125.draw();
    back.draw();
  }

 private:
  Background2D background;
  Image2D title;
  Button2D difficulty75;
  Button2D difficulty90;
  Button2D difficulty100;
  Button2D difficulty110;
  Button2D difficulty125;
  Button2D back;
};

constexpr array<uint32_t, 5> DIFFICULTIES = {75, 90, 100, 110, 125};

void newCampaign() noexcept {
  NewCampaign newCampaign;
  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT: {
          return;
        }
        case SDL_MOUSEBUTTONDOWN: {
          if (event.button.button == SDL_BUTTON_LEFT)
            newCampaign.buttonManager.mouseDown(event.button.x, event.button.y);

          break;
        }
        case SDL_MOUSEBUTTONUP: {
          if (event.button.button == SDL_BUTTON_LEFT) {
            switch (ptrdiff_t index = newCampaign.buttonManager.mouseUp(
                        event.button.x, event.button.y)) {
              case 0:
              case 1:
              case 2:
              case 3:
              case 4: {
                // new campaign with specified difficulty
                return loading(LoadingThread([index](stop_token const &token) {
                                 GameState::generate(token,
                                                     DIFFICULTIES[index]);
                                 GameState::load(token);
                               }),
                               []() {
                                 if (gameState) {
                                   // TODO: start playing
                                 } else {
                                   // TODO: failed to load
                                 }
                               });
              }
              case 5: {
                // back
                return mainMenu();
              }
            }
          }

          break;
        }
      }
    }

    newCampaign.draw();
    window->render();
  }
}
}  // namespace carrier_conquest::ui::scene
