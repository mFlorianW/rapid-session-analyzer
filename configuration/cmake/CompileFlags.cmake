# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

macro(setup_compile_flags)
    include(CheckCCompilerFlag)

    check_c_compiler_flag(-Wall HAS_WALL)
    if(HAS_WALL)
        add_compile_options(-Wall)
    endif()

    check_c_compiler_flag(-Wextra HAS_WEXTRA)
    if(HAS_WEXTRA)
        add_compile_options(-Wextra)
    endif()

    check_c_compiler_flag(-pedantic HAS_WPEDANTIC)
    if(HAS_WPEDANTIC)
        add_compile_options(-pedantic)
    endif()

    check_c_compiler_flag(-Wshadow HAS_WSHADOW)
    if(HAS_WSHADOW)
        add_compile_options(-Wshadow)
    endif()

    check_c_compiler_flag(-Wnon-virtual-dtor HAS_WNONVIRTUALDTOR)
    if(HAS_WNONVIRTUALDTOR)
        add_compile_options(-Wnon-virtual-dtor)
    endif()

    check_c_compiler_flag(-Wconversion HAS_WCONVERSION)
    if(HAS_WCONVERSION)
        add_compile_options(-Wconversion)
    endif()

    #-Wold-style-cast
    check_c_compiler_flag(-Wold-style-cast HAS_WOLDSTYLECAST)
    if(HAS_WOLDSTYLECAST)
        add_compile_options(-Wold-style-cast)
    endif()

    check_c_compiler_flag(-Wunused HAS_WUNUSED)
    if(HAS_WUNUSED)
        add_compile_options(-Wunused)
    endif()

    check_c_compiler_flag(-Woverloaded-virtual HAS_WOVERLOADEDVIRTUAL)
    if(HAS_WOVERLOADEDVIRTUAL)
        add_compile_options(-Woverloaded-virtual)
    endif()

    check_c_compiler_flag(-Wsign-conversion HAS_WSIGNCONVERSION)
    if(HAS_WSIGNCONVERSION)
        add_compile_options(-Wsign-conversion)
    endif()

    check_c_compiler_flag(-Wdouble-promotion HAS_WDOUBLEPROMOTION)
    if(HAS_WDOUBLEPROMOTION)
        add_compile_options(-Wdouble-promotion)
    endif()

    check_c_compiler_flag(-Wduplicated-branches HAS_WDUPLICATEDBRANCHES)
    if(HAS_WDUPLICATEDBRANCHES)
        add_compile_options(-Wduplicated-branches)
    endif()

    check_c_compiler_flag(-Wimplicit-fallthrough HAS_WIMPLICITFALLTHROUGH)
    if(HAS_WIMPLICITFALLTHROUGH)
        add_compile_options(-Wimplicit-fallthrough)
    endif()

    check_c_compiler_flag(-Wlifetime HAS_WLIFETIME)
    if(HAS_WLIFETIME)
        add_compile_options(-Wlifetime)
    endif()

    check_c_compiler_flag(-Wuseless-cast HAS_WUSELESSCAST)
    if(HAS_WUSELESSCAST)
        add_compile_options(-Wuseless-cast)
    endif()

    check_c_compiler_flag(-Wnull-dereference HAS_WNULLDEREFERENCE)
    if(HAS_WNULLDEREFERENCE)
        add_compile_options(-Wnull-dereference)
    endif()
endmacro()
