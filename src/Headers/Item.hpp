#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>

#include "../Constants.hpp"

class Item
{
  private:
    sf::Texture* texture;
    sf::RectangleShape shape;
    unsigned int moneyValue;
    unsigned int ammoValue;

    // Initializers
    void initShape(sf::Vector2f position);

  public:
    // Constructor
    Item(sf::Vector2f position, sf::Texture* texture, unsigned int moneyValue, unsigned int ammoValue);

    // Accessors
    const sf::FloatRect getBounds() const;
    const unsigned int getMoneyValue() const;
    const unsigned int getAmmoValue() const;

    // Functions
    void render(sf::RenderTarget &target);
};

#endif // ITEM_HPP
