# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

cmake_minimum_required(VERSION 3.23)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/configuration/cmake/")

include(FeatureSummary)
include(PreCommit)
include(CompileFlags)
include(Sanitizers)
include(Iwyu)
include(CZVersion)

cz_extract_project_version("${CMAKE_SOURCE_DIR}/.cz.toml" CZ_VERSION)
project(Rapid-Session-Analyzer VERSION "${CZ_VERSION}")
message(STATUS "Project Version: ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_TEST "Enable unit tests" OFF)
option(ENABLE_PRECOMMIT "Enables automatic pre-commit install." OFF)
add_feature_info(PreCommit ENABLE_PRECOMMIT "Automatic install of the Python pre-commit tool.")

if(ENABLE_PRECOMMIT)
    setup_precommit()
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Network
    Qml
    Quick
    QuickControls2
)

if(QT_KNOWN_POLICY_QTP0001)
    qt_policy(SET QTP0001 NEW)
endif()

if(QT_KNOWN_POLICY_QTP0004)
    qt_policy(SET QTP0004 NEW)
endif()

# Generate .qmlls.ini file for language server support
set(QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/qml" CACHE STRING "Qt Creator extra qml import paths" FORCE)

# Create .qmlls.ini in the source root
file(WRITE "${CMAKE_SOURCE_DIR}/.qmlls.ini" "[General]\nbuildDir=${CMAKE_BINARY_DIR}\n")

setup_compile_flags()
# setup_iwyu()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    setup_sanitizers()
endif()

if(ENABLE_TEST)
    include(CTest)
    find_package(Qt6 REQUIRED COMPONENTS Test)
    enable_testing()
endif()

add_subdirectory(common)
add_subdirectory(testhelper)
add_subdirectory(workflow)
add_subdirectory(RapidControls)
add_subdirectory(RapidLaptimer)

feature_summary(WHAT ALL)
