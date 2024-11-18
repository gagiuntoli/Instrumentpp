# Copyright (C) 2024 - 2024 - Guido Giuntoli <gagiuntoli@gmail.com>
#                             Jimmy Aguilar Mena <kratsbinovish@gmail.com>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


cmake_minimum_required(VERSION 3.14)
project(Instrumentpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(INSTRUMENTPP_ACTIVE "Activates the instrumentation" ON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(example_1 examples/example_1.cpp)
if (INSTRUMENTPP_ACTIVE)
    target_compile_definitions(example_1 PUBLIC INSTRUMENTPP_ACTIVE)
endif()


enable_testing()

add_test(NAME example_1 COMMAND ./example_1)
