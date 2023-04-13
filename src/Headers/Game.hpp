#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <libconfig.h++>

#include "../Constants.hpp"
#include "Player.hpp"
#include "Manager.hpp"

class Game
{
  private:
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::View view;

    // Player
    Player player;

    // Managers
    Manager<sf::Texture> textureManager;
    Manager<sf::Font> fontManager;

    // Texts
    sf::Text positionText;

    // Clocks
    sf::Clock dtClock;
    float dt;

    // Initalizers
    void initWindow();
    void initTextures();
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
    void updateView();
    void updateTexts();
    void update();

    // Render Functions
    void renderTexts();
    void render();

    // Functions
    void run();
};

#endif // GAME_H
