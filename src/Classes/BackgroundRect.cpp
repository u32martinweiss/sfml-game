#include "../Headers/BackgroundRect.hpp"

// Initializers
void BackgroundRect::initShape(sf::Vector2f position, sf::Vector2f size)
{
  this->shape.setPosition(position);
  this->shape.setSize(size);
  this->shape.setTexture(this->texture);
  this->shape.setTextureRect(sf::IntRect(0.f, 0.f, size.x, size.y));
}

// Constructor

BackgroundRect::BackgroundRect(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture)
{
  this->texture = texture;
  this->texture->setRepeated(true);
  this->initShape(position, size);
}

// Functions

void BackgroundRect::render(sf::RenderTarget& target)
{
  target.draw(this->shape);
}
