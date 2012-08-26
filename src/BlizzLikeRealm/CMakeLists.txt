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

set(blizzlike-realm_SRCS
  ${blizzlike-realm_SRCS}
  ${sources_localdir}
)

if( WIN32 )
  set(blizzlike-realm_SRCS
    ${blizzlike-realm_SRCS}
    ${sources_Debugging}
    BlizzLikeRealm.rc
  )
endif()

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/shared
  ${CMAKE_SOURCE_DIR}/src/shared/Database
  ${CMAKE_SOURCE_DIR}/src/framework
  ${ACE_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
)

set(blizzlike-realm_LINK_FLAGS "")

add_executable(blizzlike-realm
  ${blizzlike-realm_SRCS}
)

add_dependencies(blizzlike-realm revision.h)

if( NOT WIN32 )
  add_definitions(-D_BLIZZLIKE_REALM_CONFIG="${CONF_DIR}/blizzlikerealm.conf")
endif()

if( UNIX )
  set(authserver_LINK_FLAGS "-pthread ${blizzlike-realm_LINK_FLAGS}")
endif()

if( CMAKE_SYSTEM_NAME MATCHES "Darwin" )
  set(blizzlike-realm_LINK_FLAGS "-framework Carbon ${blizzlike-realm_LINK_FLAGS}")
endif()

set_target_properties(blizzlike-realm PROPERTIES LINK_FLAGS "${blizzlike-realm_LINK_FLAGS}")

target_link_libraries(blizzlike-realm
  shared
  blizzlikeframework
  ${MYSQL_LIBRARY}
  ${OPENSSL_LIBRARIES}
  ${OPENSSL_EXTRA_LIBRARIES}
  ${OSX_LIBS}
)

if( WIN32 )
  add_custom_command(TARGET blizzlike-realm
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/blizzlikerealm.conf.dist ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/
  )
endif()

if( UNIX )
  install(TARGETS blizzlike-realm DESTINATION bin)
  install(FILES blizzlikerealm.conf.dist DESTINATION etc)
elseif( WIN32 )
  install(TARGETS blizzlike-realm DESTINATION "${CMAKE_INSTALL_PREFIX}")
  install(FILES blizzlikerealm.conf.dist DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
