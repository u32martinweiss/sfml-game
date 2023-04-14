#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include <SFML/Graphics.hpp>

class Collisions
{
  public:
    static bool Intersection(sf::FloatRect boxOne, sf::FloatRect boxTwo);
};

#endif // COLLISIONS_HPP
