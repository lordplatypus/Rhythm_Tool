#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include <unordered_map>
#include "Scene.h"
#include "MP.h"
#include "LoadImage.h"

class Game
{
public:
    Game(MP* mp);
    ~Game();
    void Update(float delta_time, float beat_time);
    void Draw();
    void AddScene(const std::string& name, Scene* scene);
    void ChangeScene(const std::string& newScene);
    void EndScene();
    void Clear();

    Game(const Game& other) = delete;
    Game& operator = (const Game& other) = delete;

private:
    std::unordered_map<std::string, Scene*> scenes_;
    Scene* scene_ {nullptr};
    MP* mp_ {nullptr};
    LoadImage loadImage_;
};

#endif