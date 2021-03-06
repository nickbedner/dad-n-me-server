#pragma once
#ifndef POSITION_H
#define POSITION_H

#include "memoryallocator.h"
//
#include <cstorage/map.h>
#include <cstorage/vector.h>
#include <ubermath/ubermath.h>

#include "core/entity.h"

struct Position {
  vec3 position;
  float direction;
  float width;
  float height;
  float scale;
};

//struct PositionComponentPsuedoDO {
//  struct Vector position;
//  struct Vector direction;
//  struct Vector width;
//  struct Vector height;
//  struct Vector scale;
//  struct Vector map_ref;
//};

#endif  // POSITION_H
