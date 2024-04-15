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
#include <chrono>
#include <ctime>


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
                return "-1";
            }
            if (event.type == sf::Event::TextEntered){

                if(event.text.unicode == 8){
                    username = username.substr(0,username.size()-1);
                }
                else if(event.text.unicode == 13 && username != ""){
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
    config.close();

    return username;
}

void leaderBoard(){
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
    int width = colCount*16;
    int height = rowCount*16+50;
    sf::RenderWindow leaderboardWindow(sf::VideoMode(width, height ), "Leaderboard");
    ifstream leaderReader("files/leaderboard.txt");
    string nameIndex;
    string timeIndex;
    string leaderString = "";
    int count = 1;
    while(getline(leaderReader,timeIndex,',')){
        getline(leaderReader,nameIndex);
        leaderString += to_string(count) + ".\t" + timeIndex + "\t" + nameIndex.substr(1) + "\n\n";
        count++;
    }

    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text leaderText;
    leaderText.setFont(font);
    leaderText.setString(leaderString);
    leaderText.setCharacterSize(18);
    leaderText.setStyle(sf::Text::Bold);
    setText(leaderText,width/2,height/2 + 20);
    entities.push_back(&leaderText);

    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(20);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(title,width/2,height/2 - 120);
    entities.push_back(&title);

    while(leaderboardWindow.isOpen()) {
        sf::Event event;
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboardWindow.close();
            }
        }
        leaderboardWindow.clear(sf::Color::Blue); // credit to my friend
        for(int i = 0; i < entities.size(); i++){
            leaderboardWindow.draw(*entities.at(i));
        }
        leaderboardWindow.display();
    }
    config.close();
    leaderReader.close();
}

void endleaderBoard(int sec, int min, string username){
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
    int width = colCount*16;
    int height = rowCount*16+50;
    sf::RenderWindow leaderboardWindow(sf::VideoMode(width, height ), "Leaderboard");
    ifstream leaderReader("files/leaderboard.txt");
    string nameIndex;
    string timeIndex;
    string leaderString = "";
    vector<string> times;
    vector<string> names;
    int count = 1;
    while(getline(leaderReader,timeIndex,',')){
        getline(leaderReader,nameIndex);
        times.push_back(timeIndex);
        names.push_back(nameIndex.substr(1));
        count++;
    }


    int position = -1;

    for(int i = 0; i < times.size(); i++){
        if(min < stoi(times.at(i).substr(0,2)) || (min == stoi(times.at(i).substr(0,2)) && sec < stoi(times.at(i).substr(3,2)))){
            position = i + 1;
            break;
        }
    }

    if(position != -1) {
        for (int i = times.size() - 1; i >= position; i--) {
            times.at(i) = times.at(i - 1);
            names.at(i) = names.at(i - 1);
        }
        times.at(position - 1) = to_string(min).insert(0, 2 - to_string(min).size(), '0') + ":" +
                                 to_string(sec).insert(0, 2 - to_string(sec).size(), '0');
        names.at(position - 1) = username;
    }

    for(int i = 1; i <= times.size(); i++){
        if(i == position){
            leaderString += to_string(i) + ".\t" + times.at(i-1) + "\t" + names.at(i-1) + "*\n\n";
        }
        else {
            leaderString += to_string(i) + ".\t" + times.at(i - 1) + "\t" + names.at(i - 1) + "\n\n";
        }

    }

    config.close();
    leaderReader.close();

    string leaderStringOut = "";
    for(int i = 1; i <= times.size(); i++){
        leaderStringOut +=times.at(i-1) + ", " + names.at(i-1) + "\n";
    }

    ofstream leaderWriter("files/leaderboard.txt");
    leaderWriter << leaderStringOut;
    leaderWriter.close();



    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text leaderText;
    leaderText.setFont(font);
    leaderText.setString(leaderString);
    leaderText.setCharacterSize(18);
    leaderText.setStyle(sf::Text::Bold);
    setText(leaderText,width/2,height/2 + 20);
    entities.push_back(&leaderText);

    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(20);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(title,width/2,height/2 - 120);
    entities.push_back(&title);

    while(leaderboardWindow.isOpen()) {
        sf::Event event;
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboardWindow.close();
            }
        }
        leaderboardWindow.clear(sf::Color::Blue); // credit to my friend
        for(int i = 0; i < entities.size(); i++){
            leaderboardWindow.draw(*entities.at(i));
        }
        leaderboardWindow.display();
    }


}


