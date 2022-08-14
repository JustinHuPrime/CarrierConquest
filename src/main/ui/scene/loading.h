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

#ifndef CARRIERCONQUEST_UI_SCENE_LOADING_H_
#define CARRIERCONQUEST_UI_SCENE_LOADING_H_

#include "util/loadingThread.h"

namespace carrier_conquest::ui::scene {
void loading(util::LoadingThread loader,
             std::function<void()> const &next) noexcept;
}

#endif  // CARRIERCONQUEST_UI_SCENE_LOADING_H_
