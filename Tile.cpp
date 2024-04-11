//
// Created by casez on 4/11/2024.
//

#include "Tile.h"
#include <string>
using namespace std;

void Tile::setBomb() {
    this->bombBool = true;
}
void Tile::toggleBombVisibility(sf::Texture& mine, sf::Texture& flag) {
    if(this->bombBool) {
        if (!this->bombVisibile) {
            sf::Sprite::setTexture(mine);
            this->bombVisibile = true;
        }
        else if(this->flagBool){
            sf::Sprite::setTexture(flag);
            this->bombVisibile = false;
        }else {
            sf::Sprite::setTexture(this->covered);
            this->bombVisibile = false;
        }
    }
}

int Tile::toggleFlag(sf::Texture& flag, sf::Texture& covered,sf::Texture& mine) {
    if(this->coveredBool) {
        if (!this->flagBool) {
            sf::Sprite::setTexture(flag);
            this->flagBool = true;
            return -1;
        }
        else if(this->bombVisibile){
            sf::Sprite::setTexture(mine);
            this->flagBool = false;
            return 1;
        }else {
            sf::Sprite::setTexture(covered);
            this->flagBool = false;
            return 1;
        }
    }
    return 0;
}

void Tile::setNeighboors(int n) {
    this->neighboors = n;
}

bool Tile::reveal(map <string, sf::Texture>& assets) {
    this->coveredBool = false;
    if(this->bombBool){
        sf::Sprite::setTexture(assets.at("mine"));
        return false;
    }
    else if(this->neighboors == 0){
        sf::Sprite::setTexture(assets.at("revealed"));
        return true;
    }
    else{
        sf::Sprite::setTexture(assets.at(to_string(this->neighboors)));
        return true;
    }
}

void Tile::pause(map<std::string, sf::Texture> &assets) {
    sf::Sprite::setTexture(assets.at("revealed"));
}

void Tile::unpause(map<std::string, sf::Texture> &assets) {
    if(!this->coveredBool){
        if(this->bombBool){
            sf::Sprite::setTexture(assets.at("mine"));
        }
        else if(this->neighboors == 0){
            sf::Sprite::setTexture(assets.at("revealed"));
        }
        else{
            sf::Sprite::setTexture(assets.at(to_string(this->neighboors)));
        }
    }
    else if(this->flagBool){
        sf::Sprite::setTexture(assets.at("flag"));
    }
    else if(this->bombVisibile){
        sf::Sprite::setTexture(assets.at("mine"));
    }
    else{
        sf::Sprite::setTexture(assets.at("covered"));
    }
}
