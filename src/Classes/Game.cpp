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
  // Player
  this->textureManager.add("player", loadTexture("assets/Textures/player.png"));

  // Buller
  this->textureManager.add("bullet", loadTexture("assets/Textures/bullet.png"));

  // Tiles
  this->textureManager.add("grass", loadTexture("assets/Textures/Tiles/grass.png"));
  this->textureManager.add("stone", loadTexture("assets/Textures/Tiles/stone.png"));
  this->textureManager.add("mexico", loadTexture("assets/Textures/Tiles/mexico.png"));
  this->textureManager.add("pvc", loadTexture("assets/Textures/Tiles/pvc.png"));
  this->textureManager.add("box", loadTexture("assets/Textures/Tiles/box.png"));
  
  // Items
  this->textureManager.add("coin-1", loadTexture("assets/Textures/Items/coin-1.png"));
  this->textureManager.add("xiao", loadTexture("assets/Textures/Items/xiao.png"));
  this->textureManager.add("ammo-box", loadTexture("assets/Textures/Items/ammo-box.png"));

  // Interface
  this->textureManager.add("heart-full", loadTexture("assets/Textures/Interface/heart-full.png"));
  this->textureManager.add("inventory-box", loadTexture("assets/Textures/Interface/inventory-box.png"));
  this->textureManager.add("inventory-box-active", loadTexture("assets/Textures/Interface/inventory-box-active.png"));
  this->textureManager.add("bullets", loadTexture("assets/Textures/Interface/bullets.png"));
}

void Game::initBackgroundRects()
{
  this->backgroundRects.push_back(BackgroundRect(
    sf::Vector2f(0.f, 0.f),
    sf::Vector2f(8 * TILE_SIZE, 8 * TILE_SIZE),
    &this->textureManager.get("grass")
  ));
  this->backgroundRects.push_back(BackgroundRect(
    sf::Vector2f(8 * TILE_SIZE, 0.f),
    sf::Vector2f(8 * TILE_SIZE, 8 * TILE_SIZE),
    &this->textureManager.get("stone")
  ));
  this->backgroundRects.push_back(BackgroundRect(
    sf::Vector2f(0.f, 8 * TILE_SIZE),
    sf::Vector2f(8 * TILE_SIZE, 8 * TILE_SIZE),
    &this->textureManager.get("mexico")
  ));
  this->backgroundRects.push_back(BackgroundRect(
    sf::Vector2f(8 * TILE_SIZE, 8 * TILE_SIZE),
    sf::Vector2f(8 * TILE_SIZE, 8 * TILE_SIZE),
    &this->textureManager.get("pvc")
  ));
}

void Game::initBlocks()
{
  for (int i = 0; i < 16; i++)
  {
    this->blocks.push_back(Block(
      sf::Vector2f(
        i * TILE_SIZE,
        0.f
      ),
      &this->textureManager.get("box")
    ));
  }

  for (int i = 0; i < 16; i++)
  {
    this->blocks.push_back(Block(
      sf::Vector2f(
        i * TILE_SIZE,
        15 * TILE_SIZE
      ),
      &this->textureManager.get("box")
    ));
  }

  for (int i = 1; i < 15; i++)
  {
    this->blocks.push_back(Block(
      sf::Vector2f(
        0.f,
        i * TILE_SIZE
      ),
      &this->textureManager.get("box")
    ));
  }

  for (int i = 1; i < 15; i++)
  {
    this->blocks.push_back(Block(
      sf::Vector2f(
        15 * TILE_SIZE,
        i * TILE_SIZE
      ),
      &this->textureManager.get("box")
    ));
  }
}

