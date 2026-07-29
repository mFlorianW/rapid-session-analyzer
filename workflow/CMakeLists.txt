# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

add_library(RapidSessionAnalyzerWorkflow STATIC)
add_library(RapidSessionAnalyzer::Workflow ALIAS RapidSessionAnalyzerWorkflow)

target_sources(RapidSessionAnalyzerWorkflow PRIVATE
    include/Workflow/FilesystemStorage.hpp
    include/Workflow/ISessionStorage.hpp

    src/FilesystemStorage.cpp
)

target_include_directories(RapidSessionAnalyzerWorkflow
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(RapidSessionAnalyzerWorkflow
    PUBLIC
        Qt6::Core
        RapidSessionAnalyzer::Common
)
