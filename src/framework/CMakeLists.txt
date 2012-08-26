# Copyright (C) 2011-2012 BlizzLikeCore <http://blizzlike.servegame.com/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

SET(blizzlikeframework_STAT_SRCS
   Policies/ObjectLifeTime.cpp
   Utilities/EventProcessor.cpp
)

include_directories(
  ${ACE_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/src/framework
)

add_library(blizzlikeframework STATIC ${blizzlikeframework_STAT_SRCS})
