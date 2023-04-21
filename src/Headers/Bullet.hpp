#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

#include "../Constants.hpp"
#include "Entity.hpp"

class Bullet : public Entity
{
  private:
  // Despawn Clock
    sf::Clock despawnClock;

    // Initializers
    void initShape(sf::Vector2f position);

  public:
    // Constructor
    Bullet(sf::Vector2f position, sf::Texture* texture);

    // Accessors
    const float getDespawnTime() const;

    // Functions
    void update();
    void render(sf::RenderTarget& target);
};

#endif // BULLET_HPP
