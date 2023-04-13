#include "../Headers/Game.hpp"

// Initializers

void Game::initWindow()
{
  // Reading the window config file
  libconfig::Config windowConfig;
  try
  {
    windowConfig.readFile("config/Window.cfg");
  }
  catch (const libconfig::FileIOException &ioException)
  {
    std::cerr << "I/O error when reading the configuration file." << std::endl;
    return;
  }
  catch (const libconfig::ParseException &parseException)
  {
    std::cerr << "Parse error at " << parseException.getFile() << ": " << parseException.getLine()  << " - " << parseException.getError() << std::endl;
    return;
  }

  // Declaring the window properties as variables
  unsigned int windowWidth;
  unsigned int windowHeight;
  std::string windowTitle;
  unsigned int windowFps;
  bool windowVSync;

  // Loading the variables from the config file
  windowConfig.lookupValue("width", windowWidth);
  windowConfig.lookupValue("height", windowHeight);
  windowConfig.lookupValue("title", windowTitle);
  windowConfig.lookupValue("fps", windowFps);
  windowConfig.lookupValue("vsync", windowVSync);

  // Creating and setting up the window
  this->window = new sf::RenderWindow(
    sf::VideoMode(windowWidth, windowHeight),
    windowTitle,
    sf::Style::Titlebar | sf::Style::Close
  );
  this->window->setVerticalSyncEnabled(windowVSync);
  this->window->setFramerateLimit(windowFps);
  this->view.setSize(sf::Vector2f(windowWidth, windowHeight));
}

sf::Texture loadTexture(std::string path)
{
  sf::Texture loadedTexture;
  if (!loadedTexture.loadFromFile(path))
  {
    std::cout << "ERROR::GAME::CANT_LOAD_TEXTURE" << std::endl;
  }
  return loadedTexture;
}

void Game::initTextures()
{
  this->textureManager.add("player", loadTexture("assets/Textures/player.png"));
  this->textureManager.add("grass", loadTexture("assets/Textures/grass.png"));
}

sf::Font loadFont(std::string path)
{
  sf::Font loadedFont;
  if (!loadedFont.loadFromFile(path))
  {
    std::cout << "ERROR::GAME::CANT_LOAD_FONT" << std::endl;
  }
  return loadedFont;
}

void Game::initFonts()
{
  this->fontManager.add("terminus", loadFont("assets/Fonts/Terminus.ttf"));
}

void Game::initTexts()
{
  this->positionText.setFont(this->fontManager.get("terminus"));
  this->positionText.setFillColor(sf::Color::White);
  this->positionText.setCharacterSize(BASE_FONT_SIZE);
}

// Constructor and Destructor

Game::Game()
{
  this->initWindow();
  this->initTextures();
  this->initFonts();
  this->initTexts();
  this->player.setTexture(&this->textureManager.get("player"));

  this->mainBackgroundRect = new BackgroundRect(
    sf::Vector2f(0.f, 0.f),
    sf::Vector2f(TILE_SIZE * 12, TILE_SIZE * 12),
    &this->textureManager.get("grass")
  );
}

Game::~Game()
{
  delete this->window;
  delete this->mainBackgroundRect;
}

// Accessors

const float Game::getDt() const
{
  return this->dt;
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

      case sf::Event::Resized:
        this->view.setSize(sf::Vector2f(sfEvent.size.width, sfEvent.size.height));
        break;

      default:
        break;
    }
  }
}

void Game::updateClocks()
{
  this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateKeys()
{
  sf::Vector2f finalMovementVector;

  // WSAD Movement
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
  {
    finalMovementVector.y = -1;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
  {
    finalMovementVector.y = 1;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
  {
    finalMovementVector.x = -1;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    finalMovementVector.x = 1;
  }

  this->player.move(finalMovementVector);
}

void Game::updateView()
{
  // Centering the camera
  this->view.setCenter(sf::Vector2f(
    this->player.getBounds().left + this->player.getBounds().width / 2,
    this->player.getBounds().top + this->player.getBounds().height / 2
  ));
  this->window->setView(this->view);
}

void Game::updateTexts()
{
  sf::Vector2f playerPosition = this->player.getPosition();
  sf::Vector2i roundedPosition = sf::Vector2i(playerPosition);
  this->positionText.setString(
    "Position\n\nX: " + std::to_string(roundedPosition.x) + "\nY: " + std::to_string(roundedPosition.y)
  );
  this->positionText.setPosition(sf::Vector2f(
    this->view.getCenter().x - this->view.getSize().x / 2 + 8.f,
    this->view.getCenter().y - this->view.getSize().y / 2 + 8.f
  ));
}

void Game::update()
{
  this->updateSFMLEvent();
  this->updateClocks();
  this->updateKeys();
  this->player.update();
  this->updateView();
  this->updateTexts();
}

// Render Functions

void Game::renderTexts()
{
  this->window->draw(this->positionText);
}

void Game::render()
{
  this->window->clear();
  this->mainBackgroundRect->render(*this->window);
  this->player.render(*this->window);
  this->renderTexts();
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
