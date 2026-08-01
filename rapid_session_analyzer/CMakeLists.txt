# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

cmake_minimum_required(VERSION 3.23)

add_executable(rapid_session_analyzer
    main.cpp
)

target_link_libraries(rapid_session_analyzer
    PRIVATE
        Qt6::Core
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        RapidSessionAnalyzer::RapidLaptimer
        RapidSessionAnalyzer::RapidLaptimerPlugin
        RapidSessionAnalyzer::Controls
        RapidSessionAnalyzer::ControlsPlugin
)

qt_import_qml_plugins(rapid_session_analyzer)

set_target_properties(rapid_session_analyzer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