void Game::initItems()
{
  for (int i = 1; i < 15; i++)
  {
    this->items.push_back(Item(
      sf::Vector2f(
        i * TILE_SIZE,
        TILE_SIZE
      ),
      &this->textureManager.get("coin-1"),
      1,
      0
    ));
  }

  for (int i = 1; i < 15; i++)
  {
    this->items.push_back(Item(
      sf::Vector2f(
        i * TILE_SIZE,
        14 * TILE_SIZE
      ),
      &this->textureManager.get("ammo-box"),
      1,
      20
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

  // Version Text
  this->versionText.setFont(this->fontManager.get("terminus"));
  this->versionText.setFillColor(sf::Color::White);
  this->versionText.setCharacterSize(BASE_FONT_SIZE);
  this->versionText.setOutlineThickness(BASE_FONT_OUTLINE_THICKNESS);

  std::stringstream versionStream;
  versionStream << GAME_TITLE << '\n' << GAME_VERSION;
  this->versionText.setString(versionStream.str());

  // Item Count Text
  this->itemCountText.setFont(this->fontManager.get("terminus"));
  this->itemCountText.setFillColor(sf::Color::White);
  this->itemCountText.setCharacterSize(ITEM_FONT_SIZE);
  this->itemCountText.setOutlineThickness(BASE_FONT_OUTLINE_THICKNESS);

  // Bullet Count Text
  this->bulletCountText.setFont(this->fontManager.get("terminus"));
  this->bulletCountText.setFillColor(sf::Color::White);
  this->bulletCountText.setCharacterSize(ITEM_FONT_SIZE);
  this->bulletCountText.setOutlineThickness(BASE_FONT_OUTLINE_THICKNESS);

  this->playerInventory[PLAYER_INVENTORY_SIZE - 1].name = "xiao";
  this->playerInventory[PLAYER_INVENTORY_SIZE - 1].count = 7;
}

void Game::initInterface()
{
  this->heartShape.setTexture(&this->textureManager.get("heart-full"));
  this->heartShape.setSize(sf::Vector2f(HEART_SIZE, HEART_SIZE));
  this->inventoryBoxShape.setSize(sf::Vector2f(INVENTORY_BOX_SIZE, INVENTORY_BOX_SIZE));
  this->inventoryItemShape.setSize(sf::Vector2f(ITEM_SIZE, ITEM_SIZE));
  this->bulletsShape.setTexture(&this->textureManager.get("bullets"));
  this->bulletsShape.setSize(sf::Vector2f(22.f, 22.f));
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
  this->initInterface();
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

      case sf::Event::MouseWheelMoved:
        this->activeInventorySlot = this->activeInventorySlot + this->sfEvent.mouseWheel.delta;
        if (activeInventorySlot < 0) {
          this->activeInventorySlot = PLAYER_INVENTORY_SIZE - 1;
        } else if (activeInventorySlot >= PLAYER_INVENTORY_SIZE) {
          this->activeInventorySlot = 0;
        }
        break;

      default:
        break;
    }
  }
}

void Game::updateClocks()
{
  this->dt = this->dtClock.restart().asSeconds();
  this->bulletTime = this->bulletClock.getElapsedTime().asSeconds();
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

  // Inventory Keybindings
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) this->activeInventorySlot = 0;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) this->activeInventorySlot = 1;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) this->activeInventorySlot = 2;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) this->activeInventorySlot = 3;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) this->activeInventorySlot = 4;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) this->activeInventorySlot = 5;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)) this->activeInventorySlot = 6;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)) this->activeInventorySlot = 7;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)) this->activeInventorySlot = 8;

  this->player.move(finalMovementVector);
}

void Game::updateMouse()
{
  // Spawning Bullets
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->bulletTime > BULLET_RELOAD_TIME && this->playerBullets > 0)
  {
    sf::Vector2f mousePos(sf::Mouse::getPosition(*this->window));
    sf::Vector2f playerCenter(
      this->window->getSize().x / 2 + this->player.getBounds().width / 2,
      this->window->getSize().y / 2 + this->player.getBounds().height / 2
    );
    sf::Vector2f delta(mousePos + sf::Vector2f(BULLET_SIZE * 2, BULLET_SIZE * 2) - playerCenter);
    delta /= sqrtf(pow(delta.x, 2) + pow(delta.y, 2));

    this->bullets.push_back(
      Bullet(
        sf::Vector2f(
          this->player.getBounds().left + TILE_SIZE / 2 - BULLET_SIZE / 2,
          this->player.getBounds().top + TILE_SIZE / 2 - BULLET_SIZE / 2
        ),
        delta,
        &this->textureManager.get("bullet")
      )
    );
    this->bulletClock.restart();
    this->playerBullets--;
  }
}

