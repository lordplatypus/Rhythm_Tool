#include "../Headers/UIText.h"
#include "../Headers/LP.h"
#include "../Headers/Math.h"

UIText::UIText(sf::Vector2f position, int numOfText, std::vector<int> textIDs, int ID, int numToDisplay, int numAboveSelected, int textSpacing, int textPosition)
{
    name_ = "Text";
    ID_ = ID;
    textKey = textIDs[textPosition];
    menuPosition_ = textPosition;
    textPosition_ = textPosition + 1;
    numToDisplay_ = numToDisplay;
    numAboveSelected_ = numAboveSelected;
    textSpacing_ = textSpacing;
    staticPosition_ = position;
    position_ = staticPosition_;
    if (menuPosition_ == numOfText_ - 1) position_.y = staticPosition_.y - 64;
    else position_.y = staticPosition_.y + menuPosition_ * 64;
    LP::SetTextPosition(textKey, position_);
    endPosition_ = position_;
    numOfText_ = numOfText;
    if (menuPosition_ != 0) 
    {
        alpha_ = 255/4;
        LP::SetTextColor(textKey, 255, 255, 255, alpha_);
    }

    if (textPosition_ != numOfText_)
    {
        nextText_ = new UIText(staticPosition_, numOfText_, textIDs, ID_, numToDisplay_, numAboveSelected_, textSpacing_, textPosition_);
    }
}

UIText::~UIText()
{
    delete nextText_;
}

void UIText::Init()
{}

void UIText::Update(float delta_time, float beat_time)
{
    if (menuPosition_ >= numToDisplay_) endPosition_.y = staticPosition_.y + (menuPosition_ - numOfText_) * textSpacing_;
    else endPosition_.y = staticPosition_.y + menuPosition_ * textSpacing_;
    if (numOfText_ != textPosition_) nextText_->Update(delta_time, beat_time);

    if (position_ != endPosition_)
    {
        position_ = Math::Lerp(position_, endPosition_, 10 * delta_time);
        LP::SetTextPosition(textKey, position_);
    }
    
}

void UIText::Draw() const
{
    if (display_ == false) return;


    if (menuPosition_ >= numOfText_ - numAboveSelected_) LP::DrawText(textKey);
    if (menuPosition_ <= numToDisplay_ - 1 - numAboveSelected_) LP::DrawText(textKey);



    //if (menuPosition_ <= numToDisplay_ - 1) LP::DrawText(textKey);
    if (numOfText_ != textPosition_) nextText_->Draw();
}

void UIText::ScrollUp()
{
    menuPosition_--;
    if (menuPosition_ < 0) menuPosition_ = numOfText_ - 1;
    if (menuPosition_ == 0) alpha_ = 255;
    else alpha_ = 255/4;
    LP::SetTextColor(textKey, 255, 255, 255, alpha_);
    if (numOfText_ != textPosition_) nextText_->ScrollUp();
}

void UIText::ScrollDown()
{
    menuPosition_++;
    if (menuPosition_ > numOfText_ - 1) menuPosition_ = 0; 
    if (menuPosition_ == 0) alpha_ = 255;
    else alpha_ = 255/4;
    LP::SetTextColor(textKey, 255, 255, 255, alpha_);
    if (numOfText_ != textPosition_) nextText_->ScrollDown();
}