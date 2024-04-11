#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include "Tile.h"
#include <map>
#include "Board.h"


using namespace std;

void setText(sf::Text &text, float x, float y) {

    sf::FloatRect textRect = text.getLocalBounds();

    text.setOrigin(textRect.left + textRect.width / 2.0f,

    textRect.top + textRect.height / 2.0f);

    text.setPosition(sf::Vector2f(x, y));
}
void setSprite(sf::Sprite &sprite, float x, float y) {

    sf::FloatRect textRect = sprite.getLocalBounds();

    sprite.setOrigin(textRect.left + textRect.width / 2.0f,

                   textRect.top + textRect.height / 2.0f);

    sprite.setPosition(sf::Vector2f(x, y));
}

map <string,sf::Texture> getAssets(){
    map <string, sf::Texture> m;

    sf::Texture t;
    sf:: RenderTexture r;
    r.create(32,32);

    t.loadFromFile("files/images/tile_hidden.png");
    m.emplace("covered",t);

    t.loadFromFile("files/images/tile_revealed.png");
    m.emplace("revealed",t);

    t.loadFromFile("files/images/debug.png");
    m.emplace("debug",t);

    t.loadFromFile("files/images/digits.png");
    m.emplace("digits",t);

    t.loadFromFile("files/images/face_happy.png");
    m.emplace("happy",t);

    t.loadFromFile("files/images/face_lose.png");
    m.emplace("lose",t);

    t.loadFromFile("files/images/face_win.png");
    m.emplace("win",t);

    t.loadFromFile("files/images/flag.png");
    m.emplace("flag",t);

    t.loadFromFile("files/images/leaderboard.png");
    m.emplace("leaderboard",t);

    t.loadFromFile("files/images/mine.png");
    m.emplace("mine",t);

    t.loadFromFile("files/images/number_1.png");
    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(t));
    r.display();
    m.emplace("1",r.getTexture());

    t.loadFromFile("files/images/number_2.png");
    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(t));
    r.display();
    m.emplace("2",r.getTexture());

    t.loadFromFile("files/images/number_3.png");
    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(t));
    r.display();
    m.emplace("3",r.getTexture());

    t.loadFromFile("files/images/number_4.png");
    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(t));
    r.display();
    m.emplace("4",r.getTexture());

    t.loadFromFile("files/images/number_5.png");
    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(t));
    r.display();
    m.emplace("5",r.getTexture());

    t.loadFromFile("files/images/number_6.png");
    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(t));
    r.display();
    m.emplace("6",r.getTexture());

    t.loadFromFile("files/images/number_7.png");
    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(t));
    r.display();
    m.emplace("7",r.getTexture());

    t.loadFromFile("files/images/number_8.png");
    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(t));
    r.display();
    m.emplace("8",r.getTexture());

    t.loadFromFile("files/images/pause.png");
    m.emplace("pause",t);

    t.loadFromFile("files/images/play.png");
    m.emplace("play",t);




    r.clear();
    r.draw(sf::Sprite(m.at("revealed")));
    r.draw(sf::Sprite(m.at("mine")));
    r.display();
    t = r.getTexture();
    m.at("mine") = t;

    r.clear();
    r.draw(sf::Sprite(m.at("covered")));
    r.draw(sf::Sprite(m.at("flag")));
    r.display();
    t = r.getTexture();
    m.at("flag") = t;


    return m;
}

string welcomeScreen(){
    vector<sf::Drawable*> entities;

    ifstream config("files/config.cfg");
    string colString;
    string rowString;
    string mineString;
    getline(config,colString);
    getline(config, rowString);
    getline(config,mineString);
    int colCount = stoi(colString);
    int rowCount = stoi(rowString);
    int mineCount = stoi(mineString);
    int width = colCount*32;
    int height = rowCount*32+100;
    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height ), "Welcome!");

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("WELCOME TO MINESWEEPER");
    welcomeText.setCharacterSize(24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(welcomeText,width/2,height/2 - 150);
    entities.push_back(&welcomeText);

    sf::Text enterText;
    enterText.setFont(font);
    enterText.setString("Enter your name:");
    enterText.setCharacterSize(20);
    enterText.setStyle(sf::Text::Bold);
    setText(enterText, width/2, height/2 -75);
    entities.push_back(&enterText);

    sf::Text usernameText;
    string username = "";
    usernameText.setFont(font);
    usernameText.setString(username + "|");
    usernameText.setCharacterSize(18);
    usernameText.setStyle(sf::Text::Bold);
    setText(usernameText, width/2, height/2 -45);
    usernameText.setFillColor(sf::Color::Yellow);
    entities.push_back(&usernameText);





    while(welcomeWindow.isOpen()) {
        sf::Event event;
        while(welcomeWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                welcomeWindow.close();
            }
            if (event.type == sf::Event::TextEntered){

                if(event.text.unicode == 8){
                    username = username.substr(0,username.size()-1);
                }
                else if(event.text.unicode == 13){
                    welcomeWindow.close();
                }
                else {
                    char c = static_cast<char>(event.text.unicode);

                    if (isalpha(c) && username.size() <= 10) {

                        if (username.size() == 0) {
                            c = toupper(c);
                        } else {
                            c = tolower(c);
                        }
                        username += c;
                    }
                }
                usernameText.setString(username + "|");
                setText(usernameText, width / 2, height / 2 - 45);
            }
        }

        welcomeWindow.clear(sf::Color::Blue); // credit to my friend
        for(int i = 0; i < entities.size(); i++){
            welcomeWindow.draw(*entities.at(i));
        }
        welcomeWindow.display();
    }
    return username;
}




