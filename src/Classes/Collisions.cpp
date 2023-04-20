#include "../Headers/Collisions.hpp"

bool Collisions::Intersection(sf::FloatRect boxOne, sf::FloatRect boxTwo)
{
  return boxOne.intersects(boxTwo);
}
