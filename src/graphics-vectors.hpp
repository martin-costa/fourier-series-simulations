#pragma once

#include <ostream>
#include <cmath>

// classes declared here
class Vector3;
class Vector2;

// 3d real vector
class Vector3 {
public:
  double x;
  double y;
  double z;

  // constructors
  Vector3(double x, double y, double z);

  Vector3(Vector2 v);

  Vector3();

  // standard vector space operations
  Vector3 operator+(Vector3 v);

  void operator+=(Vector3 v);

  Vector3 operator-(Vector3 v);

  Vector3 operator-();

  void operator-=(Vector3 v);

  Vector3 operator*(double a);

  void operator*=(double a);

  Vector3 operator/(double a);

  void operator/=(double a);

  // R^3 vector operations
  friend double magnitude(Vector3 v);

  friend Vector3 normalize(Vector3 v);

  friend Vector3 schur(Vector3 v, Vector3 u);

  friend double dot(Vector3 v, Vector3 u);

  friend Vector3 cross(Vector3 v, Vector3 u);

  Vector3 normalize();

  Vector3 schur(Vector3 v);

  Vector3 cross(Vector3 v);

  Vector3 rotX(double theta);
  Vector3 rotY(double theta);
  Vector3 rotZ(double theta);

  Vector3 rotateAbout(Vector3 v, double theta);

  // overload stream operator
  friend std::ostream& operator<<(std::ostream &stream, const Vector3& v);
};

// 2d real vector
class Vector2 {
public:
  double x;
  double y;

  // constructors
  Vector2(double x, double y);

  Vector2();

  // standard vector space operations
  Vector2 operator+(Vector2 v);

  void operator+=(Vector2 v);

  Vector2 operator-(Vector2 v);

  Vector2 operator-();

  void operator-=(Vector2 v);

  Vector2 operator*(double a);

  void operator*=(double a);

  Vector2 operator/(double a);

  void operator/=(double a);

  // R^2 vector operations
  friend double magnitude(Vector2 v);

  friend Vector2 normalize(Vector2 v);

  friend Vector2 schur(Vector2 v, Vector2 u);

  friend double dot(Vector2 v, Vector2 u);

  friend Vector3 cross(Vector2 v, Vector2 u);

  Vector2 normalize();

  Vector2 schur(Vector2 v);

  Vector2 rot(double theta);

  // overload stream operator
  friend std::ostream& operator<<(std::ostream &stream, const Vector2& v);
};
