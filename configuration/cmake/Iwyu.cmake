# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

macro(setup_iwyu)
    find_program(IWYU_PATH NAMES include-what-you-use iwyu)

    if(IWYU_PATH)
        set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})
        add_feature_info(IWYU IWYU_PATH "Enable include-what-you-use with path: ${IWYU_PATH}")
    else()
        message(STATUS "include-what-you-use not found. Please install it to use this feature.")
    endif()

endmacro()
