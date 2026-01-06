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
    const string& path = ChoiceBGM(type);
    bgm.openFromFile(path);
    bgm.setLoop(true);
    bgm.setVolume(volume);
    bgm.play();
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
        //case BattleThema:
        //    File = 
        //    break;
    case ShopThema:
        File = "Audio/BGM/Pokemon-Center-Theme.ogg";
        break;
        //case BossThema:
        //    File = 
        //    break;
    case EndingThema:
        File = "Audio/BGM/mus_xpart_b.ogg";
        break;
    }
    return File;
}

void AudioManager::PlaySFX(SFXType type, float volume)
{
    sf::Sound sound(buffers[type]);
    sound.play();
    playingSounds.push_back(sound);
}

void AudioManager::Tick()
{
    endSoundIndexes.clear();

    for (int i = 0; i < playingSounds.size(); i++)
    {
        if (playingSounds[i].getStatus() != sf::Sound::Playing)
        {
            endSoundIndexes.push_back(i);
        }
    }

    for (int eraseIndex : endSoundIndexes)
    {
        playingSounds.erase(playingSounds.begin() + eraseIndex);
    }
}