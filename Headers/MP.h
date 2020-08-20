#ifndef LOAD_AUDIO_H_
#define LOAD_AUDIO_H_
#include <SFML/Audio.hpp>
#include <map>

class MP //Music Player
{
public:
    MP();
    ~MP();
    void Load();
    void PlaySE();
    void PlayMusic(sf::Music *music, bool isLoop);
    void PlayMusic(int musicID, bool isLoop);
    sf::Music* GetPlayingMusic(int musicID);
    int GetPlayingMusicID();
    float GetCurrentPlayingMusicOffSetInSec();
    sf::Time GetCurrentPlayingMusicOffSet();
    void SetBPMForSelectedMusic(int musicID, float newBPM);
    float GetBPMForSelectedMusic(int musicID);
    int GetMusicTitleText(int musicID);
    std::vector<int> GetMusicTitles();
    int GetTotalNumOfMusicTracks();
    bool WindowOfInput();
    float BeatTime();

private:
    int currentPlayingMusic;
    std::map<int, sf::Music> musicMap;
    std::map<int, float> musicBPMMap;
    std::vector<int> musicTitles_;
};

#endif