#ifndef RTYPE_SFML_AUDIO_MODULE_H_
#define RTYPE_SFML_AUDIO_MODULE_H_

#include "Modules.hpp"
#include <SFML/Audio.hpp>

#include <filesystem>

class SfmlAudioModule : public IAudioModule
{
  public:
    SfmlAudioModule(const std::filesystem::path &asset_location = ".");

    void update() override;
    void playSound(const std::string &name, float volume, float pitch) override;

  private:
    sf::Music &getSound(const std::filesystem::path &asset_path);

    std::filesystem::path m_asset_location;
    std::unordered_map<std::string, sf::Music> m_cached_assets;
};

class SfmlAudioError : public AudioError
{
  public:
    SfmlAudioError(const std::string &error);
};

#endif // RTYPE_SFML_AUDIO_MODULE_H_
