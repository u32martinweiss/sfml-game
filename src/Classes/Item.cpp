#include "../Headers/Item.hpp"

// Initializers

void Item::initShape(sf::Vector2f position)
{
  this->shape.setSize(sf::Vector2f(ITEM_SIZE, ITEM_SIZE));
  this->shape.setPosition(sf::Vector2f(
    position.x + TILE_SIZE / 4,
    position.y + TILE_SIZE / 4
  ));
}

// Constructor

Item::Item(sf::Vector2f position, sf::Texture* texture, unsigned int moneyValue, unsigned int ammoValue)
{
  this->initShape(position);
  this->shape.setTexture(texture);
  this->moneyValue = moneyValue;
  this->ammoValue = ammoValue;
}

// Accessors

const sf::FloatRect Item::getBounds() const
{
  return this->shape.getGlobalBounds();
}

const unsigned int Item::getMoneyValue() const
{
  return this->moneyValue;
}

const unsigned int Item::getAmmoValue() const
{
  return this->ammoValue;
}

// Functions

void Item::render(sf::RenderTarget& target)
{
  target.draw(this->shape);
}
