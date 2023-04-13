#include <SFML/Graphics.hpp>

// Constants
const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "SFML";

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
  sf::RectangleShape testShape(sf::Vector2f(40.f, 80.f));
  testShape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;

        default:
          break;
      }
    }

    window.clear();
    window.draw(testShape);
    window.display();
  }

  return 0;
}