int gameScreen(string username){
    auto start = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds;


    vector<sf::Drawable*> entities;
    bool firstClick = true;
    bool won = false;
    bool lost = false;
    bool pauseBool = false;

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

    int ones;
    int tens;
    int hundreds;
    bool negative = false;
    sf::Sprite onesSprite(assets.at("digits"));
    onesSprite.setPosition(33+21+21,32*(rowCount+0.5)+16);
    sf::Sprite tensSprite(assets.at("digits"));
    tensSprite.setPosition(33+21,32*(rowCount+0.5) + 16);
    sf::Sprite hundredsSprite(assets.at("digits"));
    hundredsSprite.setPosition(33,32*(rowCount+0.5) + 16);
    sf::Sprite negSprite(assets.at("digits"),sf::IntRect(21*10,0,21,32));
    negSprite.setPosition(12,32*(rowCount+0.5) + 16);
    entities.push_back(&onesSprite);
    entities.push_back(&tensSprite);
    entities.push_back(&hundredsSprite);

    int secs;
    int mins;
    sf::Sprite secOnes(assets.at("digits"),sf::IntRect(0,0,21,32));
    secOnes.setPosition(colCount*32 - 54 + 21,32*(rowCount+0.5)+16);
    sf::Sprite secTens(assets.at("digits"),sf::IntRect(0,0,21,32));
    secTens.setPosition(colCount*32 - 54,32*(rowCount+0.5)+16);
    sf::Sprite minOnes(assets.at("digits"),sf::IntRect(0,0,21,32));
    minOnes.setPosition(colCount*32 - 97 + 21,32*(rowCount+0.5)+16);
    sf::Sprite minTens(assets.at("digits"),sf::IntRect(0,0,21,32));
    minTens.setPosition(colCount*32 - 97,32*(rowCount+0.5)+16);
    entities.push_back(&secOnes);
    entities.push_back(&secTens);
    entities.push_back(&minOnes);
    entities.push_back(&minTens);


    while(gameWindow.isOpen()) {
        sf::Event event;
        while(gameWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if(!won && !lost) {
                    if (event.mouseButton.button == 0) {
                        if ((int) event.mouseButton.x / 32 < colCount && (int) event.mouseButton.y / 32 < rowCount) {
                            if (firstClick) {
                                b.addMines(mineCount, (int) event.mouseButton.x / 32, (int) event.mouseButton.y / 32);
                                b.setNeighboors();
                                firstClick = false;
                            }
                            lost = !(b.click((int) event.mouseButton.x / 32, (int) event.mouseButton.y / 32));
                            if (lost) {
                                face.setTexture(assets.at("lose"));
                            }
                            won = b.checkWin();
                            if (won) {
                                face.setTexture(assets.at("win"));
                                onesSprite.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
                                tensSprite.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
                                hundredsSprite.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
                                gameWindow.clear(sf::Color::White);
                                for (int i = 0; i < entities.size(); i++) {
                                    gameWindow.draw(*entities.at(i));
                                }
                                gameWindow.display();
                                endleaderBoard(((int) elapsed_seconds.count()) % 60,
                                               ((int) elapsed_seconds.count()) / 60, username);
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
                            pauseBool = !pauseBool;
                        }


                    } else if (event.mouseButton.button == 1 && !firstClick) {
                        if ((int) event.mouseButton.x / 32 < colCount && (int) event.mouseButton.y / 32 < rowCount) {
                            b.placeFlag((int) event.mouseButton.x / 32, (int) event.mouseButton.y / 32);
                        }
                    }
                }
                if (event.mouseButton.button == 0 && (leaderboard.getPosition().x <= event.mouseButton.x &&
                                                      leaderboard.getPosition().x >= event.mouseButton.x - 64 &&
                                                      leaderboard.getPosition().y <= event.mouseButton.y &&
                                                      leaderboard.getPosition().y >= event.mouseButton.y - 64)) {
                    if(!pauseBool) {
                        b.togglePause();
                        gameWindow.clear(sf::Color::White);
                        for (int i = 0; i < entities.size(); i++) {
                            gameWindow.draw(*entities.at(i));
                        }
                        gameWindow.display();
                        leaderBoard();
                        b.togglePause();
                    }
                    else{
                        leaderBoard();
                    }
                    start = chrono::system_clock::now();

                }
                else if ((face.getPosition().x <= event.mouseButton.x &&
                          face.getPosition().x >= event.mouseButton.x - 64 &&
                          face.getPosition().y <= event.mouseButton.y &&
                          face.getPosition().y >= event.mouseButton.y - 64)) {
                    gameWindow.close();
                    gameScreen(username);
                    return 0;
                }
            }
        }

        //flag counter
        if(b.numFlags < 0){
            negative = true;
            ones =-1* b.numFlags % 10;
            tens = -1* ((int) b.numFlags / 10)%10;
            hundreds = -1* (int) b.numFlags / 100;
        }
        else{
            negative = false;
            ones = b.numFlags % 10;
            tens = ((int) b.numFlags / 10)%10;
            hundreds = (int) b.numFlags / 100;

        }
        onesSprite.setTextureRect(sf::IntRect(21*ones,0,21,32));
        tensSprite.setTextureRect(sf::IntRect (21*tens,0,21,32));
        hundredsSprite.setTextureRect(sf::IntRect (21*hundreds,0,21,32));


        if(negative){
            gameWindow.draw(negSprite);
        }
        if(!won && !lost && !pauseBool && !firstClick) {
            elapsed_seconds += chrono::system_clock::now() - start;

            secs = ((int) elapsed_seconds.count()) % 60;
            mins = ((int) elapsed_seconds.count()) / 60;
            secOnes.setTextureRect(sf::IntRect(21 * (secs % 10), 0, 21, 32));
            secTens.setTextureRect(sf::IntRect(21 * (secs / 10), 0, 21, 32));
            minOnes.setTextureRect(sf::IntRect(21 * (mins % 10), 0, 21, 32));
            minTens.setTextureRect(sf::IntRect(21 * (mins / 10), 0, 21, 32));
        }
        start = chrono::system_clock::now();
        gameWindow.clear(sf::Color::White);
        for(int i = 0; i < entities.size(); i++){
            gameWindow.draw(*entities.at(i));
        }
        gameWindow.display();

    }



    config.close();
    return 0;
}


int main() {
    string username = welcomeScreen();
    if(username == "-1"){
        return 0;
    }
    return gameScreen(username);
}