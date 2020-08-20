#ifndef LP_H_
#define LP_H_
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <queue>

class LP
{
public:
    LP();
    ~LP();
    //Drawing Circles
    static int SetCircle(const sf::Vector2f position, const float radius);
    static void DrawCircle(const int key);
    static void DrawCircle(const int key, const sf::Vector2f position);
    static void SetCircleColor(const int key, const int red, const int green, const int blue, const int alpha);
    static void SetCircleRadius(const int key, const float radius);
    //Drawing Rectangles
    static int SetRectangle(const sf::Vector2f position, const float width, const float height);
    static void DrawRectangle(const int key);
    static void DrawRectangle(const int key, const sf::Vector2f position);
    static void SetRectangleColor(const int key, const int red, const int green, const int blue, const int alpha);
    static void SetRectangleSize(const int key, const float width, const float height);
    //Drawing Sprites
    static int SetTexture(const std::string& filePath, int width, int height);
    static void SetTexture(const int key, const std::string& filePath, int width, int height);
    static int SetSprite(const int textureKey);
    static int SetSprite(const int textureKey, const sf::Vector2f position);
    static int SetSprite(const int textureKey, const sf::Vector2f position, const int cellWidth, const int cellHeight, const int cellID);
    static std::vector<int> SetSprite(const int textureKey, const int cellWidth, const int cellHeight, const int numOfColumns, const int numOfRows);
    static void DrawSprite(const int key);
    static void DrawSprite(const int key, sf::Vector2f position);
    static void SetSpriteColor(const int key, const int red, const int green, const int blue, const int alpha);
    static void SetSpriteRotation(const int key, const float angle);
    static void SetSpriteOrigin(const int key, const sf::Vector2f newOrigin);
    static void SetSpriteOriginCenter(const int key);
    static void SetSpriteScale(const int key, const float scaleX, const float scaleY);
    static void SetSpriteHorizontalFlip(const int key, const bool flip);
    //Drawing Text
    static void SetFont(const std::string& filePath);
    static int SetText(const std::string& text, const sf::Vector2f position, int textSize);
    static void SetTextColor(const int key, const sf::Color color);
    static void SetTextColor(const int key, const int red, const int green, const int blue, const int alpha);
    static void SetTextOrigin(const int key, const sf::Vector2f newOrigin);
    static void SetTextOriginCenter(const int key);
    static void SetTextPosition(const int key, const sf::Vector2f newPosition);
    static void SetTextScale(const int key, const float scaleX, const float scaleY);
    static void DrawText(const int key);
    static void DrawText(const int key, const std::string& text);
    //Draw
    static void Draw(sf::RenderWindow *window);
    //Delete
    static void DeleteCircle(int key);
    static void DeleteRectangle(int key);
    static void DeleteTexture(int key);
    static void DeleteSprite(int key);
    static void DeleteText(int key);
    static void DeleteAll();

private:
    static int key;
    static std::queue<int> thingsToDraw;

    static std::unordered_map<int, sf::CircleShape> circleMap;
    static std::unordered_map<int, sf::RectangleShape> rectangleMap;
    static std::unordered_map<int, sf::Texture> textureMap;
    static std::unordered_map<int, sf::Sprite> spriteMap;
    static sf::Font font;
    static std::unordered_map<int, sf::Text> textMap;
};

#endif