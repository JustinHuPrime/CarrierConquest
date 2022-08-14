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

#include "options.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "util/exceptions/initException.h"

#if !defined(NDEBUG)
#elif defined(__linux__)
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
#error "operating system not supported/recognized"
#endif

using namespace carrier_conquest::util::exceptions;
using namespace std;
using namespace std::filesystem;
using namespace nlohmann;

namespace carrier_conquest {
namespace {
#if !defined(NDEBUG)
path getOptionsPath() { return path("options.json"); }
#elif defined(__linux__)
path getOptionsPath() {
  char const *homePath = getenv("HOME");
  if (homePath == nullptr) {
    passwd const *pw = getpwuid(geteuid());  // NOLINT(runtime/threadsafe_fn)
    if (pw == nullptr) throw InitException("unable to find home directory");
    homePath = pw->pw_dir;
  }

  path configPath(homePath);
  configPath /= ".carrier-conquest";
  configPath /= "options.json";
  return configPath;
}
#else
#error "operating system not supported/recognized"
#endif
}  // namespace

void to_json(json &j, Options const &o) {
  j["msaa"] = o.msaa;
  j["vsync"] = o.vsync;
  j["playTutorial"] = o.playTutorial;
}
void from_json(json const &j, Options &o) {
  j.at("msaa").get_to(o.msaa);
  j.at("vsync").get_to(o.vsync);
  j.at("playTutorial").get_to(o.playTutorial);
}

Options::Options() {
  path optionsPath = getOptionsPath();
  if (!exists(optionsPath)) {
    optionsPath = ASSET_PREFIX;
    optionsPath /= "defaultOptions.json";
  }

  try {
    ifstream fin;
    fin.exceptions(ifstream::failbit | ifstream::badbit);
    fin.open(optionsPath, ios_base::in | ios_base::binary);

    json j;
    fin >> j;
    j.get_to(*this);
  } catch (ios_base::failure const &e) {
    throw InitException("Could not read options file", e.what());
  } catch (json::exception const &e) {
    throw InitException("Could not read options file", e.what());
  }
}

Options::~Options() noexcept {
  try {
    ofstream fout;
    fout.exceptions(ofstream::failbit | ofstream::badbit);
    fout.open(getOptionsPath(), ios_base::out | ios_base::binary);
    json j(*this);
    fout << setw(2) << j;
  } catch (...) {
    // swallow exceptions - this is a destructor
  }
}

unique_ptr<Options> options;
}  // namespace carrier_conquest
