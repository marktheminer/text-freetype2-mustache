# cmake_minimum_required(VERSION 3.16...3.26)
#
# include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)
#
# project(${_name} LANGUAGES C CXX VERSION ${_version} )
#
# option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" ON) option(ENABLE_QT "Use Qt functionality" ON)
#
# include(compilerconfig) include(defaults) include(helpers)
#
# add_library(${CMAKE_PROJECT_NAME} MODULE src/datetime.cpp src/datetime.h src/text.cpp src/text.h)
#
# find_package(libobs REQUIRED) target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs OBS::libobs)
#
# target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<PLATFORM_ID:Windows>:/IGNORE:4098>)
#
# if(ENABLE_FRONTEND_API) find_package(obs-frontend-api REQUIRED) target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
# OBS::obs-frontend-api) endif()
#
# if(ENABLE_QT) find_qt(COMPONENTS Widgets Core) target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt::Core
# Qt::Widgets) target_compile_options( ${CMAKE_PROJECT_NAME} PRIVATE
# $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header -Wno-comma>) set_target_properties(
# ${CMAKE_PROJECT_NAME} PROPERTIES AUTOMOC ON AUTOUIC_SEARCH_PATHS forms AUTOUIC ON AUTORCC ON) endif()
#
# target_sources(${CMAKE_PROJECT_NAME} PRIVATE forms/obs-text-mustache-definitions.ui)
#
# target_sources(${CMAKE_PROJECT_NAME} PRIVATE src/plugin-main.c $<$<PLATFORM_ID:Darwin>:src/find-font-cocoa.m>
# $<$<PLATFORM_ID:Darwin>:src/find-font-iconv.c> $<$<PLATFORM_ID:Linux,FreeBSD,OpenBSD>:src/find-font-unix.c>
# $<$<PLATFORM_ID:Windows,Darwin>:src/find-font.c> $<$<PLATFORM_ID:Windows>:src/find-font-windows.c> "src/find-font.h"
# "src/obs-convenience.c" "src/obs-convenience.h" "src/text-freetype2.c" "src/text-freetype2.h"
# "src/text-functionality.c" "src/datetime.cpp" "src/datetime.h" "src/obs-text-mustache-definitions.cpp" "src/text.cpp"
# "src/text.h" "src/variables.cpp")
#
# option(ENABLE_FREETYPE "Enable FreeType text plugin" ON)
#
# find_package(Freetype REQUIRED)
#
# target_link_libraries( ${CMAKE_PROJECT_NAME} PRIVATE Freetype::Freetype $<$<PLATFORM_ID:Darwin>:Iconv::Iconv>
# "$<$<PLATFORM_ID:Darwin>:$<LINK_LIBRARY:FRAMEWORK,Cocoa.framework>>"
# $<$<PLATFORM_ID:Linux,FreeBSD,OpenBSD>:Fontconfig::Fontconfig>)
#
# set_target_properties_plugin(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${_name})

cmake_minimum_required(VERSION 3.16...3.26)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)

project(${_name} VERSION ${_version})

option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" ON)
option(ENABLE_QT "Use Qt functionality" ON)

include(compilerconfig)
include(defaults)
include(helpers)

add_library(${CMAKE_PROJECT_NAME} MODULE)

find_package(libobs REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

if(ENABLE_QT)
  find_qt(COMPONENTS Widgets Core)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets)
  target_compile_options(
    ${CMAKE_PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header
                                  -Wno-comma>)
  set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES AUTOMOC ON
               AUTOUIC_SEARCH_PATHS forms
               AUTOUIC ON
               AUTORCC ON)
endif()

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  PRIVATE Freetype::Freetype $<$<PLATFORM_ID:Darwin>:Iconv::Iconv>
          "$<$<PLATFORM_ID:Darwin>:$<LINK_LIBRARY:FRAMEWORK,Cocoa.framework>>"
          $<$<PLATFORM_ID:Linux,FreeBSD,OpenBSD>:Fontconfig::Fontconfig>)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE forms/obs-text-mustache-definitions.ui)

target_sources(
  ${CMAKE_PROJECT_NAME}
  PRIVATE src/plugin-main.c
          $<$<PLATFORM_ID:Darwin>:src/find-font-cocoa.m>
          $<$<PLATFORM_ID:Darwin>:src/find-font-iconv.c>
          $<$<PLATFORM_ID:Linux,FreeBSD,OpenBSD>:src/find-font-unix.c>
          $<$<PLATFORM_ID:Windows,Darwin>:src/find-font.c>
          $<$<PLATFORM_ID:Windows>:src/find-font-windows.c>
          "src/obs-convenience.c"
          "src/text-freetype2.c"
          "src/update-text.cpp"
          "src/text-functionality.c"
          "src/datetime.cpp"
          "src/obs-text-mustache-definitions.cpp"
          "src/text.cpp"
          "src/variables.cpp")

option(ENABLE_FREETYPE "Enable FreeType text plugin" ON)

find_package(Freetype REQUIRED)

if(OS_MACOS)
  find_package(Iconv REQUIRED)
elseif(
  OS_LINUX
  OR OS_FREEBSD
  OR OS_OPENBSD)
  find_package(Fontconfig REQUIRED)
endif()

target_sources(${CMAKE_PROJECT_NAME} PRIVATE src/plugin-main.c)

set_target_properties_plugin(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${_name})
