#include "Vector2D.h"
#include "Utility.h"
const Vector2D Vector2D::Zero;
std::ostream& operator<<(std::ostream &consoleOut, const Vector2D &vector2D) {
    consoleOut << "X: " << vector2D.x << ", Y: " << vector2D.y << std::endl;
    return consoleOut;
}
// IsEqual()
bool Vector2D::operator==(const Vector2D &vector2D) const {
    return (IsEqual(this->x, vector2D.x) && IsEqual(this->y, vector2D.y));
}
// IsNotEqual()
bool Vector2D::operator!=(const Vector2D &vector2D) const {
    return !(*this == vector2D);
}
Vector2D Vector2D::operator-() const {
    return (Vector2D(-x, -y));
}
Vector2D Vector2D::operator*(float scale) const {
    return Vector2D(scale * x, scale * y);
}
Vector2D Vector2D::operator/(float scale) const {
    assert(fabsf(scale) > EPSILON);
    return Vector2D(x / scale, y / scale);
}
Vector2D& Vector2D::operator*=(float scale) {
    *this = *this * scale;
    return *this;
}
Vector2D& Vector2D::operator/=(float scale) {
    *this = *this / scale;
    return *this;
}
Vector2D operator*(float scale, const Vector2D &vector2D) {
    return vector2D * scale;
}
Vector2D operator/(float scale, const Vector2D &vector2D) {
    return vector2D / scale;
}
Vector2D Vector2D::operator+(const Vector2D &vector2D) const {
    return Vector2D(x + vector2D.x, y + vector2D.y);
}
Vector2D Vector2D::operator-(const Vector2D &vector2D) const {
    return Vector2D(x - vector2D.x, y - vector2D.y);
}
Vector2D& Vector2D::operator+=(const Vector2D &vector2D) {
    *this = *this + vector2D;
    return *this;
}
Vector2D& Vector2D::operator-=(const Vector2D &vector2D) {
    *this = *this - vector2D;
    return *this;
}
float Vector2D::MagnitudeSquared() const {
    return ((x * x) + (y * y));
}
float Vector2D::Magnitude() const {
    return (sqrt(MagnitudeSquared()));
}
Vector2D Vector2D::GetUnitVector() const {
    float magintude = Magnitude();
    if (magintude > EPSILON) {
        return (*this / magintude);
    }
    else {
        return (Vector2D::Zero);
    }
}
Vector2D& Vector2D::Normalize() {
    float magintude = Magnitude();
    if (magintude > EPSILON) {
        *this /= magintude;
    }
    return *this;
}
float Vector2D::GetDistance(const Vector2D &vector2D) const {
    return (vector2D - *this).Magnitude();
}
float Vector2D::GetDotProduct(const Vector2D &vector2D) const {
    return (x * vector2D.x) + (y + vector2D.y);
}
Vector2D Vector2D::GetProjectionOnToOtherVector(
        const Vector2D &vector2D) const {
    // Get Unit Vector
    Vector2D unitVector = vector2D.GetUnitVector();
    float dotProduct = GetDotProduct(unitVector);
    return (vector2D * dotProduct);
}
float Vector2D::GetAngleBetween(const Vector2D &vector2D) {
    return acosf(GetUnitVector().GetDotProduct(vector2D.GetUnitVector()));
}

Vector2D Vector2D::GetReflectionVector(const Vector2D &normal) const {
    return (*this - (2 * GetProjectionOnToOtherVector(normal)));
}

void Vector2D::Rotate(float angle, const Vector2D &aroundPoint) {
    float cosine = cosf(angle);
    float sine = sinf(angle);
    Vector2D thisVector(this->x, this->y);
    thisVector -= aroundPoint;
    float xRotation = thisVector.x * cosine - thisVector.y * sine;
    float yRotation = thisVector.x * sine + thisVector.y * cosine;
    Vector2D rotatedVector = Vector2D(xRotation, yRotation);
    *this = rotatedVector + aroundPoint;
}

Vector2D Vector2D::RotationResult(float angle, const Vector2D &aroundPoint) {
    float cosine = cosf(angle);
    float sine = sinf(angle);
    Vector2D thisVector(this->x, this->y);
    thisVector -= aroundPoint;
    float xRotation = thisVector.x * cosine - thisVector.y * sine;
    float yRotation = thisVector.x * sine + thisVector.y * cosine;
    Vector2D rotatedVector = Vector2D(xRotation, yRotation);
    return (rotatedVector + aroundPoint);
}
