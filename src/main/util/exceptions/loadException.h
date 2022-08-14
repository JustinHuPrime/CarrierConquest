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

#ifndef CARRIERCONQUEST_UTIL_EXCEPTIONS_LOADEXCEPTION_H_
#define CARRIERCONQUEST_UTIL_EXCEPTIONS_LOADEXCEPTION_H_

#include <stdexcept>
#include <string>

namespace carrier_conquest::util::exceptions {
class LoadException : public std::exception {
 public:
  LoadException(std::string const &title, std::string const &message) noexcept;
  explicit LoadException(std::string const &message) noexcept;
  LoadException(LoadException const &) noexcept = default;
  LoadException(LoadException &&) noexcept = default;

  ~LoadException() noexcept override = default;

  LoadException &operator=(LoadException const &) noexcept = default;
  LoadException &operator=(LoadException &&) noexcept = default;

  char const *what() const noexcept override;
  std::string const &getTitle() const noexcept;
  std::string const &getMessage() const noexcept;

 private:
  std::string title;
  std::string message;
  std::string whatString;
};
}  // namespace carrier_conquest::util::exceptions

#endif  // CARRIERCONQUEST_UTIL_EXCEPTIONS_LOADEXCEPTION_H_
