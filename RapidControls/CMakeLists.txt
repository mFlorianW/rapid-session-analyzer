# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

set_source_files_properties(qml/Theme.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(RapidControls
    URI "Rapid.Controls"
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml/Rapid/Controls"
    STATIC
    QML_FILES
        qml/DialogSurface.qml
        qml/PrimaryButton.qml
        qml/Theme.qml
)

add_library(RapidSessionAnalyzer::Controls ALIAS RapidControls)
add_library(RapidSessionAnalyzer::ControlsPlugin ALIAS RapidControlsplugin)

target_link_libraries(RapidControls
    PUBLIC
        Qt6::Quick
        Qt6::QuickControls2
)
