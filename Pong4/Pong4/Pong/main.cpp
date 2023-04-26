/*
Martin Hundrup, Gil Rezin, Phoenix Staley
CptS 122
4/26/23
Side-scrolling runner game in which the player must dodge obstacles and pits to survive. Press space to jump
*/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Animation.hpp"
#include "Grass.hpp"
#include "Cloud.hpp"
#include "Hurdle.hpp"
#include "Obstacle.hpp"
#include "Player.hpp"
#include "Spawner.hpp"

using std::vector;

int main() {

    ///song file
    sf::SoundBuffer songFile;
    songFile.loadFromFile("song.wav");

    ///death file
    sf::SoundBuffer deathFile;
    deathFile.loadFromFile("death.wav");

    /// background song
    sf::Sound song;
    song.setBuffer(songFile);
    song.setVolume(55);
    song.setLoop(true);
    song.play();

    /// death sound
    sf::Sound deathSFX;
    deathSFX.setBuffer(deathFile);
    bool hasPlayedDeath = false;
   
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

    // added cloud texture to the array of textures (pos 4)
    sf::Texture textures[5];

    // dirt texture
    sf::Texture &blockTexture = textures[0];
    blockTexture.loadFromFile("dirt.png");
    blockTexture.setRepeated(true);

    // tree texture
    sf::Texture &treeTexture = textures[1];
    treeTexture.loadFromFile("tree.png");
  
    // the speed at which obstacles should move
    double currSpeed = 4;
    bool touchingGround = false;

    // shrub texture
    sf::Texture &shrubTexture = textures[2];
    shrubTexture.loadFromFile("bush.png");

    // grass texture
    sf::Texture &grassTexture = textures[3];
    grassTexture.loadFromFile("grass.png");
    grassTexture.setRepeated(true);

    // cloud texture
    sf::Texture& cloudTexture = textures[4];
    cloudTexture.loadFromFile("cloud.png");

    // sky texture
    sf::Texture skyTexture;
    skyTexture.loadFromFile("sky.png");
    skyTexture.setRepeated(true);

    // title
    sf::Texture titleTexture;
    titleTexture.loadFromFile("title.png");
    Cloud title(sf::Vector2f(500, 200), titleTexture);

    // restart prompt
    sf::Texture restartTexture;
    restartTexture.loadFromFile("restart.png");
    Cloud restart(sf::Vector2f(350, 400), restartTexture);

    // self explanatory
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "runner game", sf::Style::Close);
    window.setFramerateLimit(100);
    // Player object
    Player player(sf::Vector2f(59, 95), sf::Vector2f(50, 200));

    // creates the collection of obstacles
    // we need to have pointers, copies don't work I tried
    vector<Obstacle *> obVect;

    // 96 is pixels per unit/block
    int generationCounter = 0;
    Spawner spawnerObj(9, 1, UNITSIZE, &textures[0], &obVect, &currSpeed);

    spawnerObj.spawnStartingGround();
    // player animation test
    Animation playerAnim(sf::Vector2f(500, 404), 10);

    // the sky stuff
    // i didn't make it a class because its just a static sprite
    sf::Sprite sky;
    sky.setTexture(skyTexture);
    sky.setTextureRect(sf::IntRect(0, 0, 1600, 1600));


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

        // update each object
        for (auto i : obVect) {
            i->frameUpdate(currSpeed);
        }

        // clear the window before drawing stuff
        window.clear();

        // draw the sky
        window.draw(sky);

        // draw each obstacle
        for (auto i : obVect) {
            window.draw(*i);
        }

        // check if player collides with any obstacle
        for (auto i : obVect) {
            if (player.getGlobalBounds().intersects(i->getGlobalBounds()) && !i->isCloud()) {
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
            playerAnim.frameUpdate(player.getVelocity());
            score++;
            scoreText.setString(std::to_string(score)); // update score
        }
        else { /// game over
            window.draw(restart);

            if (!hasPlayedDeath) {
                deathSFX.play();
                hasPlayedDeath = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                /// restart
                gameOver = false;
                
                hasPlayedDeath = false;
                obVect.clear();
                title.setPosition(sf::Vector2f(500, 200));
                spawnerObj.setHeight(9);

                spawnerObj.spawnStartingGround();
                spawnerObj.cleanOutObstacles();
             
                generationCounter = 1;
                currSpeed = 4;
                score = 0;
                player.setPosition(sf::Vector2f(50, 200));
            }
        }

        playerAnim.setPosition(player.getPosition() - sf::Vector2f(11,0)); // offset for hitbox

        generationCounter--;

        // draw each obstacle
        for (auto i : obVect) {
            window.draw(*i); 
        }

        title.frameUpdate(currSpeed);
        //window.draw(restart);
        // draw player
        //window.draw(player); // hitbox, debugging tool



        window.draw(title);
        window.draw(playerAnim);
        window.draw(scoreText);
        

        window.display();
    }

    return 0;
}