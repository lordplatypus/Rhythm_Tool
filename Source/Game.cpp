#include <SFML/Graphics.hpp>
#include "../Headers/Game.h"
#include "../Headers/BPMScene.h"
#include "../Headers/NullScene.h"
#include "../Headers/LoadImage.h"
using namespace std;
using namespace sf;

static NullScene nullScene;

Game::Game(MP* mp) : mp_{mp}, scene_{&nullScene}
{
    loadImage_.Load();
    mp_->Load();
    AddScene("BPMScene", new BPMScene(this, mp_));

    scene_ = scenes_["BPMScene"];
    scene_->Init();
}

Game::~Game()
{
    Clear();
}

void Game::Update(float delta_time, float beat_time)
{
    scene_->Update(delta_time, beat_time);
}

void Game::Draw()
{
    scene_->Draw();
}

void Game::AddScene(const std::string& name, Scene* scene)
{
    scenes_[name] = scene;
}

void Game::ChangeScene(const string& newScene)
{
    EndScene();
    scene_ = scenes_[newScene];
    scene_->Init();
}

void Game::EndScene()
{
    scene_->End();
    scene_ = &nullScene;
}

void Game::Clear()
{
    scene_->End();

    for (auto pair : scenes_)
    {
        delete pair.second;
    }
    scenes_.clear();
}