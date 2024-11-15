/*
 * This source code is part of MicroPP: a finite element library
 * to solve microstructural problems for composite materials.
 *
 * Copyright (C) - 2018 - Jimmy Aguilar Mena <kratsbinovish@gmail.com>
 *                        Guido Giuntoli <gagiuntoli@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

// #ifndef TIMER

// #define INSTRUMENTPP_CONSTRUCT
// #define INSTRUMENTPP_DESTROY
// #define INSTRUMENTPP_START
// #define INSTRUMENTPP_CUSTOM(strname)

// #else

#define INSTRUMENTPP_CONSTRUCT Instrument::initialize();
#define INSTRUMENTPP_DESTROY Instrument::finalize();
#define INSTRUMENTPP_START Instrument __timer__(__FUNCTION__);
#define INSTRUMENTPP_CUSTOM(strname) Instrument __custom__(strname);

#include <chrono>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>
#include <atomic>
#include <iostream>
#include <iomanip>

typedef std::vector<uint64_t> timevect;

class Instrument {
 private:
  const uint64_t start_time_;
  const std::string funct_;

  static std::atomic<size_t> instances;
  static uint64_t initialTime;
  static std::unordered_map<std::string, timevect> times;

  static inline uint64_t take_time_stamp() {
    return uint64_t(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  }

 public:
  Instrument(const std::string funct) : funct_(funct), start_time_(take_time_stamp()) {}

  ~Instrument() {
    const uint64_t elapsed = (take_time_stamp() - start_time_) * 1E-3;
    times[funct_].push_back(elapsed);
  }

  static void initialize() {
    if (!instances++) initialTime = take_time_stamp();
  }

  static uint64_t devest(const std::vector<uint64_t> &in, const uint64_t mean) {
    uint64_t out = 0;
    for (const auto &x : in) {
      const uint64_t tmp = (x - mean);
      out += tmp * tmp;
    }

    return std::sqrt(out / in.size());
  }

  static void finalize() {
    if (0 == --instances) {
      const uint64_t elapsed = (take_time_stamp() - initialTime) * 1E-3;

      size_t cont = 0;
      std::cout << "# Final execution report: total time = " << elapsed << std::endl;
      std::cout << std::setw(6) << std::left << "#No" << std::setw(25) << "function" << std::setw(8) << std::right
                << "calls" << std::setw(16) << "total time" << std::setw(16) << "percent" << std::setw(16) << "mean"
                << std::setw(16) << "stdev" << std::setw(16) << "relative" << std::endl;

      std::cout.precision(2);
      std::cout << std::fixed;

      for (auto const &f : times) {
        const uint64_t total = std::accumulate(f.second.begin(), f.second.end(), 0.0);
        const size_t entries = f.second.size();
        const uint64_t mean = total / entries;
        const double percent = double(total) * 100 / elapsed;
        const uint64_t stdev = Instrument::devest(f.second, mean);
        const double relative = double(stdev) * 100 / mean;

        std::cout << std::setw(6) << std::left << cont++ << std::setw(25) << f.first << std::setw(8) << std::right
                  << entries << std::setw(16) << total << std::setw(16) << percent << std::setw(16) << mean
                  << std::setw(16) << stdev << std::setw(16) << relative << std::endl;
      }
    }
  }
};

// #endif
#endif