#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>

template <typename T>
class Manager
{
  private:
    std::map<std::string, T> items;

  public:
    // Functions
    void add(std::string name, T item);
    T& get(std::string name);
};

#endif // MANAGER_HPP
