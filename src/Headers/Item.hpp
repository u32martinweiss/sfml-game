#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>

#include "../Constants.hpp"

class Item
{
  private:
    sf::Texture* texture;
    sf::RectangleShape shape;

    // Initializers
    void initShape(sf::Vector2f position);

  public:
    // Constructor
    Item(sf::Vector2f position, sf::Texture* texture);

    // Functions
    void render(sf::RenderTarget &target);
};

#endif // ITEM_HPP
