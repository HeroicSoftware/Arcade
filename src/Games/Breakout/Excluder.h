/*
 * Excluder.h
 *
 *  Created on: Jan 31, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_EXCLUDER_H_
#define GAMES_EXCLUDER_H_

#include "AxisAlignedRectangle.h"
#include "BoundaryEdge.h"
#include "Utility.h"
#include <cassert>
#include <cmath>

// Makes sure objects don't go inside of other objects
class Excluder
{
public:
  void Initialize(const AxisAlignedRectangle &rectangle, bool reverseNormals = false);
  bool HasCollided(const AxisAlignedRectangle &rectangle, BoundaryEdge &boundaryEdge) const;
  Vector2D GetCollisionOffset(const AxisAlignedRectangle &rectangle) const;
  inline const AxisAlignedRectangle &GetRectangle() const
  {
    return rectangle;
  }
  void MoveBy(const Vector2D &delta);
  void MoveTo(const Vector2D &point);
  const BoundaryEdge &GetEdge(EdgeType edge) const;

  Excluder();
  virtual ~Excluder();

private:
  AxisAlignedRectangle rectangle;
  BoundaryEdge edges[NUMBER_OF_EDGES];
  void CreateEdges();
  bool reverseNormals;
};

#endif /* GAMES_EXCLUDER_H_ */
