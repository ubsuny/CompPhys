#ifndef Vector2_h
#define Vector2_h

class Vector2 {
public:
	Vector2(double ix=0., double iy=0.);

	Vector2& set_x(double ix);

	Vector2& set_y(double iy);

	double x() const;

	double y() const;

	Vector2 operator + (Vector2 const& right) const;

	Vector2 operator - (Vector2 const& right) const;

	Vector2& operator += (Vector2 const& right);

	Vector2& operator -= (Vector2 const& right);

private:
	double x_;
	double y_;
};

#endif
