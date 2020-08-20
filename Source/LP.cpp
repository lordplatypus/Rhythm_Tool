#include "../Headers/LP.h"
using namespace std;
using namespace sf;

int LP::key = 0; //creates keys to use in the below maps
queue<int> LP::thingsToDraw; //list of ints (keys) used to know what to draw
unordered_map<int, RectangleShape> LP::rectangleMap; //map of rectangles
unordered_map<int, CircleShape> LP::circleMap; //map of circles
unordered_map<int, Texture> LP::textureMap;
unordered_map<int, Sprite> LP::spriteMap;
Font LP::font;
unordered_map<int, Text> LP::textMap;

LP::LP(){}

LP::~LP(){}


//Drawing Circles
// int LP::SetCircle(int x, int y, int radius, sf::Color color)
// {//create a new circle and add it to the circle map, return the key
//     key++; //generate new key
//     circleMap[key].setRadius(radius); //set radius
//     circleMap[key].setPosition(x, y); //set position
//     circleMap[key].setFillColor(color); //set color
//     return key; //return the key to the newly created circle
// }

// void LP::DrawCircle(int key)
// {//adds circle to the list of objects to draw, no changes to the circle need to be made
//     thingsToDraw.push(key);
// }

// void LP::DrawCircle(int x, int y, int radius, sf::Color color, int key)
// {//adds circle to the list of objects to draw, changes are made to the circle before it is added to the list
//     circleMap[key].setPosition(x, y); //change position
//     circleMap[key].setRadius(radius); //change radius
//     circleMap[key].setFillColor(color); //change color
//     thingsToDraw.push(key);
// }

int LP::SetCircle(const sf::Vector2f position, const float radius)
{
    key++;
    circleMap[key].setPosition(position);
    circleMap[key].setRadius(radius);
    circleMap[key].setFillColor(Color::White);
    return key;
}

void LP::DrawCircle(const int key)
{
    thingsToDraw.push(key);
}

void LP::DrawCircle(const int key, const sf::Vector2f position)
{
    circleMap[key].setPosition(position);
    thingsToDraw.push(key);
}

void LP::SetCircleColor(const int key, const int red, const int green, const int blue, const int alpha)
{
    circleMap[key].setFillColor(Color(red, green, blue, alpha));
}

void LP::SetCircleRadius(const int key, const float radius)
{
    circleMap[key].setRadius(radius);
}


//Drawing Rectangles
int LP::SetRectangle(const sf::Vector2f position, const float width, const float height)
{
    key++;
    rectangleMap[key].setPosition(position);
    rectangleMap[key].setSize(Vector2f(width, height));
    rectangleMap[key].setFillColor(Color::White);
    return key;
}

void LP::DrawRectangle(const int key)
{
    thingsToDraw.push(key);
}

void LP::DrawRectangle(const int key, const sf::Vector2f position)
{
    rectangleMap[key].setPosition(position);
    thingsToDraw.push(key);
}

void LP::SetRectangleColor(const int key, const int red, const int green, const int blue, const int alpha)
{
    rectangleMap[key].setFillColor(Color(red, green, blue, alpha));
}

void LP::SetRectangleSize(const int key, const float width, const float height)
{
    rectangleMap[key].setSize(Vector2f(width, height));
}


//Drawing Sprites
// int LP::SetTexture(string filePath, int width, int height)
// {
//     key++;
//     textureMap[key].loadFromFile(filePath, IntRect(0, 0, width, height));
//     return key;
// }

// void LP::SetTexture(const int key, const std::string& filePath, int width, int height)
// {
//     textureMap[key].loadFromFile(filePath, IntRect(0, 0, width, height));
// }

// int LP::SetSprite(int x, int y, int textureKey)
// {
//     key++;
//     spriteMap[key].setTexture(textureMap[textureKey]);
//     spriteMap[key].setPosition(x, y);
//     return key;
// }

// int LP::SetSprite(int x, int y, int cellWidth, int cellHeight, int cellNum, int textureKey)
// {
//     key++;
//     spriteMap[key].setTexture(textureMap[textureKey]);
//     Vector2u textureSize = textureMap[textureKey].getSize();
//     spriteMap[key].setTextureRect(IntRect(cellNum % (textureSize.x / cellWidth) * cellWidth, cellNum / (textureSize.x / cellWidth) * cellWidth, cellWidth, cellHeight));
//     spriteMap[key].setPosition(x, y);
//     return key;
// }

// vector<int> LP::SetSprite(int cellWidth, int cellHeight, int numOfColumns, int numOfRows, int textureKey)
// {
//     vector<int> spriteArray;
//     for (int i = 0; i < numOfRows; i++)
//     {
//         for (int j = 0; j < numOfColumns; j++)
//         {
//             key++;
//             spriteMap[key].setTexture(textureMap[textureKey]);
//             spriteMap[key].setTextureRect(IntRect(cellWidth * j, cellHeight * i, cellWidth, cellHeight));
//             spriteArray.push_back(key);
//         }
//     }
//     return spriteArray;
// }

