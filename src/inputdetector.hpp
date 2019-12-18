#pragma once

#include <SFML/Graphics.hpp>

/* two classes KeyDetector and MouseDetector to simplify the input
 * handling for SFML
 */

//// __ KeyDetector object to handle keyboard inputs __ ////
class KeyDetector {
private:
  bool checkKey = true;

  // stores key to get inputs from
  sf::Keyboard::Key key;

public:
  KeyDetector(sf::Keyboard::Key key);

  // method to check for key presses returns true if key just typed
  bool typed();

  // method to get if key down
  bool down();
};

//// __ MouseDetector object to handle mouse inputs __ ////
class MouseDetector {
private:
  bool checkButton = true;

  // stores button to get inputs from
  sf::Mouse::Button button;

  // stores window
  sf::Window *window;

public:
  MouseDetector(sf::Mouse::Button button);

  MouseDetector(sf::Window* window);

  MouseDetector(sf::Mouse::Button button, sf::Window* window);

  // method to check for button clicks returns true if button just clicked
  bool clicked();

  // method to get if button down
  bool down();

  // method to get mouse position
  sf::Vector2i pos();

  // static method to get mouse position relative to a window
  static sf::Vector2i pos(sf::Window *window);
};
