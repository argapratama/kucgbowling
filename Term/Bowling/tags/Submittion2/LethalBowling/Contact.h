#pragma once

#include "RigidBody.h"
#include "Vector.h"

namespace Virgin
{

struct Contact
{
    RigidBody* A;     // tetrahedron containing face
    RigidBody* B;     // tetrahedron containing vertex
    Vector3 PA;       // contact point for tetrahedron A
    Vector3 PB;       // contact point for tetrahedron B
    Vector3 N;        // outward unit-length normal to face
    Vector3 EA;       // edge from A
    Vector3 EB;       // edge from B
    bool isVFContact;  // true if vertex-face, false if edge-edge
};

}
