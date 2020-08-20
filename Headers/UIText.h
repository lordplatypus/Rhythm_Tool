#ifndef UI_TEXT_H_
#define UI_TEXT_H_
#include <SFML/Graphics.hpp>
#include "UI.h"

class UIText : public UI
{
public:
    UIText(sf::Vector2f position, int numOfText, std::vector<int> textIDs, int ID, int numToDisplay, int numAboveSelected, int textSpacing, int textPosition);
    ~UIText();
    virtual void Init();
    virtual void Update(float delta_time, float beat_time);
    virtual void Draw() const;
    
    void ScrollUp();
    void ScrollDown();

private:
    UIText* nextText_{nullptr};
    sf::Vector2f staticPosition_{0.0f, 0.0f};
    sf::Vector2f position_{0.0f, 0.0f};
    sf::Vector2f endPosition_{0.0f, 0.0f};
    int textKey{0};
    int textPosition_{0};
    int numOfText_{0};
    int menuPosition_{0};
    int alpha_{255};
    int numToDisplay_{0};
    int numAboveSelected_{0};
    int textSpacing_{0};
};

#endif