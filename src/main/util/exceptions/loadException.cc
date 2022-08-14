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

#include "loadException.h"

#include <sstream>

using namespace std;

namespace carrier_conquest::util::exceptions {
LoadException::LoadException(string const &title,
                             string const &message) noexcept
    : title(title), message(message), whatString([&title, &message]() {
        stringstream ss;
        ss << title << ": " << message;
        return ss.str();
      }()) {}

LoadException::LoadException(string const &message) noexcept
    : title(message), message(message), whatString(message) {}

char const *LoadException::what() const noexcept { return whatString.c_str(); }

string const &LoadException::getTitle() const noexcept { return title; }

string const &LoadException::getMessage() const noexcept { return message; }
}  // namespace carrier_conquest::util::exceptions
