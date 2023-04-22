#include "../Headers/Bullet.hpp"
#include "../Headers/Game.hpp"

extern Game game;

// Initializers

void Bullet::initShape(sf::Vector2f position)
{
  this->shape.setSize(sf::Vector2f(BULLET_SIZE, BULLET_SIZE));
  this->shape.setPosition(position);
}

// Constructor

Bullet::Bullet(sf::Vector2f position, const sf::Vector2f movement, sf::Texture* texture)
{
  this->initShape(position);
  this->movement = movement;
  this->shape.setTexture(texture);
  this->speed = BULLET_SPEED;
}

// Accessors

const float Bullet::getDespawnTime() const
{
  return this->despawnClock.getElapsedTime().asSeconds();
}

// Functions

void Bullet::update()
{
  this->shape.move(this->movement * game.getDt() * BULLET_SPEED);
}

void Bullet::render(sf::RenderTarget& target)
{
  target.draw(this->shape);
}
