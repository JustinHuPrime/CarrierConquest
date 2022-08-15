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

#include <SDL2/SDL.h>
#include <stb_image.h>

#include <iostream>
#include <sstream>

#include "options.h"
#include "ui/components.h"
#include "ui/resources.h"
#include "ui/scene/mainMenu.h"
#include "ui/scene/scene.h"
#include "ui/window.h"
#include "util/exceptions/initException.h"
#include "version.h"

using namespace std;
using namespace carrier_conquest;
using namespace carrier_conquest::util::exceptions;
using namespace carrier_conquest::ui;
using namespace carrier_conquest::ui::scene;

int main(int argc, char **) {
  cout << "Carrier Conquest version " << VERSION_MAJOR << "." << VERSION_MINOR
       << "." << VERSION_PATCH << endl;
  cout << "Copyright 2022 Justin Hu" << endl;
  cout << "This is free software; see the source for copying conditions. There "
          "is NO"
       << endl;
  cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR "
          "PURPOSE."
       << endl;

  if (argc >= 2) {
    cerr << "Carrier Conquest is a graphical progran and does not accept "
            "command line options!"
         << endl;
    return EXIT_FAILURE;
  }

  try {
    // check SDL2
    SDL_version linked;
    SDL_GetVersion(&linked);
    SDL_version compiled;
    SDL_VERSION(&compiled);
    if (compiled.major != linked.major || compiled.minor > linked.minor) {
      stringstream ss;
      ss << "Expected SDL version " << compiled.major << "." << compiled.minor
         << "." << compiled.patch << " or later, but found " << linked.major
         << "." << linked.minor << "." << linked.patch;
      throw InitException("Incompatible SDL version", ss.str());
    }

    // initialize and check freetype
    freetype = make_unique<FreeType>();
    int linkedMajor, linkedMinor, linkedPatch;
    FT_Library_Version(freetype->get(), &linkedMajor, &linkedMinor,
                       &linkedPatch);
    if (FREETYPE_MAJOR != linkedMajor || FREETYPE_MINOR > linkedMinor) {
      stringstream ss;
      ss << "Expected FreeType version " << FREETYPE_MAJOR << "."
         << FREETYPE_MINOR << "." << FREETYPE_PATCH << " or later, but found "
         << linkedMajor << "." << linkedMinor << "." << linkedPatch;
      throw InitException("Incompatible FreeType version", ss.str());
    }

    // initialize stbi
    stbi_set_flip_vertically_on_load(true);

    // set up static objects
    options = make_unique<Options>();
    window = make_unique<Window>();
    resources = make_unique<ResourceManager>();

    // load resources
    resources->loadSplash();
    SDL_SetCursor(resources->busyCursor.get());
    Background2D splash(resources->splash);
    splash.draw();
    window->render();
    resources->loadGame();
    SDL_SetCursor(resources->arrowCursor.get());

    // start actual game
    NextScene next = NextScene(mainMenu);
    while (next) next = next();

    return EXIT_SUCCESS;
  } catch (InitException const &e) {
    if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, e.getTitle().c_str(),
                                 e.getMessage().c_str(),
                                 window ? window->getWindow() : nullptr) != 0)
      cerr << "ERROR: " << e.getTitle() << ": " << e.getMessage() << endl;

    return EXIT_FAILURE;
  } catch (...) {
    if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unexpected Error",
                                 "An unexpected error has occurred.",
                                 window ? window->getWindow() : nullptr) != 0)
      cerr << "ERROR: Unexpected Error: An unexpected error has occurred."
           << endl;

    throw;
  }
}
