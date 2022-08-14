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

#ifndef CARRIERCONQUEST_UTIL_LOADINGTHREAD_H_
#define CARRIERCONQUEST_UTIL_LOADINGTHREAD_H_

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>

namespace carrier_conquest::util {
class LoadingThread final {
 public:
  explicit LoadingThread(
      std::function<void(std::stop_token)> const &function) noexcept;
  LoadingThread(LoadingThread const &) noexcept = delete;
  LoadingThread(LoadingThread &&) noexcept = default;

  ~LoadingThread() noexcept = default;

  LoadingThread &operator=(LoadingThread const &) noexcept = delete;
  LoadingThread &operator=(LoadingThread &&) noexcept = default;

  bool isRunning() const noexcept;

 private:
  std::atomic_bool running;
  std::function<void(std::stop_token)> function;
  std::jthread thread;
};
}  // namespace carrier_conquest::util

#endif  // CARRIERCONQUEST_UTIL_LOADINGTHREAD_H_
