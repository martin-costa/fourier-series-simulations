#include "main.hpp"

int main() {

  // create the window for sfml
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Fourier Series", sf::Style::Titlebar);

  // set normal coord system ( (0,0) bottom-left and (WIDTH, HEIGHT) top-right )
  window.setView(sf::View(sf::FloatRect(0, HEIGHT, WIDTH, -HEIGHT)));

  std::thread inputThread = std::thread(updateApprox, &curve);

  // main loop of progam
  while (window.isOpen()) {

    sf::Event evnt;
    while (window.pollEvent(evnt)) { // check if program should close
      if (sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
    }

    framerate(FPS, false);

    mainLoop();

    window.display();
    window.clear(sf::Color::Black);
  }

  inputThread.detach();

  return 0;
}

void mainLoop() {

  static sf::Vector2i pos = leftMouse.pos();

  static float zoom = 1.0;

  // create a time variable
  static double timeSpeed = 1;
  static double time = 0;
  time += 0.0001 * timeSpeed;
  if (time > 1) time--;

  // speed up and slow down time
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) timeSpeed *= 0.95;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) timeSpeed *= 1.05;

  // move screen around
  if (rightMouse.down()) {
    sf::View view = window.getView();
    sf::Vector2f v(rightMouse.pos() - pos);
    view.move(-v.x * zoom, v.y * zoom);
    window.setView(view);
  }

  // zoom in
  if (shift.down()) {
    sf::View view = window.getView();
    view.zoom(1.02);
    window.setView(view);
    zoom *= 1.02;
  }

  // zoom out
  if (ctrl.down()) {
    sf::View view = window.getView();
    view.zoom(0.98);
    window.setView(view);
    zoom *= 0.98;
  }

  static bool makingCurve = false;
  if (leftMouse.clicked() && !curve.isFinished()) {
    makingCurve = true;
  }

  // draw the graph
  if (leftMouse.down()) {
    if (pos != leftMouse.pos()) {
      pos = leftMouse.pos();
      curve.addPoint(pos.x, HEIGHT - pos.y);
    }
  }
  else if (makingCurve && !curve.isFinished() && curve.points.size() > 0) {
    curve.finishCurve();
  }

  // reset the curve
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
    curve.reset();
    makingCurve = false;
    window.setView(sf::View(sf::FloatRect(0, HEIGHT, WIDTH, -HEIGHT)));
  }

  curve.drawGraph(&window);

  // draw the approximate graph
  if (curve.isFinished())
    curve.drawApproxGraph(&window);

  Vector2 arrowEnd = curve.drawArrows(time, zoom, &window);

  // lock on drawing point
  static KeyDetector P(sf::Keyboard::Key::P);
  if (P.down()) {
    sf::View view = window.getView();
    view.setCenter(sf::Vector2f(arrowEnd.x, arrowEnd.y));
    window.setView(view);
  }

  pos = leftMouse.pos();
}

void updateApprox(Curve* curve) {

  int n;

  while (true) {
    std::cout << "params: ";
    std::cin >> n;

    if (curve->isFinished()) {
      curve->getApprox(10000, n, 4000);
      //sf::sleep(sf::seconds(2 / (float)n));
    }
  }
}