#include "curve.hpp"

// constructors
Curve::Curve(std::vector<Vector2> points) {
  this->points = points;
  this->graph = std::vector<sf::Vertex>(points.size());
  this->approxGraph = std::vector<sf::Vertex>(points.size());

  this->coeffs = std::vector<Vector2>(points.size());

  if (points.size() > 0) finishCurve();
}

Curve::Curve() : Curve(std::vector<Vector2>(0)) {}

void Curve::reset() {
  this->points = std::vector<Vector2>(0);
  this->graph = std::vector<sf::Vertex>(0);
  this->approxGraph = std::vector<sf::Vertex>(0);
  this->coeffs = std::vector<Vector2>(0);
  this->tracer = std::vector<sf::Vertex>(0);

  finished = false;
  length = 0;
}

void Curve::finishCurve() {
  this->points.push_back(points[0]);
  this->finished = true;

  length = curveLength();

  this->graph = std::vector<sf::Vertex>(points.size());
  for (int i = 0; i < graph.size(); i++) {
    graph[i] = sf::Vertex(sf::Vector2f(points[i].x, points[i].y), graphColor);
  }
}

void Curve::addPoint(double x, double y) {
  if (finished) return;
  this->points.push_back(Vector2(x, y));
  this->graph.push_back(sf::Vertex(sf::Vector2f(x, y)));
}

// param of curve, map from [0, 1] -> curve
Vector2 Curve::param(double t) {

  double target = length * t;
  double pos = 0;

  int i = 0;
  
  while (pos + magnitude(points[i + 1] - points[i]) <= target) {
    pos += magnitude(points[i + 1] - points[i]);
    i++;
  }

  return points[i] + normalize(points[i + 1] - points[i]) * (target - pos);
}

void Curve::getApprox(int N, int M, int L) {

  Vector2* functionVals = new Vector2[N]();

  std::vector<Vector2> tempCoeffs = std::vector<Vector2>(2 * M + 1);
  std::vector<sf::Vertex> tempGraph = std::vector<sf::Vertex>(L);

  // get the function values
  for (int k = 0; k < N; k++)
    functionVals[k] = param(k / (double)(N));

  // get the values of the coefficients
  for (int n = -M; n <= M; n++) {

    Vector2 U(0, 0);

    for (int k = 0; k < N; k++) {
      U += functionVals[k].rot(-2 * PI * n * k / (double)N);
    }

    tempCoeffs[n + M] = U / (double)N;
  }

  for (int i = 0; i < L; i++) {

    double t = i / (double)(L-1);

    Vector2 V(0, 0);

    // approximate f(t)
    for (int n = -M; n <= M; n++)
      V += tempCoeffs[n + M].rot(2 * PI * n * t);

    tempGraph[i] = sf::Vertex(sf::Vector2f(V.x, V.y), approxGraphColor);
  }

  approxGraph = tempGraph;
  coeffs = tempCoeffs;

  delete[] functionVals;

  changed = true;
}

// calculates the length of the curve
double Curve::curveLength() {

  if (points.size() == 0) return 0;

  double length = 0;
  for (int i = 0; i < points.size() - 1; i++) {
    length += magnitude(points[i + 1] - points[i]);
  }
  return length;
}

void Curve::drawGraph(sf::RenderWindow* window) {
  window->draw(graph.data(), graph.size(), sf::LinesStrip);
}

void Curve::drawApproxGraph(sf::RenderWindow* window) {
  window->draw(approxGraph.data(), approxGraph.size(), sf::LinesStrip);
}

Vector2 Curve::drawArrows(double t, double zoom, sf::RenderWindow* window) {

  bool temp = changed;

  int M = (coeffs.size() - 1) / 2;

  if (M < 0) return Vector2(0,0);

  Vector2 v = coeffs[M].rot(2 * PI * 0 * t);
  sf::VertexArray lines(sf::LinesStrip, 2);
  lines[0].color = sf::Color(120, 40, 0);
  lines[1].color = sf::Color(120, 40, 0);

  sf::CircleShape circle;
  circle.setFillColor(sf::Color(0, 0, 0, 0));
  circle.setOutlineColor(sf::Color(120, 0, 0));
  circle.setOutlineThickness(zoom);
  circle.setPointCount(100);

  // draw circles and lines
  for (int i = 1; i <= M; i++) {

    circle.setPosition(sf::Vector2f(v.x, v.y));
    circle.setRadius(magnitude(coeffs[M + i]));
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    lines[0].position = sf::Vector2f(v.x, v.y);
    v += coeffs[M + i].rot(2 * PI * i * t);
    lines[1].position = sf::Vector2f(v.x, v.y);

    window->draw(lines);
    window->draw(circle);

    circle.setPosition(sf::Vector2f(v.x, v.y));
    circle.setRadius(magnitude(coeffs[M - i]));
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    lines[0].position = sf::Vector2f(v.x, v.y);
    v += coeffs[M - i].rot(2 * PI * -i * t);
    lines[1].position = sf::Vector2f(v.x, v.y);

    window->draw(lines);
    window->draw(circle);
  }

  // prevent change half way through method
  if (changed != temp) {
    tracer = std::vector<sf::Vertex>(0);
    return v;
  }

  // fix tracer if path has changed
  if (tracer.size() != tracerLength || changed) {
    changed = false;
    tracer = std::vector<sf::Vertex>(tracerLength);
    sf::Vertex vert = sf::Vertex(sf::Vector2f(v.x, v.y));
    for (int i = 0; i < tracerLength; i++) tracer[i] = vert;
  }

  // advance tracer
  tracer.erase(tracer.begin());
  tracer.push_back(sf::Vertex(sf::Vector2f(v.x, v.y)));

  // updater tracer colors
  for (int i = 0; i < tracer.size(); i++) {
    int r = std::min(std::max((int)approxGraphColor.r, i), 255);
    int g = std::min(std::max((int)approxGraphColor.g, i), 255);
    int b = std::min(std::max((int)approxGraphColor.b, i), 255);
    tracer[i].color = sf::Color(r, g, b);
  }

  window->draw(tracer.data(), tracer.size(), sf::LinesStrip);

  return v;
}

bool Curve::isFinished() { return finished; };