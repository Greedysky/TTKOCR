# ***************************************************************************
# * This file is part of the TTK OCR project
# * Copyright (C) 2015 - 2026 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# ***************************************************************************

cmake_minimum_required(VERSION 3.18.0)

set_property(GLOBAL PROPERTY TTK_CORE_UTILS_KITS_HEADER_FILES
  ${TTK_CORE_UTILS_DIR}/ocralgorithmutils.h
  ${TTK_CORE_UTILS_DIR}/ocrcoreutils.h
  ${TTK_CORE_UTILS_DIR}/ocrfileutils.h
  ${TTK_CORE_UTILS_DIR}/ocrimageutils.h
)

set_property(GLOBAL PROPERTY TTK_CORE_UTILS_KITS_SOURCE_FILES
  ${TTK_CORE_UTILS_DIR}/ocralgorithmutils.cpp
  ${TTK_CORE_UTILS_DIR}/ocrcoreutils.cpp
  ${TTK_CORE_UTILS_DIR}/ocrfileutils.cpp
  ${TTK_CORE_UTILS_DIR}/ocrimageutils.cpp
)
