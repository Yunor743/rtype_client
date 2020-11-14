#include "SfmlAudioModule.hpp"
#include <SFML/Audio.hpp>

SfmlAudioModule::SfmlAudioModule(const std::filesystem::path &asset_location)
    : m_asset_location(asset_location)
{
}

void SfmlAudioModule::update()
{
}

void SfmlAudioModule::playSound(const std::string &name, float volume,
                                float pitch)
{
    sf::Music &asset = this->getSound(m_asset_location / name);

    asset.setVolume(volume * 100);
    asset.setPitch(pitch);
    asset.stop();
    asset.play();
}

sf::Music &SfmlAudioModule::getSound(const std::filesystem::path &asset_path)
{
    auto [value, success] = m_cached_assets.try_emplace(asset_path);
    auto &[key, asset] = *value;

    if (!success) {
        return asset;
    }

    if (!asset.openFromFile(asset_path)) {
        throw SfmlAudioError("could not load asset " + asset_path.string());
        // throw std::runtime_error("Could not load music " + asset_path.string());
    }
    return asset;
}

SfmlAudioError::SfmlAudioError(const std::string &error)
    : AudioError("SfmlAudioModule error: " + error)
{
}
