# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

add_library(RapidSessionAnalyzerCommon STATIC)
add_library(RapidSessionAnalyzer::Common ALIAS RapidSessionAnalyzerCommon)

target_sources(RapidSessionAnalyzerCommon PRIVATE
    include/Common/GnssPosition.hpp
    include/Common/Json.hpp
    include/Common/Lap.hpp
    include/Common/Position.hpp
    include/Common/Session.hpp
    include/Common/SessionInfo.hpp
    include/Common/Track.hpp

    src/Json.cpp
    src/Lap.cpp
    src/Session.cpp
)

target_include_directories(RapidSessionAnalyzerCommon
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(RapidSessionAnalyzerCommon
    PUBLIC
        Qt6::Core
)

if(ENABLE_TEST)
    add_executable(test_common_domain_model tests/DomainModelJsonTest.cpp)
    add_test(NAME test_common_domain_model COMMAND test_common_domain_model)
    target_link_libraries(test_common_domain_model PRIVATE
        Qt6::Test
        RapidSessionAnalyzer::Common
        RapidSessionAnalyzer::TestHelper
    )
endif()
