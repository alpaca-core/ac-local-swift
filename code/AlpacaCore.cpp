// Copyright (c) Alpaca Core
// SPDX-License-Identifier: MIT
//
#include "AlpacaCore.hpp"
#include "Model.hpp"

#include <ac/local/Instance.hpp>
#include <ac/local/Model.hpp>
#include <ac/local/Lib.hpp>
#include <ac/local/ModelLoaderRegistry.hpp>
#include <ac/local/PluginManager.hpp>

#include <ac/jalog/Instance.hpp>
#include <ac/jalog/sinks/DefaultSink.hpp>

#include "aclp-dummy-plib.hpp"

namespace AC {

void initSDK() {
    ac::jalog::Instance jl;
    jl.setup().add<ac::jalog::sinks::DefaultSink>();

    add_dummy_to_ac_local_registry(ac::local::Lib::modelLoaderRegistry());
}

Expected<Model, std::string> createModel(AlpacaCoreSwift::ModelDesc& desc, DictRef params, ProgressCallbackData progressCbData) {
    ac::local::ModelDesc modelDesc;
    modelDesc.inferenceType = desc.getInferenceType();
    modelDesc.name = desc.getName();

    for (auto asset : desc.getAssets()) {
        ac::local::ModelDesc::AssetInfo assetInfo;
        assetInfo.path = asset.getPath();
        assetInfo.tag = asset.getTag();
        modelDesc.assets.push_back(assetInfo);
    }
    auto& registry = ac::local::Lib::modelLoaderRegistry();

    try {
        if (progressCbData.m_cb) {
            return Model(registry.createModel(modelDesc, params.getDict(), [&](std::string_view tag, float progress) {
                progressCbData.m_cb(progressCbData.m_context, tag.data(), tag.data() + tag.size(), progress);
                return true;
            }));
        }
        else {
            return Model(registry.createModel(modelDesc, params.getDict()));
        }
    }
    catch(const std::exception& e)
    {
        return itlib::unexpected<std::string>(e.what());
    }
}

void loadPlugin(const std::string& path) {
    ac::local::Lib::loadPlugin(path);
}
void addPluginDir(const std::string& path) {
    ac::local::Lib::addPluginDir(path);
}
void addPluginDirsFromEnv(const std::string& envVar) {
    ac::local::Lib::addPluginDirsFromEnvVar(envVar);
}
void loadAllPlugins() {
    ac::local::Lib::loadAllPlugins();
}

}
