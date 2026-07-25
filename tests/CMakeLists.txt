# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

add_executable(test_placeholder PlaceholderTest.cpp)
add_test(NAME test_placeholder COMMAND test_placeholder)
target_link_libraries(test_placeholder PRIVATE
    Qt6::Test
)
