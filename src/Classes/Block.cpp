#include "../Headers/Block.hpp"

// Initializers

void Block::initShape(sf::Vector2f position)
{
  this->shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
  this->shape.setPosition(sf::Vector2f(
    position.x,
    position.y
  ));
}

// Constructor

Block::Block(sf::Vector2f position, sf::Texture* texture)
{
  this->initShape(position);
  this->shape.setTexture(texture);
}

// Functions

void Block::render(sf::RenderTarget& target)
{
  target.draw(this->shape);
}
