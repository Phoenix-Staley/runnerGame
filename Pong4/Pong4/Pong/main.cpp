#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Animation.hpp"
#include "Grass.hpp"
#include "Hurdle.hpp"
#include "Obstacle.hpp"
#include "Spawner.hpp"

using std::vector;

int main() {
    int UNITSIZE = 96;

    srand(time(NULL));

    sf::Texture textures[4];

    // dirt texture
    sf::Texture &blockTexture = textures[0];
    blockTexture.loadFromFile("testDirt.png");
    blockTexture.setRepeated(true);

    // tree texture
    sf::Texture &treeTexture = textures[1];
    treeTexture.loadFromFile("testTree.png");
    // treeTexture.setRepeated(true);

    // shrub texture
    sf::Texture &shrubTexture = textures[2];
    shrubTexture.loadFromFile("testShrub.png");

    // grass texture
    sf::Texture &grassTexture = textures[3];
    grassTexture.loadFromFile("testGrass.png");
    grassTexture.setRepeated(true);

    // the speed at which obstacles should move
    double currSpeed = 2.5;
    double originalSpeed = currSpeed;

    // self explanatory
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "runner game");
    window.setFramerateLimit(100);

    // creates the collection of obstacles
    // we need to have pointers, copies don't work I tried
    vector<Obstacle *> obVect;

    // 96 is pixels per unit/block
    int generationCounter = 0;
    Spawner spawnerObj(9, 1, UNITSIZE, &textures[0], &obVect, &currSpeed);

    spawnerObj.spawnStartingGround();

    /// player animation test
    Animation player(sf::Vector2f(500, 404), 10);

    while (window.isOpen()) {
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

        // update animation frame
        player.frameUpdate();

        // clear the window before drawing stuff
        window.clear();

        // draw each obstacle
        for (auto i : obVect) {
            window.draw(*i);
        }

        window.draw(player);

        window.display();

        generationCounter--;
    }

    return 0;
}