void Game::updateBullets()
{
  for (int i = 0; i < this->bullets.size(); i++)
  {
    this->bullets[i].update();
    if (this->bullets[i].getDespawnTime() > 2)
    {
      this->bullets.erase(this->bullets.begin() + i);
    }
  }
}

void Game::updateIntersections()
{
  // Player and Item collisions
  auto itemIter = std::remove_if(this->items.begin(), this->items.end(), [&](Item& item) {
    if (Collisions::Intersection(player.getBounds(), item.getBounds()))
    {
      this->playerMoney += item.getMoneyValue();
      this->playerBullets += item.getAmmoValue();
      return true;
    }
    return false;
  });
  this->items.erase(itemIter, this->items.end());

  // Bullet and Block collisions
  for (Block block: this->blocks)
  {
    for (int i = 0; i < this->bullets.size(); i++)
    {
      if (Collisions::Intersection(block.getBounds(), this->bullets[i].getBounds()))
      {
        this->bullets.erase(this->bullets.begin() + i);
      }
    }
  }
}

void Game::updateCollisions()
{
  // Phyics information
  sf::FloatRect playerRect = this->player.getBounds();
  sf::Vector2f playerPosition = this->player.getPosition();
  sf::Vector2f playerMovement = this->player.getMovement();
  float movementSpeed = PLAYER_SPEED * this->dt;

  // Getting the player's future position
  sf::FloatRect futurePlayerRect = sf::FloatRect(
    playerPosition.x + playerMovement.x * this->dt,
    playerPosition.y + playerMovement.y * this->dt,
    playerRect.width,
    playerRect.height
  );

  for (const auto& block : this->blocks)
  {
    // Checking the current block intersects
    sf::FloatRect blockRect = block.getBounds();
    if (!futurePlayerRect.intersects(blockRect)) continue;
    sf::Vector2f overlap(
      std::min(futurePlayerRect.left + futurePlayerRect.width, blockRect.left + blockRect.width) - std::max(futurePlayerRect.left, blockRect.left),
      std::min(futurePlayerRect.top + futurePlayerRect.height, blockRect.top + blockRect.height) - std::max(futurePlayerRect.top, blockRect.top)
    );

    // Vertical Collision
    if (overlap.x > overlap.y) {
      if (playerPosition.y < blockRect.top) {
        // Below the Block
        player.moveTo(sf::Vector2f(playerRect.left, blockRect.top - blockRect.height));
        playerMovement.y = 0;
      } else {
        // Above the Block
        player.moveTo(sf::Vector2f(playerRect.left, blockRect.top + blockRect.height));
        playerMovement.y = 0;
      }
      continue;
    }

    // Horizontal Collision
    if (playerPosition.x < blockRect.left) {
      // Left to the Block
      player.moveTo(sf::Vector2f(blockRect.left - blockRect.width, playerRect.top));
      playerMovement.x = 0;
    } else {
      // Right to the Block
      player.moveTo(sf::Vector2f(blockRect.left + blockRect.width, playerRect.top));
      playerMovement.x = 0;
    }
  }

  // Updating the player's movement vector
  player.move(playerMovement);
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
    this->view.getCenter().x - this->view.getSize().x / 2 + TEXT_OFFSET,
    this->view.getCenter().y - this->view.getSize().y / 2 + TEXT_OFFSET
  ));

  // Version Text
  this->versionText.setPosition(sf::Vector2f(
    this->view.getCenter().x + this->view.getSize().x / 2 - this->versionText.getGlobalBounds().width - TEXT_OFFSET,
    this->view.getCenter().y - this->view.getSize().y / 2 + TEXT_OFFSET
  ));

  // Bullet Count Text
  this->bulletCountText.setPosition(sf::Vector2f(
    this->view.getCenter().x + this->view.getSize().x / 2 - this->bulletCountText.getGlobalBounds().width - this->bulletsShape.getGlobalBounds().width - TEXT_OFFSET - 8.f,
    this->view.getCenter().y + this->view.getSize().y / 2 - this->bulletCountText.getGlobalBounds().height - this->bulletsShape.getGlobalBounds().height
  ));
  this->bulletCountText.setString(std::to_string(this->playerBullets));
}

