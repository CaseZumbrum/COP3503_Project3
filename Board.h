//
// Created by casez on 4/11/2024.
//

#pragma once
#include "Tile.h"
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>
using namespace std;

struct Board {
    vector<vector<Tile>> game;
    map <string, sf::Texture> assets;
    int row;
    int col;
    int numFlags;
    int numMines;
    bool paused = false;
    bool debug = false;

    Board(int row, int col, int n, map <string, sf::Texture>& assets){
        for(int i = 0; i < row; i++){
            game.push_back({});
            for(int j = 0; j < col; j++){
                Tile t(assets.at("covered"));
                t.setPosition(j*32,i*32);
                game.at(i).push_back(t);
            }
        }
        this->assets = assets;
        this->row = row;
        this->col = col;
        this->numFlags = n;
        this->numMines = n;
    }

    bool click(int x, int y);
    void addMines(int n, int x, int y);
    void setNeighboors();
    void toggleDebug();
    void reveal(int x, int y);
    void placeFlag(int x, int y);
    bool checkWin();
    void togglePause();
};



