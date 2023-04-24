#include "../Headers/Entity.hpp"

// Mutators

void Entity::setTexture(sf::Texture* texture)
{
  this->shape.setTexture(texture);
}

void Entity::setPosition(sf::Vector2f position)
{
  this->shape.setPosition(position);
}

void Entity::setSpeed(const float newSpeed)
{
  this->speed = newSpeed;
}

// Accessors

const sf::FloatRect Entity::getBounds() const
{
  return this->shape.getGlobalBounds();
}

const sf::Vector2f Entity::getPosition() const
{
  return this->shape.getPosition();
}

const sf::Vector2f Entity::getMovement() const
{
  return this->movement;
}

// Functions

void Entity::move(sf::Vector2f movement)
{
  this->movement = movement;
}

void Entity::moveTo(sf::Vector2f position)
{
  this->shape.setPosition(position);
}
