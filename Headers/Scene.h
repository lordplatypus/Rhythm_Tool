#ifndef SCENE_H_
#define SCENE_H_
#include "MP.h"

class GameObject;

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update(float delta_time, float beat_time) = 0;
    virtual void Draw() = 0;
    virtual void End() = 0;
};

#endif