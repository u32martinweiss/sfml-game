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

Bullet::Bullet(sf::Vector2f position, sf::Texture* texture)
{
  this->initShape(position);
  this->speed = BULLET_SPEED;
  this->shape.setTexture(texture);
}

// Functions

void Bullet::update()
{

}

void Bullet::render(sf::RenderTarget& target)
{
  target.draw(this->shape);
}
