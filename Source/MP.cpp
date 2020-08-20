#include <fstream>
#include <math.h>
#include "../Headers/MP.h"
#include "../Headers/LP.h"
using namespace std;
using namespace sf;

MP::MP()
{}

MP::~MP()
{}

void MP::Load()
{
    musicMap[0].openFromFile("../Resources/Audio/Remember Passion Beat.ogg");
    musicMap[1].openFromFile("../Resources/Audio/Necro funk the around.ogg");
    musicMap[2].openFromFile("../Resources/Audio/Adjust.ogg");
    musicMap[3].openFromFile("../Resources/Audio/Southern Arena.ogg");
    musicMap[4].openFromFile("../Resources/Audio/Nothing Can Stop Us Now.ogg");
    musicMap[5].openFromFile("../Resources/Audio/Fight For Your Life.ogg");
    musicMap[6].openFromFile("../Resources/Audio/Amaryllis.flac");
    musicMap[7].openFromFile("../Resources/Audio/Ayahuasca.flac");
    musicMap[8].openFromFile("../Resources/Audio/Ceramic Summer.ogg");
    musicMap[9].openFromFile("../Resources/Audio/La Tropica.ogg");
    musicMap[10].openFromFile("../Resources/Audio/moonshade_.flac");
    musicMap[11].openFromFile("../Resources/Audio/Reconfig.ogg");
    musicMap[12].openFromFile("../Resources/Audio/Gain Therapy Edit.ogg");

    fstream data("../Resources/Data/BPM.txt");
    char dummy;
    int ID;
    do
    {
        data >> dummy;
        if (dummy == '+')
        {
            data >> ID;
            data >> dummy;
            data >> musicBPMMap[ID];
        }
    } while (dummy != '!');
    data.close();

    musicTitles_.push_back(LP::SetText("Remember_Passion_Beat", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Necro_Funk_the_Around", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Adjust", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Southern_Arena", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Nothing Can Stop Us Now", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Fight For Your Life", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Amaryllis", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Ayahuasca", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Ceramic Summer", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("La Tropica", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("moonshade_", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Reconfig", Vector2f(512, 128), 16));
    musicTitles_.push_back(LP::SetText("Gain Therapy", Vector2f(512, 128), 16));
    for (auto i : musicTitles_) LP::SetTextOriginCenter(i);
}

void MP::PlaySE()
{}

void MP::PlayMusic(Music *music, bool isLoop)
{
    music->setLoop(isLoop);
    music->play();
}

void MP::PlayMusic(int musicID, bool isLoop)
{
    if (Music::Playing)
    {
        musicMap[currentPlayingMusic].stop();
    }
    musicMap[musicID].setLoop(isLoop);
    musicMap[musicID].play();
    currentPlayingMusic = musicID;
}

Music* MP::GetPlayingMusic(int musicID)
{
    return &musicMap[musicID];
}

int MP::GetPlayingMusicID()
{
    return currentPlayingMusic;
}

float MP::GetCurrentPlayingMusicOffSetInSec()
{
    return musicMap[currentPlayingMusic].getPlayingOffset().asSeconds();
}

Time MP::GetCurrentPlayingMusicOffSet()
{
    return musicMap[currentPlayingMusic].getPlayingOffset();
}

void MP::SetBPMForSelectedMusic(int musicID, float newBPM)
{
    musicBPMMap[musicID] = newBPM;

    fstream data("../Resources/Data/BPM.txt");
    ofstream temp("../Resources/Data/Temp.txt");
    char dummy;
    int ID;
    float dummyNum;
    while(dummy != '!')
    {
        data >> dummy; //move '+'
        temp << dummy;
        if (dummy == '!') break;
        data >> ID; //move ID
        temp << ID;
        data >> dummy; //move ','
        temp << dummy;
        data >> dummyNum; //replace BPM
        temp << musicBPMMap[ID] << endl;
    }
    data.close();
    temp.close();
    remove("../Resources/Data/BPM.txt");
    rename("../Resources/Data/Temp.txt", "../Resources/Data/BPM.txt");
}

float MP::GetBPMForSelectedMusic(int musicID)
{
    return musicBPMMap[musicID];
}

int MP::GetMusicTitleText(int musicID)
{
    return musicTitles_[musicID];
}

std::vector<int> MP::GetMusicTitles()
{
    return musicTitles_;
}

int MP::GetTotalNumOfMusicTracks()
{
    return musicTitles_.size();
}

bool MP::WindowOfInput()
{
    // int deviatedTimeFromBeat = GetCurrentPlayingMusicOffSetInSec() % musicBPMMap[currentPlayingMusic];
    // if (deviatedTimeFromBeat >= 0 && deviatedTimeFromBeat <= musicBPMMap[currentPlayingMusic] / 2) return true;
    // else return false;
    return false;
}

float MP::BeatTime()
{
    return fmod(GetCurrentPlayingMusicOffSetInSec(), GetBPMForSelectedMusic(GetPlayingMusicID()));
}