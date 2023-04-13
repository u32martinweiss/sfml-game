#include "../Headers/Game.hpp"

// Constants

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "SFML";
const unsigned int WINDOW_FPS    = 60;
const bool         WINDOW_VSYNC  = false;

// Constructor and Destructor

Game::Game()
{
  // Creating the SFML Window
  this->window = new sf::RenderWindow(
    sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
    WINDOW_TITLE,
    sf::Style::Titlebar | sf::Style::Close
  );
  this->window->setFramerateLimit(WINDOW_FPS);
  this->window->setVerticalSyncEnabled(WINDOW_VSYNC);
}

Game::~Game()
{
  delete this->window;
}

// Update Functions

void Game::updateSFMLEvent()
{
  while (this->window->pollEvent(this->sfEvent))
  {
    switch (this->sfEvent.type)
    {
      case sf::Event::Closed:
        this->window->close();
        break;

      default:
        break;
    }
  }
}

void Game::update()
{
  this->updateSFMLEvent();
}

// Render Functions

void Game::render()
{
  this->window->clear();
  this->window->display();
}

// Functions

void Game::run()
{
  // Game Loop
  while (this->window->isOpen())
  {
    this->update();
    this->render();
  }
}
