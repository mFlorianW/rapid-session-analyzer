# SPDX-FileCopyrightText: 2026 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

# Extracts the Commitizen version from the config file and sets:
# - OUT_VERSION to the full version string, either "xx.yy.zz" or "xx.yy.zz-bn"
#
# Supported formats:
#   version = "1.2.3"      -> OUT_VERSION = '1.2.3'
#   version = "1.2.3-b4"   -> OUT_VERSION = '1.2.3.4'
# 
# Usage:
#   cz_extract_project_version("${CMAKE_SOURCE_DIR}/pyproject.toml" CZ_VERSION)
#   project(MyProj VERSION "${CZ_VERSION}")
function(cz_extract_project_version TOML_FILE OUT_VERSION)
    if(NOT DEFINED TOML_FILE OR TOML_FILE STREQUAL "")
        message(FATAL_ERROR "cz_extract_project_version: TOML_FILE is empty")
    endif()
    if(NOT EXISTS "${TOML_FILE}")
        message(FATAL_ERROR "cz_extract_project_version: File not found: ${TOML_FILE}")
    endif()
    if(NOT DEFINED OUT_VERSION OR OUT_VERSION STREQUAL "")
        message(FATAL_ERROR "cz_extract_project_version: OUT_VERSION var name is empty")
    endif()

    file(READ "${TOML_FILE}" _cz_toml)

    # Find: version = "x.y.z" or version = "x.y.z-bN"
    string(REGEX MATCH
        "(^|[\r\n])[ \t]*version[ \t]*=[ \t]*['\"]([0-9]+\\.[0-9]+\\.[0-9]+(-b[0-9]+)?)['\"]"
        _cz_version_match
        "${_cz_toml}"
    )

    if(NOT _cz_version_match)
    message(FATAL_ERROR
        "cz_extract_project_version: Could not find version = \"x.y.z\" (or \"x.y.z-bN\") in: ${TOML_FILE}"
    )
    endif()

    set(_cz_raw_version "${CMAKE_MATCH_2}")

    # Parse and set components.
    if(_cz_raw_version MATCHES "^([0-9]+)\\.([0-9]+)\\.([0-9]+)-b([0-9]+)$")
    set(_maj   "${CMAKE_MATCH_1}")
    set(_min   "${CMAKE_MATCH_2}")
    set(_pat   "${CMAKE_MATCH_3}")
    set(_tweak "${CMAKE_MATCH_4}") # bn -> TWEAK

    # OUT_VERSION without the 'b' => x.y.z.n
    set(_out_version "${_maj}.${_min}.${_pat}.${_tweak}")
    elseif(_cz_raw_version MATCHES "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$")
    set(_maj   "${CMAKE_MATCH_1}")
    set(_min   "${CMAKE_MATCH_2}")
    set(_pat   "${CMAKE_MATCH_3}")
    set(_tweak "0")
    set(_out_version "${_maj}.${_min}.${_pat}")
    else()
    message(FATAL_ERROR
        "cz_extract_project_version: Unsupported version format '${_cz_raw_version}'. "
        "Expected 'xx.yy.zz' or 'xx.yy.zz-bn'."
    )
    endif()

    # Export OUT_VERSION
    set(${OUT_VERSION} "${_out_version}" PARENT_SCOPE)
endfunction()
