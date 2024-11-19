# Copyright (c) Alpaca Core
# SPDX-License-Identifier: MIT
#
CPMAddPackage(
  NAME ac-test-data-whisper
  VERSION 1.0.0
  GIT_REPOSITORY https://huggingface.co/alpaca-core/ac-test-data-whisper
  GIT_TAG f33d981742198f2b55494265fc9d43156b39a30d
)
CPMAddPackage(gh:alpaca-core/helper-audio@1.0.0)
make_ac_local_plugin_available(
    NAME ilib-whisper.cpp
    VERSION 1.0.0
    GITHUB alpaca-core/ilib-whisper.cpp
)

function(ac_add_swift_executable target)
    add_executable(${target} ${ARGN})

    # generate a valid swift module name
    string(REPLACE - _ moduleName ${target})

    set_target_properties(${target} PROPERTIES
    	COMPILE_OPTIONS ""
    	Swift_MODULE_NAME ${moduleName}
   	)
    target_link_libraries(${target}
      PRIVATE
        AlpacaCoreSwift
        ExampleDataSwift
    )
    target_compile_options(${target}
      PRIVATE
        $<$<COMPILE_LANGUAGE:Swift>:-cxx-interoperability-mode=default -Xcc -std=c++20>
    )
    # Used to find modulemaps
    target_include_directories(${target}
      PRIVATE
        .
    )
    target_compile_options(${target} PRIVATE -parse-as-library)
endfunction()

function(ac_swift_example name)
    ac_add_swift_executable(example-ac-swift-${name} ${ARGN})
endfunction()

add_library(ExampleDataSwift STATIC
    ac-example-data-swift.cpp
)

target_link_libraries(ExampleDataSwift
    PRIVATE
        ac-test-data-whisper
        ac-dev::audio
        aclp::out-dir
)

ac_swift_example(Sandbox e-Sandbox.swift)
ac_swift_example(Whisper e-Whisper.swift)
ac_swift_example(Dummy e-Dummy.swift)
