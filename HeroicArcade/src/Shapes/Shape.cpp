/*
 * Shape.cpp
 *
 *  Created on: Dec 17, 2021
 *      Author: Jordan Hunt
 */

#include <Shape.h>

Shape::~Shape() {
    // TODO Auto-generated destructor stub
}

void Shape::MoveByDeltaOffset(const Vector2D &deltaOffset) {
    // For-each
    for (Vector2D &point : points) {
        point = point + deltaOffset;
    }
}
