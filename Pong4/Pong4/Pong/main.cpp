/*
Martin Hundrup, Gil Rezin, Phoenix Staley
CptS 122
4/26/23
Side-scrolling runner game in which the player must dodge obstacles and pits to survive. Press space to jump
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Animation.hpp"
#include "Grass.hpp"
#include "Hurdle.hpp"
#include "Obstacle.hpp"
#include "Player.hpp"
#include "Spawner.hpp"

using std::vector;

int main() {
    int UNITSIZE = 96;
    bool gameOver = false;
    int score = 0;

    srand(time(NULL));

    // load the score counter
    sf::Font font;
    font.loadFromFile("8-bit-hud.ttf");
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(760, 20);
    scoreText.setCharacterSize(36);

    sf::Texture textures[4];

    // dirt texture
    sf::Texture &blockTexture = textures[0];
    blockTexture.loadFromFile("testDirt.png");
    blockTexture.setRepeated(true);

    // tree texture
    sf::Texture &treeTexture = textures[1];
    treeTexture.loadFromFile("testTree.png");
    // treeTexture.setRepeated(true);
    // the speed at which obstacles should move
    double currSpeed = 4;
    bool touchingGround = false;

    // shrub texture
    sf::Texture &shrubTexture = textures[2];
    shrubTexture.loadFromFile("testShrub.png");

    // grass texture
    sf::Texture &grassTexture = textures[3];
    grassTexture.loadFromFile("testGrass.png");
    grassTexture.setRepeated(true);

    // self explanatory
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "runner game", sf::Style::Close);
    window.setFramerateLimit(100);
    // Player object
    Player player(sf::Vector2f(90, 95), sf::Vector2f(50, 200));

    // creates the collection of obstacles
    // we need to have pointers, copies don't work I tried
    vector<Obstacle *> obVect;

    // 96 is pixels per unit/block
    int generationCounter = 0;
    Spawner spawnerObj(9, 1, UNITSIZE, &textures[0], &obVect, &currSpeed);

    spawnerObj.spawnStartingGround();
    // player animation test
    Animation playerAnim(sf::Vector2f(500, 404), 10);

    while (window.isOpen()) {
        touchingGround = false;

        if (generationCounter == 0) {
            spawnerObj.cleanOutObstacles();
            spawnerObj.spawnNewGround();

            // 3 columns of blocks per generation
            generationCounter = 3 * (UNITSIZE / currSpeed);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // set each obstacles speed
        for (auto i : obVect) {
            i->setSpeed(currSpeed);
        }

        // move each obstacle
        for (auto i : obVect) {
            i->move(-i->getSpeed(), 0);
        }

        // clear the window before drawing stuff
        window.clear();

        // draw each obstacle
        for (auto i : obVect) {
            window.draw(*i);
        }

        // check if player collides with any obstacle
        for (auto i : obVect) {
            if (player.getGlobalBounds().intersects(i->getGlobalBounds())) {
                touchingGround = true;
            }
            //std::cout << "0: " << textures[0].getNativeHandle() << "\t1: " << textures[1].getNativeHandle() << "\t2: " << textures[2].getNativeHandle() << std::endl;
            // if touching the dirt, or any obstacles past score of 300 (invincibility window), end game
            if (player.getGlobalBounds().intersects(i->getGlobalBounds()) && score > 300 && (i->getTexture()->getNativeHandle() == textures[0].getNativeHandle() || i->getTexture()->getNativeHandle() == textures[1].getNativeHandle() || i->getTexture()->getNativeHandle() == textures[2].getNativeHandle()))
            {
                currSpeed = 0;
                gameOver = true;
            }
        }

        // update various items that should stop when the player dies
        if (!gameOver)
        {
            player.updateMovement(touchingGround);
            playerAnim.frameUpdate();
            score++;
            scoreText.setString(std::to_string(score));
        }

        playerAnim.setPosition(player.getPosition());

        generationCounter--;

        // draw each obstacle
        for (auto i : obVect) {
            window.draw(*i); 
        }

        // draw player
        //window.draw(player);
        window.draw(playerAnim);
        window.draw(scoreText);

        window.display();
    }

    return 0;
}