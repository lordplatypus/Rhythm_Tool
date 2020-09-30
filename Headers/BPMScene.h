#ifndef SET_BPM_SCENE_H_
#define SET_BPM_SCENE_H_
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "MP.h"
#include "Game.h"
#include "UIManager.h"

class BPMScene : public Scene
{
public:
    BPMScene(Game* game, MP* mp);
    ~BPMScene() override;
    virtual void Init() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    virtual void End() override;

private:
    void ImportSPB();
    void MainMenu();
    void MusicSelectMenu();
    void BPMSetUp();
    void MusicPlayBack(float delta_time, float beat_time);
    void SaveBPMForSelectedSong();

private:
    //Background
    int background;

    //enum for states
    enum State {Menu, MusicSelect, SetUp, PlayBack, Save};
    State state = Menu;

    //Menu Text
    std::vector<int> menu;
    int selectedOption = 0;
    int setupInstructions;
    //int playbackInstructions;
    int savedText;
    int displayMusicTitle;
    int displayBeatsPerMin;
    int displaySecPerBeat;
    int displayBeatTimer;
    int displayBeatCount;

    float alpha{0};

    //Music Select
    std::vector<int> musicTitles;//for the verticle menu
    int musicID = 0;
    int selectedMusicID = 0;

    //Numbers
    std::vector<float> listOfBeats;
    float beatsPerMin{0};
    float secPerBeat{0};
    float beatTimer{0};
    float zeroOutTime{0};
    int count{0};

    std::unordered_map<int, float> MusicSPBMap;

    //Play Back
    std::vector<int> playerSprite;
    std::vector<int> heartSprite;

    //for Player
    float timer{0};
    float timeInbetweenFrames{0};
    int animCount = 0;

    //For heart
    int heartCount{0};
    bool oneTime{false};

    bool pressedUp = false;
    bool pressedDown = false;
    bool pressedRight = false;
    bool pressedLeft = false;
    bool pressedZ = true;
    bool pressedX = true;

    bool firstTime = true;

    MP* mp_ {nullptr};
    Game* game_ {nullptr};
    UIManager ui_;
};

#endif