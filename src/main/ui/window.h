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

#ifndef CARRIERCONQUEST_UI_WINDOW_H_
#define CARRIERCONQUEST_UI_WINDOW_H_

#include <SDL.h>

#include <memory>

namespace carrier_conquest::ui {
class Window final {
 public:
  Window();
  Window(Window const &) noexcept = delete;
  Window(Window &&) noexcept = delete;

  ~Window() noexcept;

  Window &operator=(Window const &) noexcept = delete;
  Window &operator=(Window &&) noexcept = delete;

  void render() noexcept;

  SDL_Window *getWindow() noexcept;
  int getWidth() const noexcept;
  int getHeight() const noexcept;

  void clear() noexcept;

 private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
  std::unique_ptr<std::remove_pointer<SDL_GLContext>::type,
                  decltype(&SDL_GL_DeleteContext)>
      context;
  int width;
  int height;
};

extern std::unique_ptr<Window> window;
}  // namespace carrier_conquest::ui

#endif  // CARRIERCONQUEST_UI_WINDOW_H_