// void LP::DrawSprite(Vector2f position, const int key)
// {
//     spriteMap[key].setPosition(position);
//     thingsToDraw.push(key);
// }

// void LP::DrawSprite(int x, int y, bool flip, int key)
// {
//     spriteMap[key].setPosition(x, y);
//     if (flip) spriteMap[key].setScale(-1, 1);
//     else spriteMap[key].setScale(1, 1);
//     thingsToDraw.push(key);
// }

// void LP::DrawSprite(float x, float y, bool flip, int key)
// {
//     spriteMap[key].setPosition(x, y);
//     if (flip) 
//     {
//         spriteMap[key].setScale(-1, 1);
//         spriteMap[key].setOrigin(spriteMap[key].getLocalBounds().width, 0);
//     }
//     else 
//     {
//         spriteMap[key].setScale(1, 1);
//         spriteMap[key].setOrigin(0, 0);
//     }
//     thingsToDraw.push(key);
// }

// void LP::DrawSprite(float x, float y, bool flip, float scaleX, float scaleY, int key)
// {
//     spriteMap[key].setPosition(x, y);
//     if (flip) 
//     {
//         spriteMap[key].setScale(-scaleX, scaleY);
//         spriteMap[key].setOrigin(spriteMap[key].getLocalBounds().width, 0);
//     }
//     else 
//     {
//         spriteMap[key].setScale(scaleX, scaleY);
//         spriteMap[key].setOrigin(0, 0);
//     }
//     thingsToDraw.push(key);
// }

// void LP::DrawSprite(int key)
// {
//     thingsToDraw.push(key);
// }

// void LP::SetSpriteColor(int key, int red, int green, int blue, int alpha)
// {
//     spriteMap[key].setColor(Color(red, green, blue, alpha));
// }

// void LP::SetSpriteRotation(int key, float angle)
// {
//     spriteMap[key].setRotation(angle);
// }

// void LP::SetSpriteOrigin(const int key, const Vector2f newOrigin)
// {
//     spriteMap[key].setOrigin(newOrigin);
// }

// void LP::SetSpriteScale(const int key, const float scaleX, const float scaleY)
// {
//     spriteMap[key].setScale(scaleX, scaleY);
// }

// void LP::SetSpriteHorizontalFlip(const int key, bool flip)
// {
//     if (flip && spriteMap[key].getScale().x > 0)
//     {
//         spriteMap[key].scale(-1.0f, 1.0f);
//         spriteMap[key].setOrigin(spriteMap[key].getLocalBounds().width, spriteMap[key].getOrigin().y);
//     }
//     else if (!flip && spriteMap[key].getScale().x < 0)
//     {
//         spriteMap[key].scale(-1.0f, 1.0f);
//         spriteMap[key].setOrigin(0, spriteMap[key].getOrigin().y);
//     }
// }

int LP::SetTexture(const std::string& filePath, int width, int height)
{
    key++;
    textureMap[key].loadFromFile(filePath, IntRect(0, 0, width, height));
    return key;
}

void LP::SetTexture(const int key, const std::string& filePath, int width, int height)
{
    textureMap[key].loadFromFile(filePath, IntRect(0, 0, width, height));
}

int LP::SetSprite(const int textureKey)
{
    key++;
    spriteMap[key].setTexture(textureMap[textureKey]);
    return key;
}

int LP::SetSprite(const int textureKey, const sf::Vector2f position)
{
    key++;
    spriteMap[key].setTexture(textureMap[textureKey]);
    spriteMap[key].setPosition(position);
    return key;
}

int LP::SetSprite(const int textureKey, const Vector2f position, const int cellWidth, const int cellHeight, const int cellID)
{
    key++;
    spriteMap[key].setTexture(textureMap[textureKey]);
    Vector2u textureSize = textureMap[textureKey].getSize();
    spriteMap[key].setTextureRect(IntRect(cellID % (textureSize.x / cellWidth) * cellWidth, cellID / (textureSize.x / cellWidth) * cellWidth, cellWidth, cellHeight));
    spriteMap[key].setPosition(position);
    return key;
}

std::vector<int> LP::SetSprite(const int textureKey, const int cellWidth, const int cellHeight, const int numOfColumns, const int numOfRows)
{
    vector<int> spriteArray;
    for (int i = 0; i < numOfRows; i++)
    {
        for (int j = 0; j < numOfColumns; j++)
        {
            key++;
            spriteMap[key].setTexture(textureMap[textureKey]);
            spriteMap[key].setTextureRect(IntRect(cellWidth * j, cellHeight * i, cellWidth, cellHeight));
            spriteArray.push_back(key);
        }
    }
    return spriteArray;
}

