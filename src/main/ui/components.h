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

#ifndef CARRIERCONQUEST_UI_COMPONENTS_H_
#define CARRIERCONQUEST_UI_COMPONENTS_H_

#include <vector>

#include "ui/resources.h"

namespace carrier_conquest::ui {
class Background2D final {
 public:
  explicit Background2D(Texture2D &) noexcept;
  Background2D(Background2D const &) noexcept = delete;
  Background2D(Background2D &&) noexcept = default;

  ~Background2D() noexcept = default;

  Background2D &operator=(Background2D const &) noexcept = delete;
  Background2D &operator=(Background2D &&) noexcept = default;

  void draw() noexcept;

 private:
  Texture2D &texture;
};

class Image2D final {
 public:
  static Image2D centered(Texture2D &, float x, float y) noexcept;
  static Image2D alignBottom(Texture2D &, float x, float y) noexcept;
  Image2D(Image2D const &) noexcept = delete;
  Image2D(Image2D &&) noexcept = default;

  ~Image2D() noexcept = default;

  Image2D &operator=(Image2D const &) noexcept = delete;
  Image2D &operator=(Image2D &&) noexcept = default;

  void draw() noexcept;

 private:
  Texture2D &texture;
  VBO vbo;
  VAO vao;

  Image2D(Texture2D &, float x, float y) noexcept;
};

class Clickable {
 public:
  Clickable() noexcept;
  Clickable(Clickable const &) noexcept = default;
  Clickable(Clickable &&) noexcept = default;

  virtual ~Clickable() noexcept = default;

  Clickable &operator=(Clickable const &) noexcept = default;
  Clickable &operator=(Clickable &&) noexcept = default;

  virtual bool clicked(int32_t x, int32_t y) const noexcept = 0;

  virtual void activate();
  virtual void deactivate();

 protected:
  bool active;
};

template <typename T>
class ButtonManager final {
 public:
  ButtonManager(
      std::vector<std::reference_wrapper<T>> const &clickables_) noexcept
      : clickables(clickables_), clicked(clickables.end()) {}
  ButtonManager(ButtonManager const &) noexcept = delete;
  ButtonManager(ButtonManager &&) noexcept = default;

  ~ButtonManager() noexcept = default;

  ButtonManager &operator=(ButtonManager const &) noexcept = delete;
  ButtonManager &operator=(ButtonManager &&) noexcept = default;

  void mouseDown(int32_t x, int32_t y) noexcept {
    clicked = std::find_if(clickables.begin(), clickables.end(),
                           [&x, &y](T const &t) { return t.clicked(x, y); });

    if (clicked != clickables.end()) {
      clicked->get().activate();
    }
  }

  ptrdiff_t mouseUp(int32_t x, int32_t y) noexcept {
    if (clicked == clickables.end()) {
      return -1;
    } else {
      clicked->get().deactivate();
      return clicked->get().clicked(x, y) ? clicked - clickables.begin() : -1;
    }
  }

 private:
  std::vector<std::reference_wrapper<T>> clickables;
  std::vector<std::reference_wrapper<T>>::iterator clicked;
};

template <typename T>
class FocusManager final {
 public:
  FocusManager(
      std::vector<std::reference_wrapper<T>> const &clickables_) noexcept
      : clickables(clickables_), active(clickables.end()) {}
  FocusManager(FocusManager const &) noexcept = delete;
  FocusManager(FocusManager &&) noexcept = default;

  ~FocusManager() noexcept = default;

  FocusManager &operator=(FocusManager const &) noexcept = delete;
  FocusManager &operator=(FocusManager &&) noexcept = default;

  void mouseDown(int32_t x, int32_t y) noexcept {
    if (active != clickables.end()) {
      active->get().deactivate();
    }

    active =
        std::find_if(clickables.begin(), clickables.end(),
                     [&x, &y](Clickable const &t) { return t.clicked(x, y); });
  }

  T *mouseUp(int32_t x, int32_t y) noexcept {
    if (active == clickables.end()) {
      return nullptr;
    } else {
      if (active->get().clicked(x, y)) {
        active->get().activate();
        return &active->get();
      } else {
        return nullptr;
      }
    }
  }

