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

Item::Item(sf::Vector2f position, sf::Texture* texture, unsigned int value)
{
  this->initShape(position);
  this->shape.setTexture(texture);
  this->value = value;
}

// Accessors

const sf::FloatRect Item::getBounds() const
{
  return this->shape.getGlobalBounds();
}

const unsigned int Item::getValue() const
{
  return this->value;
}

// Functions

void Item::render(sf::RenderTarget& target)
{
  target.draw(this->shape);
}