int main() {
    //string username = welcomeScreen();
    //cout << username << endl;



    vector<sf::Drawable*> entities;
    bool firstClick = true;
    bool won = false;
    bool lost = false;

    ifstream config("files/config.cfg");
    string colString;
    string rowString;
    string mineString;
    getline(config,colString);
    getline(config, rowString);
    getline(config,mineString);
    int colCount = stoi(colString);
    int rowCount = stoi(rowString);
    int mineCount = stoi(mineString);
    int width = colCount*32;
    int height = rowCount*32+100;
    sf::RenderWindow gameWindow(sf::VideoMode(width, height ), "Minesweeper");

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    map <string, sf::Texture> assets = getAssets();

    Board b(rowCount,colCount, mineCount, assets);

    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < colCount; j++){
            entities.push_back(&(b.game.at(i).at(j)));
        }
    }

    sf::Sprite face(assets.at("happy"));
    face.setPosition((colCount/2.0*32)-32,32*(rowCount+0.5));
    entities.push_back(&face);

    sf::Sprite debug(assets.at("debug"));
    debug.setPosition((colCount*32)-304,32*(rowCount+0.5));
    entities.push_back(&debug);
    sf::Sprite pause(assets.at("pause"));
    pause.setPosition((colCount*32)-240,32*(rowCount+0.5));
    entities.push_back(&pause);
    sf::Sprite leaderboard(assets.at("leaderboard"));
    leaderboard.setPosition((colCount*32)-176,32*(rowCount+0.5));
    entities.push_back(&leaderboard);


    while(gameWindow.isOpen()) {
        sf::Event event;
        while(gameWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if(!won && !lost) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == 0) {
                        if ((int) event.mouseButton.x / 32 < colCount && (int) event.mouseButton.y / 32 < rowCount) {
                            if (firstClick) {
                                b.addMines(mineCount, (int) event.mouseButton.x / 32, (int) event.mouseButton.y / 32);
                                b.setNeighboors();
                                firstClick = false;
                            }
                            lost = !(b.click((int) event.mouseButton.x / 32, (int) event.mouseButton.y / 32));
                            if(lost){
                                face.setTexture(assets.at("lose"));
                            }
                        } else if (!firstClick && (debug.getPosition().x <= event.mouseButton.x &&
                                                   debug.getPosition().x >= event.mouseButton.x - 64 &&
                                                   debug.getPosition().y <= event.mouseButton.y &&
                                                   debug.getPosition().y >= event.mouseButton.y - 64)) {
                            b.toggleDebug();
                        } else if ((pause.getPosition().x <= event.mouseButton.x &&
                                    pause.getPosition().x >= event.mouseButton.x - 64 &&
                                    pause.getPosition().y <= event.mouseButton.y &&
                                    pause.getPosition().y >= event.mouseButton.y - 64)) {
                            b.togglePause();
                        }
                    } else if (event.mouseButton.button == 1) {
                        if ((int) event.mouseButton.x / 32 < colCount && (int) event.mouseButton.y / 32 < rowCount) {
                            b.placeFlag((int) event.mouseButton.x / 32, (int) event.mouseButton.y / 32);
                            won = b.checkWin();
                            if(won){
                                face.setTexture(assets.at("win"));
                            }
                        }
                    } else if (event.mouseButton.button == 2) {
                        b.togglePause();
                    }
                }
            }
        }

        gameWindow.clear(sf::Color::White);
        for(int i = 0; i < entities.size(); i++){
            gameWindow.draw(*entities.at(i));
        }
        gameWindow.display();
    }



    return 0;
}