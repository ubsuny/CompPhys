#include "Vector2.h"

Vector2::Vector2(double ix, double iy) {
    x_ = ix;
    y_ = iy;
}

Vector2& Vector2::set_x(double ix) {
    x_ = ix;
    return *this;
}

Vector2& Vector2::set_y(double iy) {
    y_ = iy;
    return *this;
}

double Vector2::x() const {
    return x_;
}

double Vector2::y() const {
    return y_;
}

Vector2 Vector2::operator + (Vector2 const& right) const {
    Vector2 retval(x_ + right.x(), y_ + right.y());
    return retval;
}

Vector2 Vector2::operator - (Vector2 const& right) const {
    Vector2 retval(x_ - right.x(), y_ - right.y());
    return retval;
}

Vector2& Vector2::operator += (Vector2 const& right) {
    x_ = x_ + right.x();
    y_ = y_ + right.y();
    return *this;
}

Vector2& Vector2::operator -= (Vector2 const& right) {
    x_ = x_ - right.x();
    y_ = y_ - right.y();
    return *this;
}
