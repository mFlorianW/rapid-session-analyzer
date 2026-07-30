# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

add_library(RapidSessionAnalyzerTestHelper STATIC)
add_library(RapidSessionAnalyzer::TestHelper ALIAS RapidSessionAnalyzerTestHelper)

target_sources(RapidSessionAnalyzerTestHelper PRIVATE
    include/TestHelper/SessionSamples.hpp

    src/SessionSamples.cpp
)

target_include_directories(RapidSessionAnalyzerTestHelper
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(RapidSessionAnalyzerTestHelper
    PUBLIC
        Qt6::Core
        RapidSessionAnalyzer::Common
)
