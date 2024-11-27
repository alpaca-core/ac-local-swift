# Copyright (c) Alpaca Core
# SPDX-License-Identifier: MIT
#
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

if(POLICY CMP0157)
	# enable proper Swift incremental building with ninja
	# this is the default for cmake 3.29, but the issue doesn't warrant bumping min required
	cmake_policy(SET CMP0157 NEW)
endif()

project(ac-local-swift
    VERSION 1.0.0
    DESCRIPTION "Swift wrapper for the Alpaca Core Local SDK"
    LANGUAGES Swift CXX
)

include(./get-ac-build.cmake)
include(init_ac_prj)

#################
# options

option(AC_LOCAL_SWIFT_BUILD_TESTS "${PROJECT_NAME}: build tests" ${testsDefault})
option(AC_LOCAL_SWIFT_BUILD_EXAMPLES "${PROJECT_NAME}: build examples" ${examplesDefault})
mark_as_advanced(AC_LOCAL_SWIFT_BUILD_TESTS AC_LOCAL_SWIFT_BUILD_EXAMPLES)

#######################################
# packages

include(ac_build_prj_util)
add_ac_local(0.1.3)
CPMAddPackage(gh:iboB/itlib@1.11.4)

#######################################
# cfg

if(sanitizerFlags)
    # TODO: #159
    message(FATAL_ERROR "${CMAKE_PROJECT_NAME}: Can't configure Swift wrapper. \
        The project is configured with '${sanitizerFlags}'. swiftc cannot does not understand them. ")
endif()

if(CMAKE_Swift_COMPILER_VERSION VERSION_LESS "6.0")
    message(FATAL_ERROR "${CMAKE_PROJECT_NAME}: Can't configure Swift wrapper. "
        "Swift version must be at least 6.0. Found: ${CMAKE_Swift_COMPILER_VERSION}")
endif()

add_subdirectory(code)

if(AC_LOCAL_SWIFT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

if(AC_LOCAL_SWIFT_BUILD_TESTS)
    add_subdirectory(example)
endif()
