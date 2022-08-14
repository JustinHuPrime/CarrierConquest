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

#include "ui/scene/mainMenu.h"

#include <SDL2/SDL.h>

#include "game/game.h"
#include "ui/components.h"
#include "ui/scene/loading.h"
#include "ui/scene/newCampaign.h"
#include "ui/window.h"

using namespace carrier_conquest::util;
using namespace std;
using namespace carrier_conquest::game;

namespace carrier_conquest::ui::scene {
class MainMenu final {
 public:
  ButtonManager<Button2D> buttonManager;

  MainMenu() noexcept
      : background(resources->mainMenuBackground),
        title(Image2D::centered(resources->mainMenuTitle, 0.5f, layout(0, 5))),
        newCampaign(Button2D::centered(resources->newCampaignOn,
                                       resources->newCampaignOff, 0.5f,
                                       layout(1, 5))),
        loadCampaign(Button2D::centered(resources->loadCampaignOn,
                                        resources->loadCampaignOff, 0.5f,
                                        layout(2, 5))),
        options(Button2D::centered(resources->optionsOn, resources->optionsOff,
                                   0.5f, layout(3, 5))),
        quit(Button2D::centered(resources->quitOn, resources->quitOff, 0.5f,
                                layout(4, 5))),
        buttonManager({newCampaign, loadCampaign, options, quit}) {}
  MainMenu(MainMenu const &) noexcept = delete;
  MainMenu(MainMenu &&) noexcept = delete;

  ~MainMenu() noexcept = default;

  MainMenu &operator=(MainMenu const &) noexcept = delete;
  MainMenu &operator=(MainMenu &&) noexcept = delete;

  void draw() noexcept {
    background.draw();
    title.draw();
    newCampaign.draw();
    loadCampaign.draw();
    options.draw();
    quit.draw();
  }

 private:
  Background2D background;
  Image2D title;
  Button2D newCampaign;
  Button2D loadCampaign;
  Button2D options;
  Button2D quit;
};

void mainMenu() noexcept {
  MainMenu mainMenu;

  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT: {
          return;
        }
        case SDL_MOUSEBUTTONDOWN: {
          if (event.button.button == SDL_BUTTON_LEFT)
            mainMenu.buttonManager.mouseDown(event.button.x, event.button.y);

          break;
        }
        case SDL_MOUSEBUTTONUP: {
          if (event.button.button == SDL_BUTTON_LEFT) {
            switch (mainMenu.buttonManager.mouseUp(event.button.x,
                                                   event.button.y)) {
              case 0: {
                // new campaign
                return newCampaign();
              }
              case 1: {
                // load campaign
                return loading(LoadingThread([](stop_token const &token) {
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
              case 2: {
                // options
                return;  // TODO
              }
              case 3: {
                // quit
                return;
              }
            }
          }

          break;
        }
      }
    }

    mainMenu.draw();
    window->render();
  }
}
}  // namespace carrier_conquest::ui::scene
