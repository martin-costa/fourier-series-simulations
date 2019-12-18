#include <SFML/Graphics.hpp>

#include <iostream>
#include <thread>

#include "framerate.hpp"
#include "inputdetector.hpp"
#include "curve.hpp"

#define WIDTH 1600
#define HEIGHT 900

#define FPS 60

int main();

void mainLoop();

void updateApprox(Curve* curve);

sf::RenderWindow window;

Curve curve;

MouseDetector leftMouse(sf::Mouse::Button::Left, &window);
MouseDetector rightMouse(sf::Mouse::Button::Right, &window);

KeyDetector ctrl(sf::Keyboard::Key::LControl);
KeyDetector shift(sf::Keyboard::Key::LShift);