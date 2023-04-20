#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>

#include "../Constants.hpp"

class Item
{
  private:
    sf::Texture* texture;
    sf::RectangleShape shape;
    unsigned int value;

    // Initializers
    void initShape(sf::Vector2f position);

  public:
    // Constructor
    Item(sf::Vector2f position, sf::Texture* texture, unsigned int value);

    // Accessors
    const sf::FloatRect getBounds() const;
    const unsigned int getValue() const;

    // Functions
    void render(sf::RenderTarget &target);
};

#endif // ITEM_HPP
