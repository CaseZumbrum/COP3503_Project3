//
// Created by casez on 4/11/2024.
//

#include "Board.h"
#include <cstdlib>

bool Board::click(int x, int y) {
    if(!this->paused) {
        if (this->game.at(y).at(x).bombBool) {
            this->game.at(y).at(x).reveal(this->assets);
            return false;

        } else {
            this->reveal(x, y);
            return true;
        }
    }
}

void Board::reveal(int x, int y) {
    if(this->game.at(y).at(x).flagBool){
        this->numFlags += this->game.at(y).at(x).toggleFlag(this->assets.at("flag"),this->assets.at("covered"),this->assets.at("mine"));
    }
    this->game.at(y).at(x).reveal(this->assets);

    if(this->game.at(y).at(x).neighboors == 0){
        for(int k = -1; k <=1; k++) {
            for (int l = -1; l <= 1; l++) {
                if (y + k >= 0 && y + k < this->row && x + l >= 0 && x + l < this->col) {
                    if (!(k == 0 && l == 0) && game.at(y+k).at(x+l).coveredBool && !game.at(y+k).at(x+l).flagBool) {
                        this->reveal(x+l,y+k);

                    }
                }
            }
        }
    }

}

void Board::addMines(int n, int x, int y) {
    int bombx;
    int bomby;
    for(int i = 0; i < n; i++){
        bombx = rand() % this->col;
        bomby = rand() % this->row;
        while(this->game.at(bomby).at(bombx).bombBool || ((x-1 <= bombx && bombx <= x+1) && y-1 <= bomby && bomby <= y+1)){
            bombx = rand() % this->col;
            bomby = rand() % this->row;
        }
        this->game.at(bomby).at(bombx).bombBool = true;

    }
}

void Board::setNeighboors() {
    int n;
    for(int i = 0; i < this->row; i++){
        for(int j = 0; j < this->col; j++){
            n = 0;
            for(int k = -1; k <=1; k++){
                for(int l = -1; l <= 1; l++){
                    if(i +k >= 0 && i + k < this->row && j + l >= 0 && j + l < this->col){
                        if(!(k == 0 && l==0)){
                            if(this->game.at(i+k).at(j+l).bombBool){
                                n++;
                            }
                        }
                    }
                }
            }
            this->game.at(i).at(j).setNeighboors(n);
        }
    }
}

void Board::toggleDebug() {
        this->debug = !this->debug;
        for(int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                this->game.at(i).at(j).toggleBombVisibility(this->assets.at("mine"),this->assets.at("flag"));
            }
        }


}

void Board::placeFlag(int x, int y) {
    if(!this->paused) {
        this->numFlags += this->game.at(y).at(x).toggleFlag(assets.at("flag"), assets.at("covered"), this->assets.at("mine"));
    }
}

bool Board::checkWin() {
    if(this->numFlags == 0){
        for(int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                if(!(!this->game.at(i).at(j).bombBool || this->game.at(i).at(j).flagBool)){
                    return false;
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}

void Board::togglePause() {
    if(!this->paused){
        this->paused = true;
        for(int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                this->game.at(i).at(j).pause(this->assets);
            }
        }
    }
    else{
        this->paused = false;
        for(int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                this->game.at(i).at(j).unpause(this->assets);
            }
        }
    }
}


