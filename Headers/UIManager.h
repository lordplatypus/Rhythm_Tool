#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_
#include <SFML/Graphics.hpp>
#include <list>
#include "UI.h"

class UIManager
{
public:
    UIManager();
    ~UIManager();
    void Init();
    void Update(float delta_time, float beat_time);
    void Draw() const;

    void AddUI(UI* ui);
    void RemoveUI(const std::string& name);
    void RemoveUI(const std::string& name, const int ID);
    UI* Find(const std::string& name) const;
    UI* Find(const std::string& name, const int ID) const;
    void SetDisplay(const std::string& name, const int ID, const bool display);
    void Clear();

    void AddUIText(sf::Vector2f position, int numOfText, std::vector<int> textIDs, int ID, int numToDisplay, int numAboveSelected, int textSpacing);
    void ScrollUp(const int ID);
    void ScrollDown(const int ID);

    // void AddUIHeart(Camera* camera, int numOfHearts, float bpm);
    // void TakeDamagePlayer();

    // void AddUIArrow(sf::Vector2f position, int ID, int numOfArrows);
    // int GetCurrentArrow(const int ID) const;
    // void UpdateArrowPosition(const int ID, const sf::Vector2f position);
    // void UpdateArrowVisiblity(const int ID, const bool isVisible);
    // void TakeDamageEnemy(const int ID, ParticleManager* PM);
    // void HealDamageEnemy(const int ID);

    // sf::Vector2f GetCameraViewSize();
    // sf::Vector2f GetCameraCenter();
    // float GetCameraRightEdge();
    // float GetCameraLeftEdge();
    // float GetCameraTopEdge();
    // float GetCameraBottomEdge();

private:
    //Camera* camera_;
    std::list<UI*> uiObjects_;
};

#endif