#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Headers/LP.h"
#include "../Headers/MP.h"
#include "../Headers/Game.h"
#include "../Headers/DeltaTime.h"
using namespace sf;
using namespace std;

int main()
{
    bool isRunning = true;//bool for main game loop
    RenderWindow window(VideoMode(1080, 720), "game window"); //game window
    //window.setFramerateLimit(60);
    MP mp;

    Game game{&mp}; //Create game class, handles scenes

    DeltaTime deltaTime;

    sf::View mainCamera;
    mainCamera.setSize(1080.f, 720.f);
    mainCamera.setCenter(Vector2f(540, 360));

    while (isRunning)
    {//main game loop
        Event event; //events
        while (window.pollEvent(event))
        {//
            if (event.type == Event::Closed)
            {
                isRunning = false;
            }
            else if (event.key.code == Keyboard::Escape)
            {
                isRunning = false;
            }
        }
        game.Update(deltaTime.GetDeltaTime(), mp.BeatTime());
        window.setView(mainCamera);
        game.Draw(); //objects are added to the draw maps
        window.clear();
        LP::Draw(&window); //actually draw objects
        window.display();
    }
    return EXIT_SUCCESS;
}