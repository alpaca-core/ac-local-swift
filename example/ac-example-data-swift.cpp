
// Copyright (c) Alpaca Core
// SPDX-License-Identifier: MIT
//
// #include "../../../gen/ac-test-data-llama-dir.h"

#include <ac-test-data-whisper-dir.h>
#include <ac-audio.hpp>

#include <aclp-out-dir.h>

namespace AC {

const char* getWhisperDir() {
    return AC_TEST_DATA_WHISPER_DIR;
}

// const char* getLlamaDir() {
//     return AC_TEST_DATA_LLAMA_DIR;
// }


const char* getPluginsDir() {
    return ACLP_OUT_DIR;
}

std::vector<float> loadWavF32Mono(const std::string& path) {
    return ac::audio::loadWavF32Mono(path);
}

}
