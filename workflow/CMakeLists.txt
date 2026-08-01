# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

add_library(RapidSessionAnalyzerWorkflow STATIC)
add_library(RapidSessionAnalyzer::Workflow ALIAS RapidSessionAnalyzerWorkflow)

target_sources(RapidSessionAnalyzerWorkflow PRIVATE
    include/Workflow/FilesystemStorage.hpp
    include/Workflow/HttpLaptimerSessionManagement.hpp
    include/Workflow/ILaptimerSessionManagement.hpp
    include/Workflow/ISessionStorage.hpp

    src/FilesystemStorage.cpp
    src/HttpLaptimerSessionManagement.cpp
)

target_include_directories(RapidSessionAnalyzerWorkflow
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(RapidSessionAnalyzerWorkflow
    PUBLIC
        Qt6::Core
        Qt6::Network
        RapidSessionAnalyzer::Common
)

if(ENABLE_TEST)
    add_executable(test_workflow_http_laptimer_session_management tests/HttpLaptimerSessionManagementTest.cpp)
    add_test(NAME test_workflow_http_laptimer_session_management COMMAND test_workflow_http_laptimer_session_management)
    target_link_libraries(test_workflow_http_laptimer_session_management PRIVATE
        Qt6::Network
        Qt6::Test
        RapidSessionAnalyzer::Workflow
        RapidSessionAnalyzer::TestHelper
    )

    add_executable(test_workflow_filesystem_storage tests/FilesystemStorageTest.cpp)
    add_test(NAME test_workflow_filesystem_storage COMMAND test_workflow_filesystem_storage)
    target_link_libraries(test_workflow_filesystem_storage PRIVATE
        Qt6::Test
        RapidSessionAnalyzer::Workflow
        RapidSessionAnalyzer::TestHelper
    )
endif()
