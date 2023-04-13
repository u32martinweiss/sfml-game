#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
  protected:
    sf::Texture* texture;
    sf::RectangleShape shape;

    // Physics
    float speed;
    sf::Vector2f movement;

  public:
    // Mutators
    void setTexture(sf::Texture* texture);
    void setPosition(sf::Vector2f position);
    void setSpeed(const float newSpeed);

    // Accessors
    const sf::FloatRect getBounds() const;
    const sf::Vector2f getPosition() const;

    // Functions
    void move(sf::Vector2f movement);
    virtual void update() = 0;
    virtual void render(sf::RenderTarget &target) = 0;
};

#endif // ENTITY_HPP
