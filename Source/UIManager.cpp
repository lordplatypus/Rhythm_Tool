#include "../Headers/UIManager.h"
#include "../Headers/UIText.h"

UIManager::UIManager()
{}

UIManager::~UIManager()
{
    Clear();
}

void UIManager::Init()
{}

void UIManager::Update(float delta_time, float beat_time)
{
    for (auto ui : uiObjects_)
    {
        ui->Update(delta_time, beat_time);
    }
}

void UIManager::Draw() const
{
    for (auto ui : uiObjects_)
    {
        ui->Draw();
    }
}

void UIManager::AddUI(UI* ui)
{
    uiObjects_.push_back(ui);
}

void UIManager::RemoveUI(const std::string& name)
{
    for (auto i = uiObjects_.begin(); i != uiObjects_.end(); )
    {
        if ((*i)->GetName() == name)
        {
            delete *i;
            i = uiObjects_.erase(i);
        }
        else i++;
    }
}

void UIManager::RemoveUI(const std::string& name, const int ID)
{
    for (auto i = uiObjects_.begin(); i != uiObjects_.end(); )
    {
        if ((*i)->GetName() == name && (*i)->GetID() == ID)
        {
            delete *i;
            i = uiObjects_.erase(i);
        }
        else i++;
    }
}

UI* UIManager::Find(const std::string& name) const
{
    for (auto ui : uiObjects_)
    {
        if (ui->GetName() == name)
        {
            return ui;
        }
    }
    return nullptr;
}

UI* UIManager::Find(const std::string& name, const int ID) const
{
    for (auto ui : uiObjects_)
    {
        if (ui->GetName() == name && ui->GetID() == ID)
        {
            return ui;
        }
    }
    return nullptr;
}

void UIManager::SetDisplay(const std::string& name, const int ID, const bool display)
{
    Find(name, ID)->SetDisplay(display);
}

void UIManager::Clear()
{
    for (auto ui : uiObjects_)
    {
        delete ui;
    }
    uiObjects_.clear();
}

void UIManager::AddUIText(sf::Vector2f position, int numOfText, std::vector<int> textIDs, int ID, int numToDisplay, int numAboveSelected, int textSpacing)
{
    AddUI(new UIText(position, numOfText, textIDs, ID, numToDisplay, numAboveSelected, textSpacing, 0));
}

void UIManager::ScrollUp(const int ID)
{
    dynamic_cast<UIText*>(Find("Text", ID))->ScrollUp();
}

void UIManager::ScrollDown(const int ID)
{
    dynamic_cast<UIText*>(Find("Text", ID))->ScrollDown();
}

// void UIManager::AddUIHeart(Camera* camera, int numOfHearts, float bpm)
// {
//     AddUI(new UIHeart(camera, numOfHearts, 0, bpm));
// }

// void UIManager::TakeDamagePlayer()
// {
//     dynamic_cast<UIHeart*>(Find("Heart"))->TakeDamage();
// }

// void UIManager::AddUIArrow(sf::Vector2f position, int ID, int numOfArrows)
// {
//     AddUI(new UIArrow(position, ID, numOfArrows, 0));
// }

// int UIManager::GetCurrentArrow(const int ID) const
// {
//     return dynamic_cast<UIArrow*>(Find("Arrow", ID))->GetCurrentArrow();
// }

// void UIManager::UpdateArrowPosition(const int ID, const sf::Vector2f position)
// {
//     dynamic_cast<UIArrow*>(Find("Arrow", ID))->UpdatePosition(position);
// }

// void UIManager::UpdateArrowVisiblity(const int ID, const bool isVisible)
// {
//     dynamic_cast<UIArrow*>(Find("Arrow", ID))->UpdateVisiblity(isVisible);
// }

// void UIManager::TakeDamageEnemy(const int ID, ParticleManager* PM)
// {
//     dynamic_cast<UIArrow*>(Find("Arrow", ID))->TakeDamage(PM);
// }

// void UIManager::HealDamageEnemy(const int ID)
// {
//     dynamic_cast<UIArrow*>(Find("Arrow", ID))->Heal();
// }