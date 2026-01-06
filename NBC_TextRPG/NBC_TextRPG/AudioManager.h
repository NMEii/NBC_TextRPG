#pragma once

using namespace std;

// SFX 타입
enum SFXType
{
    Select,     // 선택 사운드
    LevelUp,    // 레벨업 사운드
    Heal,       // 회복 사운드
    Damaged,    // 피격 사운드

    Dig,        // 구멍파기     음원이 길어서 속도를 올리든 딜레이걸든 해야할거 같음.
    Tackle,     // 몸통박치기
    Growl       // 울음소리
};

enum BGMType
{
    None,
    MainThema,      // 전투 BGM
    BattleThema,    // 상점 BGM
    ShopThema,      // 상점 BGM
    BossThema,      // 보스 BGM
    EndingThema     // 엔딩 크레딧 BGM
};

class AudioManager
{
public:
    
    static AudioManager& Get()
    {
        static AudioManager instance;
        return instance;
    }

    // 오디오 생성
    void InitSound();  

    // BGM 재생
    void PlayBGM(const BGMType type, float volume);

    // BGM 정지
    void StopBGM();

    // BGM 선택
    string ChoiceBGM(BGMType type);
    
    // SFX 재생
    void PlaySFX(SFXType type, float volume);

private:
    // 생성자
    AudioManager(); 
    
    sf::Music bgm;

    map<SFXType, sf::SoundBuffer> buffers;
    map<SFXType, std::vector<sf::Sound>> pools;

    vector<sf::Sound> playingSounds;
    BGMType currentBGM = BGMType::None;
};