void LP::DrawSprite(const int key)
{
    thingsToDraw.push(key);
}

void LP::DrawSprite(const int key, sf::Vector2f position)
{
    spriteMap[key].setPosition(position);
    thingsToDraw.push(key);
}

void LP::SetSpriteColor(const int key, const int red, const int green, const int blue, const int alpha)
{
    spriteMap[key].setColor(Color(red, green, blue, alpha));
}

void LP::SetSpriteRotation(const int key, const float angle)
{
    spriteMap[key].setRotation(angle);
}

void LP::SetSpriteOrigin(const int key, const sf::Vector2f newOrigin)
{
    spriteMap[key].setOrigin(newOrigin);
}

void LP::SetSpriteOriginCenter(const int key)
{
    spriteMap[key].setOrigin(spriteMap[key].getLocalBounds().width / 2, spriteMap[key].getLocalBounds().height / 2);
}

void LP::SetSpriteScale(const int key, const float scaleX, const float scaleY)
{
    spriteMap[key].setScale(scaleX, scaleY);
}

void LP::SetSpriteHorizontalFlip(const int key, const bool flip)
{
    if (flip && spriteMap[key].getScale().x > 0)
    {
        spriteMap[key].scale(-1.0f, 1.0f);
        spriteMap[key].setOrigin(spriteMap[key].getLocalBounds().width, spriteMap[key].getOrigin().y);
    }
    else if (!flip && spriteMap[key].getScale().x < 0)
    {
        spriteMap[key].scale(-1.0f, 1.0f);
        spriteMap[key].setOrigin(0, spriteMap[key].getOrigin().y);
    }
}


//Drawing Text
void LP::SetFont(const string& filePath)
{
    font.loadFromFile(filePath);
}

int LP::SetText(const string& text, const Vector2f position, int textSize)
{
    key++;
    textMap[key].setFont(font);
    textMap[key].setCharacterSize(textSize);
    textMap[key].setPosition(position);
    textMap[key].setFillColor(sf::Color::White);
    textMap[key].setString(text);
    return key;
}

void LP::SetTextColor(const int key, const sf::Color color)
{
    textMap[key].setFillColor(color);
}

void LP::SetTextColor(const int key, const int red, const int green, const int blue, const int alpha)
{
    textMap[key].setFillColor(Color(red, green, blue, alpha));
}

void LP::SetTextOrigin(const int key, const sf::Vector2f newOrigin)
{
    textMap[key].setOrigin(newOrigin);
}

void LP::SetTextOriginCenter(const int key)
{
    textMap[key].setOrigin(textMap[key].getLocalBounds().width / 2, textMap[key].getLocalBounds().height / 2);
}

void LP::SetTextPosition(const int key, const sf::Vector2f newPosition)
{
    textMap[key].setPosition(newPosition);
}

void LP::SetTextScale(const int key, const float scaleX, const float scaleY)
{
    textMap[key].setScale(scaleX, scaleY);
}

void LP::DrawText(int key)
{
    thingsToDraw.push(key);
}

void LP::DrawText(const int key, const string& text)
{
    textMap[key].setString(text);
    thingsToDraw.push(key);
}


//Draw
void LP::Draw(RenderWindow *window)
{
    if(thingsToDraw.size() > 0)
    {//as long as there are things to draw, run the below code
        int numOfThingsToDraw = thingsToDraw.size(); //save the num of things to draw
        for (int i = 0; i < numOfThingsToDraw; i++)
        {
            if (circleMap.find(thingsToDraw.front()) != circleMap.end())
            {//if the circleMap contains the key draw the circle
                window->draw(circleMap[thingsToDraw.front()]);
            }
            else if (rectangleMap.find(thingsToDraw.front()) != rectangleMap.end())
            {//if the rectangleMap contains the key, draw the rectangle
                window->draw(rectangleMap[thingsToDraw.front()]);
            }
            else if (spriteMap.find(thingsToDraw.front()) != spriteMap.end())
            {
                window->draw(spriteMap[thingsToDraw.front()]);
            }
            else if (textMap.find(thingsToDraw.front()) != textMap.end())
            {
                window->draw(textMap[thingsToDraw.front()]);
            }
            thingsToDraw.pop(); //remove the key from the list
        }
    }
}


//Delete
void LP::DeleteCircle(int key)
{
    circleMap.erase(key);
}

void LP::DeleteRectangle(int key)
{
    rectangleMap.erase(key);
}

void LP::DeleteTexture(int key)
{
    textureMap.erase(key);
}

void LP::DeleteSprite(int key)
{
    spriteMap.erase(key);
}

void LP::DeleteText(int key)
{
    textMap.erase(key);
}

void LP::DeleteAll()
{
    circleMap.clear();
    rectangleMap.clear();
}