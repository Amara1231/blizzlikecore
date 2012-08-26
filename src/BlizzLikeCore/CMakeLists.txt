# Copyright (C) 2011-2012 BlizzLikeCore <http://blizzlike.servegame.com/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

file(GLOB sources_localdir *.cpp *.h)

set(blizzlike-core_SRCS
  ${blizzlike-core_SRCS}
  ${sources_localdir}
)

if( WIN32 )
  set(blizzlike-core_SRCS
    ${blizzlike-core_SRCS}
    ${sources_Debugging}
    BlizzLikeCore.rc
  )
endif()

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/dep/gsoap
  ${CMAKE_SOURCE_DIR}/dep/sockets/include
  ${CMAKE_SOURCE_DIR}/dep/SFMT
  ${CMAKE_SOURCE_DIR}/dep/mersennetwister
  ${CMAKE_SOURCE_DIR}/src/collision
  ${CMAKE_SOURCE_DIR}/src/shared
  ${CMAKE_SOURCE_DIR}/src/shared/Database
  ${CMAKE_SOURCE_DIR}/src/framework
  ${CMAKE_SOURCE_DIR}/src/game
  ${ACE_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
)

set(blizzlike-core_LINK_FLAGS "")

add_executable(blizzlike-core ${blizzlike-core_SRCS})

if( NOT WIN32 )
  add_definitions(-D_BLIZZLIKE_CORE_CONFIG="${CONF_DIR}/blizzlikecore.conf")
endif()

add_dependencies(blizzlike-core revision.h)

if( UNIX )
  set(blizzlike-core_LINK_FLAGS "-pthread ${blizzlike-core_LINK_FLAGS}")
endif()

set_target_properties(blizzlike-core PROPERTIES LINK_FLAGS "${blizzlike-core_LINK_FLAGS}")

target_link_libraries(blizzlike-core
  game
  shared
  scripts
  blizzlikeframework
  collision
  g3dlib
  gsoap
  ${JEMALLOC_LIBRARY}
  ${READLINE_LIBRARY}
  ${TERMCAP_LIBRARY}
  ${ACE_LIBRARY}
  ${MYSQL_LIBRARY}
  ${OPENSSL_LIBRARIES}
  ${OPENSSL_EXTRA_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${OSX_LIBS}
)

if( WIN32 )
  add_custom_command(TARGET blizzlike-core
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/blizzlikecore.conf.dist ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/
  )
endif()

if( UNIX )
  install(TARGETS blizzlike-core DESTINATION bin)
  install(FILES blizzlikecore.conf.dist DESTINATION etc)
elseif( WIN32 )
  install(TARGETS blizzlike-core DESTINATION "${CMAKE_INSTALL_PREFIX}")
  install(FILES blizzlikecore.conf.dist DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
