#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>
#include <libconfig.h++>

#include "../Constants.hpp"
#include "Player.hpp"
#include "BackgroundRect.hpp"
#include "Block.hpp"
#include "Item.hpp"
#include "Bullet.hpp"
#include "Collisions.hpp"
#include "Manager.hpp"
#include "../Structs/InventoryItem.hpp"

class Game
{
  private:
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::View view;

    // Environment
    std::vector<BackgroundRect> backgroundRects;
    std::vector<Block> blocks;
    std::vector<Item> items;
    std::vector<Bullet> bullets;

    // Player
    Player player;
    unsigned int playerMoney = 0;
    unsigned int playerHealth = 10;
    unsigned int playerBullets = 20;

    // Interface
    InventoryItem playerInventory[PLAYER_INVENTORY_SIZE];
    int activeInventorySlot = 0;
    sf::RectangleShape heartShape;
    sf::RectangleShape inventoryBoxShape;
    sf::RectangleShape inventoryItemShape;
    sf::RectangleShape bulletsShape;

    // Managers
    Manager<sf::Texture> textureManager;
    Manager<sf::Font> fontManager;

    // Texts
    sf::Text debugText;
    sf::Text versionText;
    sf::Text coinsText;
    sf::Text itemCountText;
    sf::Text bulletCountText;

    // Clocks
    sf::Clock dtClock;
    float dt;
    sf::Clock bulletClock;
    float bulletTime;

    // Initalizers
    void initWindow();
    void initTextures();
    void initBackgroundRects();
    void initBlocks();
    void initItems();
    void initFonts();
    void initTexts();
    void initInterface();

  public:
    // Constructor and Destructor
    Game();
    virtual ~Game();

    // Accessors
    const float getDt() const;

    // Update Functions
    void updateSFMLEvent();
    void updateClocks();
    void updateKeys();
    void updateMouse();
    void updateBullets();
    void updateIntersections();
    void updateCollisions();
    void updateView();
    void updateTexts();
    void updateInventory();
    void update();

    // Render Functions
    void renderBackgroundRects();
    void renderBlocks();
    void renderItems();
    void renderBullets();
    void renderInterface();
    void renderTexts();
    void render();

    // Functions
    void run();
};

#endif // GAME_H
