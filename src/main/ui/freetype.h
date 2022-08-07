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

#ifndef CARRIERCONQUEST_UI_FREETYPE_H_
#define CARRIERCONQUEST_UI_FREETYPE_H_

#include <memory>

#include "ft2build.h"
#include FT_FREETYPE_H

namespace carrier_conquest::ui {
class FreeType final {
 public:
  FreeType();
  FreeType(FreeType const &) noexcept = delete;
  FreeType(FreeType &&) noexcept = delete;

  ~FreeType() noexcept = default;

  FreeType &operator=(FreeType const &) noexcept = delete;
  FreeType &operator=(FreeType &&) noexcept = delete;

  FT_Library get() noexcept;
  FT_Library const get() const noexcept;

 private:
  std::unique_ptr<std::remove_pointer<FT_Library>::type,
                  decltype(&FT_Done_FreeType)>
      library;
};

extern std::unique_ptr<FreeType> freetype;
}  // namespace carrier_conquest::ui

#endif  // CARRIERCONQUEST_UI_FREETYPE_H_
