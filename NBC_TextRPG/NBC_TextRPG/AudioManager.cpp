#include "pch.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
    InitSound();
}

void AudioManager::InitSound()
{
    // 선택음 설정
    buffers[SFXType::Select].loadFromFile("Audio/SFX/snd_select.wav");
    pools[SFXType::Select].resize(4);
    for (auto& s : pools[SFXType::Select])
    {
        s.setBuffer(buffers[SFXType::Select]);
    }

    // 레벨 업
    buffers[SFXType::LevelUp].loadFromFile("Audio/SFX/pokemon-Level-up-Sound.ogg");
    pools[SFXType::LevelUp].resize(4);
    for (auto& s : pools[SFXType::LevelUp])
    {
        s.setBuffer(buffers[SFXType::LevelUp]);
    }

    // 체력 회복
    buffers[SFXType::Heal].loadFromFile("Audio/SFX/Heal.mp3");
    pools[SFXType::Heal].resize(4);
    for (auto& s : pools[SFXType::Heal])
    {
        s.setBuffer(buffers[SFXType::Heal]);
    }

    // 피격
    buffers[SFXType::Damaged].loadFromFile("Audio/SFX/snd_damage.wav");
    pools[SFXType::Damaged].resize(4);
    for (auto& s : pools[SFXType::Damaged])
    {
        s.setBuffer(buffers[SFXType::Damaged]);
    }

    // 구멍파기
    buffers[SFXType::Dig].loadFromFile("Audio/SFX/Skill/Dig.mp3");
    pools[SFXType::Dig].resize(4);
    for (auto& s : pools[SFXType::Dig])
    {
        s.setBuffer(buffers[SFXType::Dig]);
    }

    // 몸통박치기
    buffers[SFXType::Tackle].loadFromFile("Audio/SFX/Skill/Tackle.mp3");
    pools[SFXType::Tackle].resize(4);
    for (auto& s : pools[SFXType::Tackle])
    {
        s.setBuffer(buffers[SFXType::Tackle]);
    }

    // 울음소리
    buffers[SFXType::Growl].loadFromFile("Audio/SFX/Skill/Growl.mp3");
    pools[SFXType::Growl].resize(4);
    for (auto& s : pools[SFXType::Growl])
    {
        s.setBuffer(buffers[SFXType::Growl]);
    }
}

void AudioManager::PlayBGM(const BGMType type, float volume)
{
    if (bgm.getStatus() == sf::Music::Playing && currentBGM == type)
    {
        return;
    }

    bgm.stop();

    const std::string& path = ChoiceBGM(type);
    if (!bgm.openFromFile(path))
        return;

    bgm.setLoop(true);
    bgm.setVolume(volume);
    bgm.play();

    currentBGM = type;
}

void AudioManager::StopBGM()
{
    bgm.stop();
}

string AudioManager::ChoiceBGM(BGMType type)
{
    string File = "";
    switch (type)
    {
    case MainThema:
        File = "Audio/BGM/mus_shop.ogg";
        break;
    case BattleThema:
        File = "Audio/BGM/Battle.ogg";
        break;
    case ShopThema:
        File = "Audio/BGM/Pokemon-Center-Theme.ogg";
        break;
    case BossThema:
        File = "Audio/BGM/Afterglow.ogg";
        break;
    case EndingThema:
        File = "Audio/BGM/StartOfLegend.ogg";
        break;
    }
    return File;
}

void AudioManager::PlaySFX(SFXType type, float volume)
{
    playingSounds.emplace_back();                 // 빈 Sound 생성
    sf::Sound& sound = playingSounds.back();      // 참조
    sound.setBuffer(buffers[type]);
    sound.setVolume(volume);
    sound.play();
}

