//
// Created by casez on 4/11/2024.
//
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>
using namespace std;

#pragma once

struct Tile : public sf::Sprite {
    int neighboors = 0;
    //map <string, sf::Texture> assets;
    sf::Texture covered;
    bool coveredBool = true;
    bool flagBool = false;
    bool bombBool = false;
    bool bombVisibile = false;

    Tile(sf::Texture& covered): sf::Sprite(covered){
        //this->assets = assets;
        this->covered = covered;

    }

    void setBomb();
    void toggleBombVisibility(sf::Texture& mine,sf::Texture& flag);
    int toggleFlag(sf::Texture& flag, sf::Texture& covered,sf::Texture& mine);
    bool reveal(map <string, sf::Texture>& assets);
    void setNeighboors(int n);
    void pause(map <string, sf::Texture>& assets);
    void unpause(map <string, sf::Texture>& assets);
};



