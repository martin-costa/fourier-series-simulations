#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "graphics-vectors.hpp"

#define PI 3.14159265359

class Curve {
private:

  double length;

  bool finished;

  bool changed = false;

public:

  // the points that define the curve
  std::vector<Vector2> points;

  // the graph of the curve
  std::vector<sf::Vertex> graph;

  sf::Color graphColor = sf::Color(35, 35, 35);

  // the graph of an appromiation of the curve
  std::vector<sf::Vertex> approxGraph;

  sf::Color approxGraphColor = sf::Color(100, 100, 100);

  std::vector<sf::Vertex> tracer;

  int tracerLength = 255;

  // lengths of rotating vectors in approximation
  std::vector<Vector2> coeffs;

  // constructors
  Curve(std::vector<Vector2> points);

  Curve();

  void reset();

  void finishCurve();

  void addPoint(double x, double y);

  // param of the curve, map p:[0, 1] --> C
  Vector2 param(double t);

  // sets vertices to a fourier approximation
  void getApprox(int N, int M, int L);

  // calculates the length of the curve
  double curveLength();

  void drawGraph(sf::RenderWindow* window);

  void drawApproxGraph(sf::RenderWindow* window);

  Vector2 drawArrows(double t, double zoom, sf::RenderWindow* window);

  bool isFinished();
};