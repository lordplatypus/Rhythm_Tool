#ifndef UI_H_
#define UI_H_
#include <string>

class UI
{
public:
    virtual ~UI() = default;
    virtual void Init() = 0;
    virtual void Update(float delta_time, float beat_time) = 0;
    virtual void Draw() const = 0;
    const std::string& GetName() const
    {
        return name_;
    }
    int GetID() const
    {
        return ID_;
    }
    void SetDisplay(const bool display)
    {
        display_ = display;
    }

protected:
    std::string name_{""};
    int ID_{-1};
    bool display_{true};
};

#endif