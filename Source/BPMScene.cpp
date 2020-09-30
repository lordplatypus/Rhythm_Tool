#include <fstream>
#include <math.h>
#include "../Headers/BPMScene.h"
#include "../Headers/LP.h"
#include "../Headers/TextureID.h"
using namespace std;
using namespace sf;

BPMScene::BPMScene(Game* game, MP* mp) : game_{game}, mp_{mp} 
{}

BPMScene::~BPMScene()
{}

void BPMScene::Init()
{
    //Create Text for the main menu (メインメニューのテクストを設定する)
    menu.push_back(LP::SetText("Choose Music", Vector2f(256, 256), 16));
    menu.push_back(LP::SetText("Start BPM Setup", Vector2f(256, 256), 16));
    menu.push_back(LP::SetText("Start Playback", Vector2f(256, 256), 16));
    menu.push_back(LP::SetText("Save Changes", Vector2f(256, 256), 16));
    menu.push_back(LP::SetText("Quit", Vector2f(256, 256), 16));
    for (auto i : menu) LP::SetTextOriginCenter(i); //set the origin to the center (テクストの原点を設定する)

    //Duplicate the music titles (text) from the MP class
    for (int i = 0; i < mp_->GetTotalNumOfMusicTracks(); i++) musicTitles.push_back(LP::SetText(mp_->GetMusicTitle(i), Vector2f(0.0f, 0.0f), 16));
    for (auto i : musicTitles) LP::SetTextOriginCenter(i);

    //Verticle menu setup ()
    ui_.AddUIText(Vector2f(275, 183), menu.size(), menu, 0, 3, 1, 32); //set up a verticle menu for the main menu ()
    ui_.AddUIText(Vector2f(803, 183), musicTitles.size(), musicTitles, 1, 5, 2, 32); //set up a verticle menu for song titles ()
    ui_.SetDisplay("Text", 1, false); //song titles start off hidden ()

    //Set up the rest of the text used (残るテクストを設定する)
    setupInstructions = LP::SetText("Z to start,\n\nDown to time beats,\n\nX to return", Vector2f(584+16, 88+16), 16);
    savedText = LP::SetText("Saved", Vector2f(803, 183), 16);
    LP::SetTextOriginCenter(savedText);
    displayMusicTitle = LP::SetText("Music Title: NA", Vector2f(96, 448), 16);
    displayBeatsPerMin = LP::SetText("Beats Per Min: NA", Vector2f(96, 480), 16);
    //secPerBeat = mp_->GetBPMForSelectedMusic(musicID);
    displaySecPerBeat = LP::SetText("Beats Per Sec: NA", Vector2f(96, 512), 16);
    displayBeatTimer = LP::SetText("0", Vector2f(96, 544), 16);
    displayBeatCount = LP::SetText("0", Vector2f(96, 576), 16);

    //setup background picture ()
    background = LP::SetSprite(BPMSceneTexture, Vector2f(0, 0));

    //setup sprites used for timing (スプライトを設定する)
    heartSprite = LP::SetSprite(heartTexture, 16, 16, 2, 1); //heart sprite (ハートのスプライト)
    for (auto i : heartSprite) 
    {
        LP::SetSpriteScale(i, 8, 8); //set heart sprite scale ()
        LP::SetSpriteOriginCenter(i);
    }
    playerSprite = LP::SetSprite(robokoTexture, 32, 32, 6, 1); //char sprite (キャラクターのスプライト)
    for (auto i : playerSprite) 
    {
        LP::SetSpriteScale(i, 6, 6); //set char sprite scale ()
        LP::SetSpriteOriginCenter(i);
    }

    //Import data into "MusicSPBMap"
    ImportSPB();
}

void BPMScene::ImportSPB()
{
    fstream data("./Resources/Data/BPM.txt");
    char dummy;
    int ID;
    do
    {
        data >> dummy;
        if (dummy == '+')
        {
            data >> ID;
            data >> dummy;
            data >> MusicSPBMap[ID];
        }
    } while (dummy != '!');
    data.close();
}

