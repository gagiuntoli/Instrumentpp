/*
 *  This source code is part of Instrument library.
 *
 *  Copyright (C) - 2024 - Guido Giuntoli <gagiuntoli@gmail.com>
 *                         Jimmy Aguilar Mena <kratsbinovish@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "instrument.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N 100000

int func_3(void);

int func_1(void) {
  INSTRUMENTPP_START

  int j = 0;
  for (int k = 0; k < 100; ++k) {
    for (int i = 0; i < N; ++i)
		j += i;
    for (int i = 0; i < N; ++i)
		j -= i;
  }

  return j;
}

int func_2(void) {
  INSTRUMENTPP_START

  int j = 0;
  for (int i = 0; i < N; ++i)
	  j += i;
  for (int i = 0; i < N; ++i)
	  j -= i;

  func_3();

  return j;
}

int func_3(void) {
  INSTRUMENTPP_START

  int j = 0;
  for (int i = 0; i < N; ++i)
	  j += i;

  for (int i = 0; i < N; ++i)
	  j -= i;

  return j;
}

int main(void) {
  INSTRUMENTPP_CONSTRUCT;

  for (int i = 0; i < 10; i++) {
    func_2();
    func_1();
    func_1();
    func_2();
    func_2();
    func_2();
    func_1();
    func_2();
  }

  return 0;
}
