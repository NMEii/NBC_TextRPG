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

    // 레벨 업
    buffers[SFXType::LevelUp].loadFromFile("Audio/SFX/pokemon-Level-up-Sound.ogg");

    // 체력 회복
    buffers[SFXType::Heal].loadFromFile("Audio/SFX/Heal.mp3");

    // 피격
    buffers[SFXType::Damaged].loadFromFile("Audio/SFX/snd_damage.wav");

    // 구멍파기
    buffers[SFXType::Dig].loadFromFile("Audio/SFX/Skill/Dig.mp3");

    // 몸통박치기
    buffers[SFXType::Tackle].loadFromFile("Audio/SFX/Skill/Tackle.mp3");

    // 울음소리
    buffers[SFXType::Growl].loadFromFile("Audio/SFX/Skill/Growl.mp3");

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
    //const string& path = ChoiceBGM(type);
    //bgm.openFromFile(path);
    //bgm.setLoop(true);
    //bgm.setVolume(volume);
    //bgm.play();
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
    //sf::Sound sound(buffers[type]);
    //sound.play();
    //playingSounds.push_back(sound);
}

void AudioManager::Tick()
{
    for (auto it = playingSounds.cbegin(); it != playingSounds.cend(); ++it)
    {
        if (it->getStatus() != sf::Sound::Playing)
        {
            it = playingSounds.erase(it);
        }
        else
        {
            ++it;
        }
    }
}


