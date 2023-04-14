#ifndef ITEM_STRUCTS_HPP
#define ITEM_STRUCTS_HPP

#include <SFML/Graphics.hpp>
#include <string>

struct InventoryItem
{
  std::string name = "N/A";
  unsigned int value = 0;
};

#endif // ITEM_STRUCTS_HPP
