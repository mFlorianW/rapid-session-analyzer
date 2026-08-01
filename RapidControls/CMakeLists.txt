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
        qml/FluentIcon.qml
        qml/FluentTextField.qml
        qml/PrimaryButton.qml
        qml/Theme.qml
    RESOURCES
        qml/icons/download.svg
        qml/icons/download-dark.svg
        qml/icons/info.svg
        qml/icons/info-dark.svg
        qml/icons/library.svg
        qml/icons/library-dark.svg
)

add_library(RapidSessionAnalyzer::Controls ALIAS RapidControls)
add_library(RapidSessionAnalyzer::ControlsPlugin ALIAS RapidControlsplugin)

target_link_libraries(RapidControls
    PUBLIC
        Qt6::Quick
        Qt6::QuickControls2
)

if(ENABLE_TEST)
    find_package(Qt6 REQUIRED COMPONENTS Test)

    add_executable(test_rapid_controls_import tests/RapidControlsImportTest.cpp)
    add_test(NAME test_rapid_controls_import COMMAND test_rapid_controls_import)

    target_link_libraries(test_rapid_controls_import PRIVATE
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Test
        RapidControls
        RapidControlsplugin
    )

    qt_import_qml_plugins(test_rapid_controls_import)

    set_tests_properties(test_rapid_controls_import PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
    )
endif()