void BPMScene::Update(float delta_time, float beat_time)
{
    if (state == Menu)
    {//Main menu (マインメニュー)
        MainMenu();
    }
    else if (state == MusicSelect)
    {//Music select (音楽選択)
        MusicSelectMenu();
    }
    else if (state == SetUp)
    {//Setup the BPM for selected song (選択した音楽のBPMを設定する)
        BPMSetUp();
    }
    else if (state == PlayBack)
    {//Play back the selected song
        MusicPlayBack(delta_time, beat_time);
    }
    else if (state == Save)
    {//save new BPM
        SaveBPMForSelectedSong();
    }

    //for 'saved' text fade out
    if (alpha > 0) 
    {
        alpha -= 200 * delta_time;
        LP::SetTextColor(savedText, 255, 255, 255, alpha);
    }
    else alpha = 0;

    //UI update
    ui_.Update(delta_time, beat_time);

    //one activation per one button press
    if (!Keyboard::isKeyPressed(Keyboard::Z)) pressedZ = false;
    if (!Keyboard::isKeyPressed(Keyboard::X)) pressedX = false;
    if (!Keyboard::isKeyPressed(Keyboard::Up)) pressedUp = false;
    if (!Keyboard::isKeyPressed(Keyboard::Down)) pressedDown = false;
    if (!Keyboard::isKeyPressed(Keyboard::Left)) pressedLeft = false;
    if (!Keyboard::isKeyPressed(Keyboard::Right)) pressedRight = false;
}

void BPMScene::MainMenu()
{
    if (!pressedUp && Keyboard::isKeyPressed(Keyboard::Up))
    {
        selectedOption--;
        if (selectedOption < 0) selectedOption = menu.size() - 1;
        ui_.ScrollDown(0);
        pressedUp = true;
    }
    if (!pressedDown && Keyboard::isKeyPressed(Keyboard::Down))
    {
        selectedOption++;
        if (selectedOption > menu.size() - 1) selectedOption = 0;
        ui_.ScrollUp(0);
        pressedDown = true;
    }
    if (!pressedZ && Keyboard::isKeyPressed(Keyboard::Z))
    {
        if (selectedOption == 0) 
        {
            state = MusicSelect;
            ui_.SetDisplay("Text", 1, true);
        }
        if (selectedOption == 1) state = SetUp;
        if (selectedOption == 2) state = PlayBack;
        if (selectedOption == 3) state = Save;
        if (selectedOption == 4) ;
        pressedZ = true;
    }
}

void BPMScene::MusicSelectMenu()
{
    if (!pressedUp && Keyboard::isKeyPressed(Keyboard::Up))
    {
        musicID--;
        if (musicID < 0) musicID = musicTitles.size() - 1;
        ui_.ScrollDown(1);
        pressedUp = true;
    }
    if (!pressedDown && Keyboard::isKeyPressed(Keyboard::Down))
    {
        musicID++;
        if (musicID > musicTitles.size() - 1) musicID = 0;
        ui_.ScrollUp(1);
        pressedDown = true;
    }
    if (!pressedZ && Keyboard::isKeyPressed(Keyboard::Z))
    {
        selectedMusicID = musicID;

        LP::SetNewText(displayMusicTitle, mp_->GetMusicTitle(selectedMusicID));
        LP::SetNewText(displayBeatsPerMin, "Beats Per Min: " + to_string((int)round(60 / MusicSPBMap[musicID])));
        LP::SetNewText(displaySecPerBeat, "Beats Per Sec: " + to_string(MusicSPBMap[selectedMusicID]));
        LP::SetNewText(displayBeatTimer, "Beat Time: 0");
        LP::SetNewText(displayBeatCount, "Beat Count: 0");

        state = Menu;
        ui_.SetDisplay("Text", 1, false);
        pressedZ = true;
    }
    if (!pressedX && Keyboard::isKeyPressed(Keyboard::X))
    {
        musicID = selectedMusicID;
        state = Menu;
        ui_.SetDisplay("Text", 1, false);
        pressedX = true;
    }
}