void Game::updateInventory()
{

}

void Game::update()
{
  this->updateSFMLEvent();
  this->updateClocks();
  this->updateKeys();
  this->updateMouse();
  this->updateBullets();
  this->updateCollisions();
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

void Game::renderBullets()
{
  for (Bullet bullet : this->bullets)
  {
    bullet.render(*this->window);
  }
}

void Game::renderInterface()
{
  for (int i = 0; i < this->playerHealth; i++)
  {
    this->heartShape.setPosition(sf::Vector2f(
      this->view.getCenter().x - this->view.getSize().x / 2 + TEXT_OFFSET + i * (HEART_SIZE + HEART_SIZE / 6.f),
      this->view.getCenter().y + this->view.getSize().y / 2 - this->heartShape.getGlobalBounds().width - TEXT_OFFSET - INVENTORY_BOX_SIZE - HEART_SIZE / 3.f
    ));
    this->window->draw(this->heartShape);
  }

  for (int i = 0; i < PLAYER_INVENTORY_SIZE; i++)
  {
    // Setting the inventory box texture
    this->inventoryBoxShape.setTexture(&this->textureManager.get(i == this->activeInventorySlot ? "inventory-box-active" : "inventory-box"));
  
    // Rendering the inventory boxes
    this->inventoryBoxShape.setPosition(sf::Vector2f(
      this->view.getCenter().x - this->view.getSize().x / 2 + TEXT_OFFSET + i * (INVENTORY_BOX_SIZE - 1.f),
      this->view.getCenter().y + this->view.getSize().y / 2 - this->inventoryBoxShape.getGlobalBounds().width - TEXT_OFFSET
    ));
    if (this->playerInventory[i].count > 0) {
      // Item count
      this->itemCountText.setString(std::to_string(this->playerInventory[i].count));
      this->itemCountText.setPosition(sf::Vector2f(
        this->inventoryBoxShape.getGlobalBounds().left + INVENTORY_BOX_SIZE - this->itemCountText.getGlobalBounds().width - 4.f,
        this->inventoryBoxShape.getGlobalBounds().top + INVENTORY_BOX_SIZE - this->itemCountText.getGlobalBounds().height - 4.f
      ));

      // Item texture
      this->inventoryItemShape.setTexture(&this->textureManager.get(this->playerInventory[i].name));
      this->inventoryItemShape.setPosition(sf::Vector2f(
        this->inventoryBoxShape.getGlobalBounds().left + (INVENTORY_BOX_SIZE - ITEM_SIZE) / 2,
        this->inventoryBoxShape.getGlobalBounds().top + (INVENTORY_BOX_SIZE - ITEM_SIZE) / 2
      ));
    } else {
      this->itemCountText.setString("");
    }

    // Rendering the inventory
    this->window->draw(this->inventoryBoxShape);
    this->window->draw(this->inventoryItemShape);
    this->window->draw(this->itemCountText);
  }

  this->bulletsShape.setPosition(sf::Vector2f(
    this->view.getCenter().x + this->view.getSize().x / 2 - this->bulletsShape.getGlobalBounds().width - TEXT_OFFSET,
    this->view.getCenter().y + this->view.getSize().y / 2 - this->bulletsShape.getGlobalBounds().height - TEXT_OFFSET
  ));
  this->window->draw(this->bulletsShape);
}

void Game::renderTexts()
{
  this->window->draw(this->debugText);
  this->window->draw(this->versionText);
  this->window->draw(this->bulletCountText);
}

void Game::render()
{
  this->window->clear();
  this->renderBackgroundRects();
  this->renderBlocks();
  this->renderItems();
  this->renderBullets();
  this->player.render(*this->window);
  this->renderInterface();
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
