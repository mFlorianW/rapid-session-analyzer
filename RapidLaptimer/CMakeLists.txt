# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

qt_add_qml_module(RapidLaptimer
    URI "RapidLaptimer"
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml/RapidLaptimer"
    STATIC
    QML_FILES
        qml/SessionDownloadPane.qml
    SOURCES
        include/RapidLaptimer/LaptimerSessionBrowser.hpp
        src/LaptimerSessionBrowser.cpp
)

add_library(RapidSessionAnalyzer::RapidLaptimer ALIAS RapidLaptimer)
add_library(RapidSessionAnalyzer::RapidLaptimerPlugin ALIAS RapidLaptimerplugin)

target_include_directories(RapidLaptimer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/RapidLaptimer
)

target_link_libraries(RapidLaptimer
    PUBLIC
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        RapidSessionAnalyzer::Workflow
        RapidSessionAnalyzer::Controls
)

if(ENABLE_TEST)
    find_package(Qt6 REQUIRED COMPONENTS Test)

    add_executable(test_rapid_laptimer_import tests/RapidLaptimerImportTest.cpp)
    add_test(NAME test_rapid_laptimer_import COMMAND test_rapid_laptimer_import)
    target_link_libraries(test_rapid_laptimer_import PRIVATE
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Test
        RapidControls
        RapidControlsplugin
        RapidLaptimer
        RapidLaptimerplugin
    )
    qt_import_qml_plugins(test_rapid_laptimer_import)
    set_tests_properties(test_rapid_laptimer_import PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
    )

    add_executable(test_rapid_laptimer_session_browser tests/LaptimerSessionBrowserTest.cpp)
    add_test(NAME test_rapid_laptimer_session_browser COMMAND test_rapid_laptimer_session_browser)
    target_link_libraries(test_rapid_laptimer_session_browser PRIVATE
        Qt6::Network
        Qt6::Test
        RapidLaptimer
        RapidSessionAnalyzer::TestHelper
    )
endif()