void BPMScene::BPMSetUp()
{
    if (!pressedZ && Keyboard::isKeyPressed(Keyboard::Z))
    {//reset variables
        mp_->PlayMusic(musicID, false);
        pressedZ = true;
        secPerBeat = 0;
        beatsPerMin = 0;
        beatTimer = 0;
        zeroOutTime = 0;
        count = 0;
        listOfBeats.clear();
    }

    if (!pressedDown && Keyboard::isKeyPressed(Keyboard::Down))
    {
        if (firstTime == true)
        {
            zeroOutTime = mp_->GetCurrentPlayingMusicOffSetInSec();
            firstTime = false;
        }
        else
        { 
            beatTimer = mp_->GetCurrentPlayingMusicOffSetInSec() - zeroOutTime;
            zeroOutTime = mp_->GetCurrentPlayingMusicOffSetInSec();

            listOfBeats.push_back(beatTimer);
            //secPerBeat = 0;
            MusicSPBMap[musicID] = 0;
            //for (auto i : listOfBeats) secPerBeat += i;
            for (auto i : listOfBeats) MusicSPBMap[musicID] += i;
            //secPerBeat /= listOfBeats.size(); //average time inbetween beats
            MusicSPBMap[musicID] /= listOfBeats.size();
            //if (secPerBeat != 0) beatsPerMin = (int)round(60 / secPerBeat); //BPM
            if (MusicSPBMap[musicID] != 0) 
            {
                beatsPerMin = round(60 / MusicSPBMap[musicID]);
                secPerBeat = MusicSPBMap[musicID];
                LP::SetNewText(displayBeatsPerMin, "Beats Per Min: " + to_string((int)beatsPerMin));
                LP::SetNewText(displaySecPerBeat, "Beats Per Sec: " + to_string(secPerBeat));
            }
        }

        pressedDown = true;
        count++; //for beat count
    }

    if (!pressedX && Keyboard::isKeyPressed(Keyboard::X))
    {
        firstTime = true;
        state = Menu;
        pressedX = true;
    }
}

void BPMScene::MusicPlayBack(float delta_time, float beat_time)
{
    if (!pressedUp && Keyboard::isKeyPressed(Keyboard::Up))
    {
        MusicSPBMap[musicID] = 60 / (60 / MusicSPBMap[musicID] + 1);
        secPerBeat = MusicSPBMap[musicID];
        beatsPerMin = (int)round(60 / MusicSPBMap[musicID]);
        timeInbetweenFrames = MusicSPBMap[musicID] / 10;
        LP::SetNewText(displayBeatsPerMin, "Beats Per Min: " + to_string((int)round(60 / MusicSPBMap[musicID])));
        LP::SetNewText(displaySecPerBeat, "Beats Per Sec: " + to_string(MusicSPBMap[selectedMusicID]));
        pressedUp = true;
    }
    if (!pressedDown && Keyboard::isKeyPressed(Keyboard::Down))
    {
        MusicSPBMap[musicID] = 60 / (60 / MusicSPBMap[musicID] - 1);
        secPerBeat = MusicSPBMap[musicID];
        beatsPerMin = (int)round(60 / MusicSPBMap[musicID]);
        timeInbetweenFrames = MusicSPBMap[musicID] / 10;
        LP::SetNewText(displayBeatsPerMin, "Beats Per Min: " + to_string((int)round(60 / MusicSPBMap[musicID])));
        LP::SetNewText(displaySecPerBeat, "Beats Per Sec: " + to_string(MusicSPBMap[selectedMusicID]));
        pressedDown = true;
    }

    if (firstTime)
    {//reset variables
        mp_->PlayMusic(musicID, false);
        secPerBeat = mp_->GetBPMForSelectedMusic(musicID);
        beatsPerMin = (int)round(60 / MusicSPBMap[musicID]);
        animCount = 0;
        count = 0;
        timeInbetweenFrames = secPerBeat / 10;
        LP::SetNewText(displayBeatsPerMin, "Beats Per Min: " + to_string((int)round(60 / MusicSPBMap[musicID])));
        LP::SetNewText(displaySecPerBeat, "Beats Per Sec: " + to_string(MusicSPBMap[selectedMusicID]));
        firstTime = false;
    }

    beatTimer = fmod(mp_->GetCurrentPlayingMusicOffSetInSec(), MusicSPBMap[musicID]);
    //beatTimer = beat_time;

    //Heart Animation
    if (oneTime && beatTimer <= timeInbetweenFrames)
    {
        if (heartCount == 0) heartCount = 1;
        else heartCount = 0;
        oneTime = false;
        count++;
    }
    else if (beatTimer > timeInbetweenFrames) oneTime = true;

    //Player Animation
    timer += delta_time;
    if (beatTimer <= timeInbetweenFrames) animCount = 0;     
    else if (animCount != 5 && timer >= timeInbetweenFrames) 
    {
        animCount++;
        timer = 0;
    }

    if (!pressedX && Keyboard::isKeyPressed(Keyboard::X))
    {
        count = 0;
        LP::SetNewText(displayBeatTimer, "Beat Time: 0");
        LP::SetNewText(displayBeatCount, "Beat Count: 0");
        firstTime = true;
        state = Menu;
        pressedX = true;
    }
}

