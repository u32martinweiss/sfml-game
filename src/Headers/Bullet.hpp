#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

#include "../Constants.hpp"
#include "Entity.hpp"

class Bullet : public Entity
{
  private:
    sf::Vector2f movement;

    // Despawn Clock
    sf::Clock despawnClock;

    // Initializers
    void initShape(sf::Vector2f position);

  public:
    // Constructor
    Bullet(sf::Vector2f position, const sf::Vector2f movement, sf::Texture* texture);

    // Accessors
    const float getDespawnTime() const;

    // Functions
    void update();
    void render(sf::RenderTarget& target);
};

#endif // BULLET_HPP