 private:
  std::vector<std::reference_wrapper<T>> clickables;
  std::vector<std::reference_wrapper<T>>::iterator active;
};

class Button2D final : public Clickable {
 public:
  static Button2D centered(Texture2D &onTexture, Texture2D &offTexture, float x,
                           float y) noexcept;
  static Button2D alignRight(Texture2D &onTexture, Texture2D &offTexture,
                             float x, float y) noexcept;
  static Button2D alignLeft(Texture2D &onTexture, Texture2D &offTexture,
                            float x, float y) noexcept;
  Button2D(Button2D const &) noexcept = delete;
  Button2D(Button2D &&) noexcept = default;

  ~Button2D() noexcept override = default;

  Button2D &operator=(Button2D const &) noexcept = delete;
  Button2D &operator=(Button2D &&) noexcept = default;

  void draw() noexcept;

  bool clicked(int32_t x, int32_t y) const noexcept override;

 private:
  Texture2D &onTexture;
  Texture2D &offTexture;
  VBO vbo;
  VAO vao;
  float left;
  float right;
  float top;
  float bottom;

  static constexpr float RADIUS = 50.0f;

  Button2D(Texture2D &onTexture, Texture2D &offTexture, float x,
           float y) noexcept;
};

class Textbox2D final : public Clickable {
 public:
  static Textbox2D alignTop(Font &font, Texture2D &texture,
                            glm::vec4 const &colour, float x, float y) noexcept;
  Textbox2D(Textbox2D const &) noexcept = delete;
  Textbox2D(Textbox2D &&) noexcept = default;

  ~Textbox2D() noexcept = default;

  Textbox2D &operator=(Textbox2D const &) noexcept = delete;
  Textbox2D &operator=(Textbox2D &&) noexcept = default;

  operator std::u32string() const noexcept;

  void draw() noexcept;

  bool clicked(int32_t x, int32_t y) const noexcept;

  void textEditing(std::u32string const &text) noexcept;
  void textInput(std::u32string const &text) noexcept;
  void cursorLeft() noexcept;
  void cursorRight() noexcept;
  void cursorHome() noexcept;
  void cursorEnd() noexcept;
  void backspace() noexcept;

 private:
  Font &font;
  Texture2D &texture;
  glm::vec4 colour;
  VBO vbo;
  VAO vao;
  float left;
  float right;
  float top;
  float bottom;
  std::u32string preCursor;
  std::u32string composition;
  std::u32string postCursor;

  VBO glyphVBO;
  VAO glyphVAO;
  VBO cursorVBO;
  VAO cursorVAO;

  static constexpr float RADIUS = 25.0f;

  Textbox2D(Font &font, Texture2D &texture, glm::vec4 const &colour, float x,
            float y) noexcept;

  void drawCursor(float x) noexcept;
};

class TextField2D final {
 public:
  std::u32string text;

  static TextField2D centered(Font &font, Texture2D &texture,
                              glm::vec4 const &colour, float x,
                              float y) noexcept;
  TextField2D(TextField2D const &) noexcept = delete;
  TextField2D(TextField2D &&) noexcept = default;

  ~TextField2D() noexcept = default;

  TextField2D &operator=(TextField2D const &) noexcept = delete;
  TextField2D &operator=(TextField2D &&) noexcept = default;

  void draw() noexcept;

 private:
  Font &font;
  Texture2D &texture;
  glm::vec4 colour;
  VBO vbo;
  VAO vao;
  float left;
  float right;
  float top;
  float bottom;

  VBO glyphVBO;
  VAO glyphVAO;

  static constexpr float RADIUS = 0.0f;

  TextField2D(Font &font, Texture2D &texture, glm::vec4 const &colour, float x,
              float y) noexcept;
};

float layout(size_t index, size_t count) noexcept;
}  // namespace carrier_conquest::ui

#endif  // CARRIERCONQUEST_UI_COMPONENTS_H_
