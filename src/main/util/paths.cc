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

#include "util/paths.h"

using namespace std::filesystem;

namespace carrier_conquest::util {
#if !defined(NDEBUG)
std::filesystem::path getSavePath() { return current_path(); }
#elif defined(__linux__)
path getSavePath() {
  char const *homePath = getenv("HOME");
  if (homePath == nullptr) {
    passwd const *pw = getpwuid(geteuid());  // NOLINT(runtime/threadsafe_fn)
    if (pw == nullptr) throw InitException("unable to find home directory");
    homePath = pw->pw_dir;
  }

  return path(homePath) / ".carrier-conquest";
}
#else
#error "operating system not supported/recognized"
#endif
}  // namespace carrier_conquest::util
