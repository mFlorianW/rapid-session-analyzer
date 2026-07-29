# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

add_executable(test_common_domain_model ../common/tests/DomainModelJsonTest.cpp)
add_test(NAME test_common_domain_model COMMAND test_common_domain_model)
target_link_libraries(test_common_domain_model PRIVATE
    Qt6::Test
    RapidSessionAnalyzer::Common
    RapidSessionAnalyzer::TestHelper
)

add_executable(test_workflow_filesystem_storage ../workflow/tests/FilesystemStorageTest.cpp)
add_test(NAME test_workflow_filesystem_storage COMMAND test_workflow_filesystem_storage)
target_link_libraries(test_workflow_filesystem_storage PRIVATE
    Qt6::Test
    RapidSessionAnalyzer::Workflow
    RapidSessionAnalyzer::TestHelper
)

add_executable(test_rapid_controls_import RapidControlsImportTest.cpp)
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
