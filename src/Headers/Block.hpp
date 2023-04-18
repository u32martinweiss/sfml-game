#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>

#include "../Constants.hpp"

class Block
{
  private:
    sf::Texture* texture;
    sf::RectangleShape shape;

    // Initialzers
    void initShape(sf::Vector2f position);

  public:
    // Construcor
    Block(sf::Vector2f position, sf::Texture* texture);

    // Functions
    void render(sf::RenderTarget& target);
};

#endif // BLOCK_HPP
