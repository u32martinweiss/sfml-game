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

Item::Item(sf::Vector2f position, sf::Texture* texture)
{
  this->initShape(position);
  this->shape.setTexture(texture);
}

// Functions

void Item::render(sf::RenderTarget& target)
{
  target.draw(this->shape);
}
