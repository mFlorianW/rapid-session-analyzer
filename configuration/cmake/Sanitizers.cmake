# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

macro(setup_sanitizers)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        set(SANITIZERS "address,undefined")
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            set(SANITIZERS "${SANITIZERS},leak")
        endif()
        add_compile_options(-fsanitize=${SANITIZERS} -fno-omit-frame-pointer)
        add_link_options(-fsanitize=${SANITIZERS})

        add_feature_info(Santizers SANITIZERS "Enable Address, Undefined and Leak (Clang only) sanitizers for debugging.")
    endif()
endmacro()
