#ifndef NULL_SCENE_H_
#define NULL_SCENE_H_
#include "Scene.h"

class NullScene : public Scene
{
public:
    virtual void Init() override {}
    virtual void Update(float delta_time, float beat_time) override {}
    virtual void Draw() override {}
    virtual void End() override {}
};

#endif