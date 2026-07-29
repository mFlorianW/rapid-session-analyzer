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
