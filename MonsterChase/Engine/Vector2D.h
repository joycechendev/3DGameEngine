#pragma once
class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(float i_x, float i_y) : x_coord(i_x), y_coord(i_y) {}

	// get x coordination of vector
	float x() const { return x_coord; }
	// get y coordination of vector
	float y() const { return y_coord; }

	// set x coordination of vector
	void set_x(const float i_x) { this->x_coord = i_x; }

	// set x coordination of vector
	void set_y(const float i_y) { this->y_coord = i_y; }

	// assignment operator
	void operator =(const Vector2D &vec);


	~Vector2D();

private:
	float x_coord;
	float y_coord;
};

Vector2D operator +(const Vector2D &lhs, const Vector2D &rhs);
bool operator ==(const Vector2D &lhs, const Vector2D &rhs);
bool operator !=(const Vector2D &lhs, const Vector2D &rhs);
float cross(const Vector2D &lhs, const Vector2D &rhs);
// dot product (result is scalar value)
float dot(const Vector2D &lhs, const Vector2D &rhs);