void BPMScene::SaveBPMForSelectedSong()
{
    // secPerBeat = 0;
    // if (listOfBeats.size() != 0)
    // {
    //     for (auto i : listOfBeats) secPerBeat += i;
    //     secPerBeat /= listOfBeats.size(); //average time inbetween beats
    // }
    // if (secPerBeat != 0)
    // {
    //     mp_->SetBPMForSelectedMusic(musicID, secPerBeat);
    //     alpha = 255; //for 'saved' text fade out
    // }

    if (MusicSPBMap[musicID] != 0)
    {
        mp_->SetBPMForSelectedMusic(musicID, MusicSPBMap[musicID]);
        alpha = 255;
    }
    state = Menu;
}

void BPMScene::Draw()
{
    //Draw Background
    LP::DrawSprite(background);

    //Draw different things at different states
    if (state == Menu)
    {
        LP::DrawText(displayMusicTitle);
        LP::DrawText(displayBeatsPerMin);
        LP::DrawText(displaySecPerBeat);
        LP::DrawText(displayBeatTimer);
        LP::DrawText(displayBeatCount);

        LP::DrawSprite(playerSprite[0], Vector2f(901, 535));
        LP::DrawSprite(heartSprite[0], Vector2f(705, 535));
    }

    else if (state == MusicSelect)
    {
        LP::DrawText(displayMusicTitle);
        LP::DrawText(displayBeatsPerMin);
        LP::DrawText(displaySecPerBeat);
        LP::DrawText(displayBeatTimer);
        LP::DrawText(displayBeatCount);

        LP::DrawSprite(playerSprite[0], Vector2f(901, 535));
        LP::DrawSprite(heartSprite[0], Vector2f(705, 535));
    }

    else if (state == SetUp)
    {
        LP::DrawText(setupInstructions);
        LP::DrawText(displayMusicTitle);
        LP::DrawText(displayBeatsPerMin);
        LP::DrawText(displaySecPerBeat);
        LP::DrawText(displayBeatTimer, "Beat Time: " + to_string(beatTimer));
        LP::DrawText(displayBeatCount, "Beat Count: " + to_string(count));
        LP::DrawSprite(playerSprite[0], Vector2f(901, 535));
        LP::DrawSprite(heartSprite[0], Vector2f(705, 535));
    }

    else if (state == PlayBack)
    {
        LP::DrawText(displayMusicTitle);
        LP::DrawText(displayBeatsPerMin);
        LP::DrawText(displaySecPerBeat);
        LP::DrawText(displayBeatTimer, "Beat Time: " + to_string(beatTimer));
        LP::DrawText(displayBeatCount, "Beat Count: " + to_string(count));
        LP::DrawSprite(playerSprite[animCount], Vector2f(901, 535));
        LP::DrawSprite(heartSprite[heartCount], Vector2f(705, 535));
    }

    else if (state == Save)
    {}

    if (alpha > 0) LP::DrawText(savedText); //draw 'saved' text when visible

    //Draw UI
    ui_.Draw();
}

void BPMScene::End()
{
    //delete main menu text (マインメニューテクストを削除する)
    for (auto i : menu)
    {
        LP::DeleteText(i);
    }
    menu.clear();

    //delete other text (他のテクストを削除する)
    LP::DeleteText(setupInstructions);
    LP::DeleteText(displayBeatCount);
    LP::DeleteText(displayBeatsPerMin);
    LP::DeleteText(displaySecPerBeat);
    LP::DeleteText(savedText);

    //delete heart sprite (ハートのスパライトを削除する)
    for(auto i : heartSprite)
    {
        LP::DeleteSprite(i);
    }
    heartSprite.clear();

    //delete char sprite (キャラクターのスパライトを削除する)
    for(auto i : playerSprite)
    {
        LP::DeleteSprite(i);
    }
    playerSprite.clear();
}