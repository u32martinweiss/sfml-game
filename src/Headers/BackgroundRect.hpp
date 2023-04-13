#ifndef BACKGROUNDRECT_HPP
#define BACKGROUNDRECT_HPP

#include <SFML/Graphics.hpp>

class BackgroundRect
{
  private:
    sf::RectangleShape shape;
    sf::Texture* texture;

    // Initializers
    void initShape(sf::Vector2f position, sf::Vector2f size);

  public:
    // Constructor
    BackgroundRect(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture);

    // Functions
    void render(sf::RenderTarget& target);
};

#endif // BACKGROUNDRECT_HPP
