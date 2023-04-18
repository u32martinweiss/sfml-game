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

    // Player
    Player player;
    InventoryItem playerInventory[PLAYER_INVENTORY_SIZE];
    unsigned int playerMoney = 0;

    // Managers
    Manager<sf::Texture> textureManager;
    Manager<sf::Font> fontManager;

    // Texts
    sf::Text debugText;
    sf::Text inventoryText;
    sf::Text versionText;

    // Clocks
    sf::Clock dtClock;
    float dt;

    // Initalizers
    void initWindow();
    void initTextures();
    void initBackgroundRects();
    void initBlocks();
    void initItems();
    void initFonts();
    void initTexts();

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
    void updateIntersections();
    void updateView();
    void updateTexts();
    void updateInventory();
    void update();

    // Render Functions
    void renderBackgroundRects();
    void renderBlocks();
    void renderItems();
    void renderTexts();
    void render();

    // Functions
    void run();
};

#endif // GAME_H
