#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Headers/LoadImage.h"
#include "../Headers/TextureID.h"
#include "../Headers/LP.h"
using namespace std;

LoadImage::LoadImage()
{}

LoadImage::~LoadImage()
{}

void LoadImage::Load()
{
    //Font(フォント)
    LP::SetFont("./Resources/Font/Blue Sky 8x8.ttf");

    //Player(プレーヤー)
    LP::SetTexture(robokoTexture, "./Resources/Image/Player_Roboko.png", 256, 160);

    //Heart(ハート)
    LP::SetTexture(heartTexture, "./Resources/Image/Hearts.png", 64, 16);

    LP::SetTexture(BPMSceneTexture, "./Resources/Image/BPMScene2.png", 1080, 720);
}