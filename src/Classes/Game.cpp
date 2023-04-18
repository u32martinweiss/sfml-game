#include "../Constants.hpp"
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
  this->textureManager.add("grass", loadTexture("assets/Textures/Tiles/grass.png"));
  this->textureManager.add("stone", loadTexture("assets/Textures/Tiles/stone.png"));
  this->textureManager.add("mexico", loadTexture("assets/Textures/Tiles/mexico.png"));
  this->textureManager.add("pvc", loadTexture("assets/Textures/Tiles/pvc.png"));
  this->textureManager.add("coin-1", loadTexture("assets/Textures/Items/coin-1.png"));
  this->textureManager.add("box", loadTexture("assets/Textures/Tiles/box.png"));
}

void Game::initBackgroundRects()
{
  this->backgroundRects.push_back(BackgroundRect(
    sf::Vector2f(0.f, 0.f),
    sf::Vector2f(6 * TILE_SIZE, 6 * TILE_SIZE),
    &this->textureManager.get("grass")
  ));
  this->backgroundRects.push_back(BackgroundRect(
    sf::Vector2f(6 * TILE_SIZE, 0.f),
    sf::Vector2f(6 * TILE_SIZE, 6 * TILE_SIZE),
    &this->textureManager.get("stone")
  ));
  this->backgroundRects.push_back(BackgroundRect(
    sf::Vector2f(0.f, 6 * TILE_SIZE),
    sf::Vector2f(6 * TILE_SIZE, 6 * TILE_SIZE),
    &this->textureManager.get("mexico")
  ));
  this->backgroundRects.push_back(BackgroundRect(
    sf::Vector2f(6 * TILE_SIZE, 6 * TILE_SIZE),
    sf::Vector2f(6 * TILE_SIZE, 6 * TILE_SIZE),
    &this->textureManager.get("pvc")
  ));
}

void Game::initBlocks()
{
  for (int i = 0; i < 12; i++)
  {
    this->blocks.push_back(Block(
      sf::Vector2f(
        i * TILE_SIZE,
        0.f
      ),
      &this->textureManager.get("box")
    ));
  }
}

void Game::initItems()
{
  for (int i = 0; i < 12; i++)
  {
    this->items.push_back(Item(
      sf::Vector2f(
        i * TILE_SIZE,
        TILE_SIZE
      ),
      &this->textureManager.get("coin-1"),
      1
    ));
  }
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
  // Debug Text
  this->debugText.setFont(this->fontManager.get("terminus"));
  this->debugText.setFillColor(sf::Color::White);
  this->debugText.setCharacterSize(BASE_FONT_SIZE);
  this->debugText.setOutlineThickness(BASE_FONT_OUTLINE_THICKNESS); 	

  // Inventory Text
  this->inventoryText.setFont(this->fontManager.get("terminus"));
  this->inventoryText.setFillColor(sf::Color::White);
  this->inventoryText.setCharacterSize(BASE_FONT_SIZE);
  this->inventoryText.setOutlineThickness(BASE_FONT_OUTLINE_THICKNESS); 	

  // Version Text
  this->versionText.setFont(this->fontManager.get("terminus"));
  this->versionText.setFillColor(sf::Color::White);
  this->versionText.setCharacterSize(BASE_FONT_SIZE);
  this->versionText.setOutlineThickness(BASE_FONT_OUTLINE_THICKNESS);

  std::stringstream versionStream;
  versionStream << GAME_TITLE << '\n' << GAME_VERSION;
  this->versionText.setString(versionStream.str());
}

// Constructor and Destructor

Game::Game()
{
  this->initWindow();
  this->initTextures();
  this->initBackgroundRects();
  this->initBlocks();
  this->initItems();
  this->initFonts();
  this->initTexts();
  this->player.setTexture(&this->textureManager.get("player"));
}

Game::~Game()
{
  delete this->window;
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

void Game::updateIntersections()
{
  auto iter = std::remove_if(this->items.begin(), this->items.end(), [&](Item& item) {
    if (Collisions::Intersection(player.getBounds(), item.getBounds()))
    {
      this->playerMoney += item.getValue();
      return true;
    }
    return false;
  });

  this->items.erase(iter, this->items.end());
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
  int fps = round(1.f / this->dt);

  // Debug Text
  this->debugText.setString(
    "Position\n\nX: " + std::to_string(roundedPosition.x) + "\nY: " + std::to_string(roundedPosition.y) + "\n\nFPS: " + std::to_string(fps)
  );
  this->debugText.setPosition(sf::Vector2f(
    this->view.getCenter().x - this->view.getSize().x / 2 + 8.f,
    this->view.getCenter().y - this->view.getSize().y / 2 + 8.f
  ));

  // Inventory Text
  this->inventoryText.setPosition(sf::Vector2f(
    this->view.getCenter().x - this->view.getSize().x / 2 + 8.f,
    this->view.getCenter().y + this->view.getSize().y / 2 - this->inventoryText.getGlobalBounds().height - 8.f
  ));

  // Version Text
  this->versionText.setPosition(sf::Vector2f(
    this->view.getCenter().x + this->view.getSize().x / 2 - this->versionText.getGlobalBounds().width - 8.f,
    this->view.getCenter().y - this->view.getSize().y / 2 + 8.f
  ));
}

void Game::updateInventory()
{
  std::stringstream inventoryStream;
  inventoryStream << "Balance: " << this->playerMoney << " CZK\n\n";
  for (int i = 0; i < PLAYER_INVENTORY_SIZE; i++)
  {
    inventoryStream << i + 1 << ") " << this->playerInventory[i].name;
    if (i != PLAYER_INVENTORY_SIZE - 1) inventoryStream << '\n';
  }
  this->inventoryText.setString(inventoryStream.str());
}

void Game::update()
{
  this->updateSFMLEvent();
  this->updateClocks();
  this->updateKeys();
  this->player.update();
  this->updateIntersections();
  this->updateView();
  this->updateInventory();
  this->updateTexts();
}

// Render Functions

void Game::renderBackgroundRects()
{
  for (BackgroundRect backgroundRect : this->backgroundRects)
  {
    backgroundRect.render(*this->window);
  }
}

void Game::renderBlocks()
{
  for (Block block : this->blocks)
  {
    block.render(*this->window);
  }
}

void Game::renderItems()
{
  for (Item item : this->items)
  {
    item.render(*this->window);
  }
}

void Game::renderTexts()
{
  this->window->draw(this->debugText);
  this->window->draw(this->inventoryText);
  this->window->draw(this->versionText);
}

void Game::render()
{
  this->window->clear();
  this->renderBackgroundRects();
  this->renderBlocks();
  this->renderItems();
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
