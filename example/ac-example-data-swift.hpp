// Copyright (c) Alpaca Core
// SPDX-License-Identifier: MIT
//
#pragma once

#include <vector>
#include <string>

namespace AC {

const char* getWhisperDir();

// const char* getLlamaDir();

const char* getPluginsDir();

std::vector<float> loadWavF32Mono(const std::string& path);

}
