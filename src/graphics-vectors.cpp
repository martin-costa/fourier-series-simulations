#include "graphics-vectors.hpp"

// ---------------------------- //
// Vector3 methods defined here //
// ---------------------------- //

// constructors
Vector3::Vector3(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3::Vector3(Vector2 v) {
  this->x = v.x;
  this->y = v.y;
  this->z = 0;
}


Vector3::Vector3() : Vector3(0, 0, 0) {}

// standard vector space operations
Vector3 Vector3::operator+(Vector3 v) {
  return Vector3(x + v.x, y + v.y, z + v.z);
}

void Vector3::operator+=(Vector3 v) {
  x += v.x;
  y += v.y;
  z += v.z;
}

Vector3 Vector3::operator-(Vector3 v) {
  return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator-() {
  return Vector3(-x, -y, -z);
}

void Vector3::operator-=(Vector3 v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

Vector3 Vector3::operator*(double a) {
  return Vector3(x * a, y * a, z * a);
}

void Vector3::operator*=(double a) {
  x *= a;
  y *= a;
  z *= a;
}

Vector3 Vector3::operator/(double a) {
  return Vector3(x / a, y / a, z / a);
}

void Vector3::operator/=(double a) {
  x /= a;
  y /= a;
  z /= a;
}

// R^3 vector operations
double magnitude(Vector3 v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 normalize(Vector3 v) {
   return v / magnitude(v);
}

Vector3 schur(Vector3 v, Vector3 u) {
  return Vector3(v.x * u.x, v.y * u.y, v.z * u.z);
}

double dot(Vector3 v, Vector3 u) {
  return v.x * u.x + v.y * u.y + v.z * u.z;
}

Vector3 cross(Vector3 v, Vector3 u) {
  return Vector3(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x);
}

Vector3 Vector3::normalize() {
  *this /= magnitude(*this);
  return *this;
}

Vector3 Vector3::schur(Vector3 v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;
  return *this;
}

Vector3 Vector3::cross(Vector3 v) {
  *this = Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  return *this;
}

Vector3 Vector3::rotX(double theta) {
  return Vector3(x, y * cos(theta) - z * sin(theta), y * sin(theta) + z * cos(theta));
}

Vector3 Vector3::rotY(double theta) {
  return Vector3(x * cos(theta) + z * sin(theta), y, -x * sin(theta) + z * cos(theta));
}

Vector3 Vector3::rotZ(double theta) {
  return Vector3(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta), z);
}

Vector3 Vector3::rotateAbout(Vector3 v, double theta) {
  double c = cos(theta);
  double s = sin(theta);

  double ux = (c + v.x * v.x * (1 - c)) * x + (v.x * v.y * (1 - c) - v.z * s) * y + (v.x * v.z * (1 - c) + v.y * s) * z;
  double uy = (v.y * v.x * (1 - c) + v.z * s) * x + (c + v.y * v.y * (1 - c)) * y + (v.y * v.z * (1 - c) - v.x * s) * z;
  double uz = (v.z * v.x * (1 - c) - v.y * s) * x + (v.z * v.y * (1 - c) + v.x * s) * y + (c + v.z * v.z * (1 - c)) * z;

  return Vector3(ux, uy, uz);
}

// overload stream operator
std::ostream& operator<<(std::ostream &stream, const Vector3& v) {
  return stream << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

// ---------------------------- //
// Vector2 methods defined here //
// ---------------------------- //

// constructors
Vector2::Vector2(double x, double y) {
  this->x = x;
  this->y = y;
}

Vector2::Vector2() : Vector2(0, 0) {}

// standard vector space operations
Vector2 Vector2::operator+(Vector2 v) {
  return Vector2(x + v.x, y + v.y);
}

void Vector2::operator+=(Vector2 v) {
  x += v.x;
  y += v.y;
}

Vector2 Vector2::operator-(Vector2 v) {
  return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator-() {
  return Vector2(-x, -y);
}

void Vector2::operator-=(Vector2 v) {
  x -= v.x;
  y -= v.y;
}

Vector2 Vector2::operator*(double a) {
  return Vector2(x * a, y * a);
}

void Vector2::operator*=(double a) {
  x *= a;
  y *= a;
}

Vector2 Vector2::operator/(double a) {
  return Vector2(x / a, y / a);
}

void Vector2::operator/=(double a) {
  x /= a;
  y /= a;
}

// R^2 vector operations
double magnitude(Vector2 v) {
  return sqrt(v.x * v.x + v.y * v.y);
}

Vector2 normalize(Vector2 v) {
   return v / magnitude(v);
}

Vector2 schur(Vector2 v, Vector2 u) {
  return Vector2(v.x * u.x, v.y * u.y);
}

double dot(Vector2 v, Vector2 u) {
  return v.x * u.x + v.y * u.y;
}

Vector3 cross(Vector2 v, Vector2 u) {
  return Vector3(0, 0, v.x * u.y - v.y * u.x);
}

Vector2 Vector2::normalize() {
  *this /= magnitude(*this);
  return *this;
}

Vector2 Vector2::schur(Vector2 v) {
  x *= v.x;
  y *= v.y;
  return *this;
}

Vector2 Vector2::rot(double theta) {

  return Vector2(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));
}

// overload stream operator
std::ostream& operator<<(std::ostream &stream, const Vector2& v) {
  return stream << "[" << v.x << ", " << v.y << "]";
}
