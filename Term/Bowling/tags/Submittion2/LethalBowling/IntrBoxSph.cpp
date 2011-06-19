#include "IntrBoxSph.h"

#include "TMath.h"

namespace Virgin
{


//----------------------------------------------------------------------------

bool TestIntersection (const Box& rkBox,
    const Sphere& rkSphere)
{
    // Test for intersection in the coordinate system of the box by
    // transforming the sphere into that coordinate system.
    Vector3 kCDiff = rkSphere.Center() - rkBox.Center();

    float fAx = Math::FAbs(kCDiff.Dot(rkBox.Axis(0)));
    float fAy = Math::FAbs(kCDiff.Dot(rkBox.Axis(1)));
    float fAz = Math::FAbs(kCDiff.Dot(rkBox.Axis(2)));
    float fDx = fAx - rkBox.Extent(0);
    float fDy = fAy - rkBox.Extent(1);
    float fDz = fAz - rkBox.Extent(2);

    if ( fAx <= rkBox.Extent(0) )
    {
        if ( fAy <= rkBox.Extent(1) )
        {
            if ( fAz <= rkBox.Extent(2) )
            {
                // sphere center inside box
                return true;
            }
            else
            {
                // potential sphere-face intersection with face z
                return fDz <= rkSphere.Radius();
            }
        }
        else
        {
            if ( fAz <= rkBox.Extent(2) )
            {
                // potential sphere-face intersection with face y
                return fDy <= rkSphere.Radius();
            }
            else
            {
                // potential sphere-edge intersection with edge formed
                // by faces y and z
                float fRSqr = rkSphere.Radius()*rkSphere.Radius();
                return fDy*fDy + fDz*fDz <= fRSqr;
            }
        }
    }
    else
    {
        if ( fAy <= rkBox.Extent(1) )
        {
            if ( fAz <= rkBox.Extent(2) )
            {
                // potential sphere-face intersection with face x
                return fDx <= rkSphere.Radius();
            }
            else
            {
                // potential sphere-edge intersection with edge formed
                // by faces x and z
                float fRSqr = rkSphere.Radius()*rkSphere.Radius();
                return fDx*fDx + fDz*fDz <= fRSqr;
            }
        }
        else
        {
            if ( fAz <= rkBox.Extent(2) )
            {
                // potential sphere-edge intersection with edge formed
                // by faces x and y
                float fRSqr = rkSphere.Radius()*rkSphere.Radius();
                return fDx*fDx + fDy*fDy <= fRSqr;
            }
            else
            {
                // potential sphere-vertex intersection at corner formed
                // by faces x,y,z
                float fRSqr = rkSphere.Radius()*rkSphere.Radius();
                return fDx*fDx + fDy*fDy + fDz*fDz <= fRSqr;
            }
        }
    }
}
//----------------------------------------------------------------------------

static float GetVertexIntersection (float fDx, float fDy, float fDz, float fVx,
    float fVy, float fVz, float fRSqr)
{
    // Finds the time of a 3D line-sphere intersection between a line
    // P = Dt, where P = (fDx, fDy, fDz) and D = (fVx, fVy, fVz) and
    // a sphere of radius^2 fRSqr.  Note: only valid if there is, in fact,
    // an intersection.

    float fVSqr = fVx*fVx + fVy*fVy + fVz*fVz;
    float fDot = fDx*fVx + fDy*fVy + fDz*fVz;
    float fDiff = fDx*fDx + fDy*fDy + fDz*fDz - fRSqr;
    float fInv = Math::InvSqrt(Math::FAbs(fDot*fDot-fVSqr*fDiff));
    return fDiff*fInv/(1.0f-fDot*fInv);
}
//----------------------------------------------------------------------------

static float GetEdgeIntersection (float fDx, float fDz, float fVx, float fVz,
    float fVSqr, float fRSqr)
{
    // Finds the time of a 2D line-circle intersection between a line
    // P = Dt where P = (fDx,fDz) and D = (fVx, fVz) and a circle of radius^2
    // fRSqr.  Note: only valid if there is, in fact, an intersection.

    float fDot = fVx*fDx + fVz*fDz;
    float fDiff = fDx*fDx + fDz*fDz - fRSqr;
    float fInv = Math::InvSqrt(Math::FAbs(fDot*fDot-fVSqr*fDiff));
    return fDiff*fInv/(1.0f-fDot*fInv);
}
//----------------------------------------------------------------------------

static int FindFaceRegionIntersection (float fEx, float fEy, float fEz, float fCx,
    float fCy, float fCz, float fVx, float fVy, float fVz, float& rfTFirst,
    float fRadius, float& rfIx, float& rfIy, float& rfIz, bool bAboveFace)
{
    // Returns when and whether a sphere in the region above face +Z
    // intersects face +Z or any of its vertices or edges.  The input
    // bAboveFace is true when the x and y coordinates are within the x and y
    // extents.  The function will still work if they are not, but it needs
    // to be false then, to avoid some checks that assume that x and y are
    // within the extents.  This function checks face z, and the vertex and
    // two edges that the velocity is headed towards on the face.

    // check for already intersecting if above face
    if ( fCz <= fEz + fRadius && bAboveFace )
    {
        rfTFirst = (float)0.0;
        return -1;
    }

    // check for easy out (moving away on Z axis)
    if ( fVz >= (float)0.0 )
        return 0;

    float fRSqr = fRadius*fRadius;

    float fVSqrX = fVz*fVz + fVx*fVx;
    float fVSqrY = fVz*fVz + fVy*fVy;
    float fDx, fDy, fDz = fCz - fEz;
    float fCrossX, fCrossY;
    int iXSign, iYSign;

    // This determines which way the box is heading and finds the values of
    // CrossX and CrossY which are positive if the sphere center will not
    // pass through the box.  Then it is only necessary to check two edges,
    // the face and the vertex for intersection.

    if ( fVx >= (float)0.0 )
    {
        iXSign = 1;
        fDx = fCx - fEx;
        fCrossX = fVx*fDz - fVz*fDx;
    }
    else
    {
        iXSign = -1;
        fDx = fCx + fEx;
        fCrossX = fVz*fDx - fVx*fDz;
    }

    if ( fVy >= (float)0.0 )
    {
        iYSign = 1;
        fDy = fCy - fEy;
        fCrossY = fVy*fDz - fVz*fDy;
    }
    else
    {
        iYSign = -1;
        fDy = fCy + fEy;
        fCrossY = fVz*fDy - fVy*fDz;
    }

    // does the circle intersect along the x edge?
    if ( fCrossX > fRadius*fVx*iXSign )
    {
        if ( fCrossX*fCrossX > fRSqr*fVSqrX )
        {
            // sphere overshoots box on the x-axis (either side)
            return 0;
        }

        // does the circle hit the y edge?
        if ( fCrossY > fRadius*fVy*iYSign )
        {
            // potential vertex intersection
            if ( fCrossY*fCrossY > fRSqr*fVSqrY )
            {
                // sphere overshoots box on the y-axis (either side)
                return 0;
            }

            Vector3 kVel(fVx,fVy,fVz);
            Vector3 kD(fDx,fDy,fDz);
            Vector3 kCross = kD.Cross(kVel);
            if ( kCross.SquaredLength() > fRSqr*kVel.SquaredLength() )
            {
                // sphere overshoots the box on the corner
                return 0;
            }

            rfTFirst = GetVertexIntersection(fDx,fDy,fDz,fVx,fVy,fVz,fRSqr);
            rfIx = fEx*iXSign;
            rfIy = fEy*iYSign;
        }
        else
        {
            // x-edge intersection
            rfTFirst = GetEdgeIntersection(fDx,fDz,fVx,fVz,fVSqrX,fRSqr);
            rfIx = fEx*iXSign;
            rfIy = fCy + fVy*rfTFirst;
        }
    }
    else
    {
        // does the circle hit the y edge?
        if ( fCrossY > fRadius*fVy*iYSign )
        {
            // potential y-edge intersection

            if ( fCrossY*fCrossY > fRSqr*fVSqrY )
            {
                // sphere overshoots box on the y-axis (either side)
                return 0;
            }

            rfTFirst = GetEdgeIntersection(fDy,fDz,fVy,fVz,fVSqrY,fRSqr);
            rfIx = fCx + fVx*rfTFirst;
            rfIy = fEy*iYSign;
        }
        else
        {
            // face intersection (easy)
            rfTFirst = (-fDz + fRadius)/fVz;
            rfIx = rfTFirst*fVx + fCx;
            rfIy = rfTFirst*fVy + fCy;
        }
    }

    // z coordinate of any intersection must be the face of z
    rfIz = fEz;
    return 1;
}
//----------------------------------------------------------------------------

static int FindJustEdgeIntersection (float fCy, float fEx, float fEy, float fEz,
    float fDx, float fDz, float fVx, float fVy, float fVz, float fRadius,
    float& rfTFirst, float& rfIx, float& rfIy, float& rfIz)
{
    // Finds the intersection of a point fDx and fDz away from an edge with
    // direction y.  The sphere is at a point fCy, and the edge is at the
    // point fEx.  Checks the edge and the vertex the velocity is heading
    // towards.

    float fRSqr = fRadius*fRadius;
    float fDy, fCrossZ, fCrossX;  // possible edge/vertex intersection
    int iSignY;

    // Depending on the sign of Vy, pick the vertex that the velocity is
    // heading towards on the edge, as well as creating fCrossX and fCrossZ
    // such that their sign will always be positive if the sphere center goes
    // over that edge.

    if ( fVy >= (float)0.0 )
    {
        iSignY = 1;
        fDy = fCy - fEy;
        fCrossZ = fDx*fVy - fDy*fVx;
        fCrossX = fDz*fVy - fDy*fVz;
    }
    else
    {
        iSignY = -1;
        fDy = fCy + fEy;
        fCrossZ = fDy*fVx - fDx*fVy;
        fCrossX = fDy*fVz - fDz*fVy;
    }

    // Check where on edge this intersection will occur
    if ( fCrossZ >= (float)0.0 && fCrossX >= (float)0.0 && 
         fCrossX*fCrossX + fCrossZ*fCrossZ > fVy*fVy*fRadius*fRadius )
    {
        // sphere potentially intersects with vertex
        Vector3 kVel(fVx,fVy,fVz);
        Vector3 kD(fDx,fDy,fDz);
        Vector3 kCross = kD.Cross(kVel);
        if ( kCross.SquaredLength() > fRSqr*kVel.SquaredLength() )
        {
            // sphere overshoots the box on the vertex
            return 0;
        }

        // sphere actually does intersect the vertex
        rfTFirst = GetVertexIntersection(fDx,fDy,fDz,fVx,fVy,fVz,fRSqr);
        rfIx = fEx;
        rfIy = iSignY*fEy;
        rfIz = fEz;
    }
    else
    {
        // sphere intersects with edge
        float fVSqrX = fVz*fVz + fVx*fVx;
        rfTFirst = GetEdgeIntersection(fDx,fDz,fVx,fVz,fVSqrX,fRSqr);
        rfIx = fEx;
        rfIy = fCy + rfTFirst*fVy;
        rfIz = fEz;
    }
    return 1;
}
//----------------------------------------------------------------------------

static int FindEdgeRegionIntersection (float fEx, float fEy, float fEz,
    float fCx, float fCy, float fCz, float fVx, float fVy, float fVz,
    float& rfTFirst, float fRadius, float& rfIx, float& rfIy, float& rfIz,
    bool bAboveEdge)
{
    // Assumes the sphere center is in the region above the x and z planes.
    // The input bAboveEdge is true when the y coordinate is within the y
    // extents.  The function will still work if it is not, but it needs to be
    // false then, to avoid some checks that assume that y is within the
    // extent.  This function checks the edge that the region is above, as
    // well as does a "face region" check on the face it is heading towards.

    float fDx = fCx - fEx;
    float fDz = fCz - fEz;
    float fRSqr = fRadius*fRadius;

    if ( bAboveEdge )
    {
        float fDiff = fDx*fDx + fDz*fDz - fRSqr;
        if ( fDiff <= (float)0.0 )
        {
            // circle is already intersecting the box
            rfTFirst = (float)0.0;
            return -1;
        }
    }

    float fDot = fVx*fDx + fVz*fDz;
    if ( fDot >= (float)0.0 )
    {
        // circle not moving towards box
        return 0;
    }

    // The value fKross splits the region of interest along the edge in the
    // middle of that region.
    float fKross = fVz*fDx - fVx*fDz; 
    if ( fKross >= (float)0.0 )
    {
        // sphere moving towards +z face
        if ( fVx >= (float)0.0 )
        {
            // passed corner, moving away from box
            return 0;
        }

        // Intersection with x-z edge.  If there is trouble with objects that
        // "scrape" the surface (velocity perpendicular to face normal, and
        // point of contact with a radius direction parallel to the face
        // normal), this check may need to be a little more inclusive (small
        // tolerance due to floating point errors) as the edge check needs
        // to get "scraping" objects (as they hit the edge with the point)
        // and the face region check will not catch it because the object is
        // not moving towards the face.
        if ( fKross <= -fRadius*fVx )
        {
            return FindJustEdgeIntersection(fCy,fEz,fEy,fEx,fDz,fDx,fVz,fVy,
                fVx,fRadius,rfTFirst,rfIz,rfIy,rfIx);
        }

        // now, check the face of z for intersections
        return FindFaceRegionIntersection(fEx,fEy,fEz,fCx,fCy,fCz,fVx,fVy,
            fVz,rfTFirst,fRadius,rfIx,rfIy,rfIz,false);
    }
    else
    {
        // sphere moving towards +x face
        if ( fVz >= (float)0.0 )
        {
            // passed corner, moving away from box
            return 0;
        }

        // Check intersection with x-z edge.  See the note above above
        // "scraping" objects.
        if ( fKross >= fRadius*fVz )
        {
            // possible edge/vertex intersection
            return FindJustEdgeIntersection(fCy,fEx,fEy,fEz,fDx,fDz,fVx,fVy,
                fVz,fRadius,rfTFirst,rfIx,rfIy,rfIz);
        }

        // now, check the face of x for intersections
        return FindFaceRegionIntersection(fEz,fEy,fEx,fCz,fCy,fCx,fVz,fVy,
            fVx,rfTFirst,fRadius,rfIz,rfIy,rfIx,false);
    }
}
//----------------------------------------------------------------------------

static int FindVertexRegionIntersection (float fEx, float fEy,  float fEz,
    float fCx, float fCy, float fCz, float fVx, float fVy, float fVz,
    float& rfTFirst, float fRadius, float& rfIx, float& rfIy, float& rfIz)
{
    // assumes the sphere is above the vertex +Ex, +Ey, +Ez

    float fDx = fCx - fEx;
    float fDy = fCy - fEy;
    float fDz = fCz - fEz;
    float fRSqr = fRadius*fRadius;
    float fDiff = fDx*fDx + fDy*fDy + fDz*fDz - fRSqr;
    if ( fDiff <= (float)0.0 )
    {
        // sphere is already intersecting the box
        rfTFirst = (float)0.0;
        return -1;
    }

    if ( fVx*fDx + fVy*fDy + fVz*fDz >= (float)0.0 )
    {
        // sphere not moving towards box
        return 0;
    }

    // The box can be divided up into 3 regions, which simplifies checking to
    // see what the sphere hits.  The regions are divided by which edge
    // (formed by the vertex and some axis) is closest to the velocity
    // vector.
    //
    // To check if it hits the vertex, look at the edge (E) it is going
    // towards.  Create a plane formed by the other two edges (with E as the
    // plane normal) with the vertex at the origin.  The intercept along an
    // axis, in that plane, of the line formed by the sphere center and the
    // velocity as its direction, will be fCrossAxis/fVEdge.  Thus, the
    // distance from the origin to the point in the plane that that line from
    // the sphere in the velocity direction crosses will be the squared sum
    // of those two intercepts.  If that sum is less than the radius squared,
    // then the sphere will hit the vertex otherwise, it will continue on
    // past the vertex.  If it misses, since it is known which edge the box
    // is near, the find edge region test can be used.
    //
    // Also, due to the constrained conditions, only those six cases (two for
    // each region, since fCrossEdge can be + or -) of signs of fCross values
    // can occur.
    //
    // The 3rd case will also pick up cases where D = V, causing a ZERO cross.

    float fCrossX = fVy*fDz - fVz*fDy;
    float fCrossY = fVx*fDz - fVz*fDx;
    float fCrossZ = fVy*fDx - fVx*fDy;
    float fCrX2 = fCrossX*fCrossX;
    float fCrY2 = fCrossY*fCrossY;
    float fCrZ2 = fCrossZ*fCrossZ;
    float fVx2 = fVx*fVx;
    float fVy2 = fVy*fVy;
    float fVz2 = fVz*fVz;

    // Intersection with the vertex?
    if ( fCrossY < (float)0.0
    &&   fCrossZ >= (float)0.0
    &&   fCrY2 + fCrZ2 <= fRSqr*fVx2
    
    ||   fCrossZ < (float)0.0
    &&   fCrossX < (float)0.0
    &&   fCrX2 + fCrZ2 <= fRSqr*fVy2
    
    ||   fCrossY >= (float)0.0
    &&   fCrossX >= 0
    &&   fCrX2 + fCrY2 <= fRSqr*fVz2 )
    {
        // standard line-sphere intersection
        rfTFirst = GetVertexIntersection(fDx,fDy,fDz,fVx,fVy,fVz,
            fRadius*fRadius);
        rfIx = rfTFirst*fVx + fCx;
        rfIy = rfTFirst*fVy + fCy;
        rfIz = rfTFirst*fVz + fCz;
        return 1;
    }
    else if ( fCrossY < (float)0.0 && fCrossZ >= (float)0.0 )
    {
        // x edge region, check y,z planes
        return FindEdgeRegionIntersection(fEy,fEx,fEz,fCy,fCx,fCz,fVy,fVx,
            fVz,rfTFirst,fRadius,rfIy,rfIx,rfIz,false);
    }
    else if ( fCrossZ < (float)0.0 && fCrossX < (float)0.0 )
    {
        // y edge region, check x,z planes
        return FindEdgeRegionIntersection(fEx,fEy,fEz,fCx,fCy,fCz,fVx,fVy,
            fVz,rfTFirst,fRadius,rfIx,rfIy,rfIz,false);
    }
    else // ( fCrossY >= 0 && fCrossX >= 0 )
    {
        // z edge region, check x,y planes
        return FindEdgeRegionIntersection(fEx,fEz,fEy,fCx,fCz,fCy,fVx,fVz,
            fVy,rfTFirst,fRadius,rfIx,rfIz,rfIy,false);        
    }
}
//----------------------------------------------------------------------------

bool FindIntersection (const Box& rkBox,
    const Vector3& rkBoxVelocity, const Sphere& rkSphere,
    const Vector3& rkSphVelocity, float& rfTFirst, float fTMax,
    int& riQuantity, Vector3& rkP)
{
    // Find intersections relative to the coordinate system of the box.
    // The sphere is transformed to the box coordinates and the velocity of
    // the sphere is relative to the box.
    Vector3 kCDiff = rkSphere.Center() - rkBox.Center();
    Vector3 kVel = rkSphVelocity - rkBoxVelocity;
    float fAx = kCDiff.Dot(rkBox.Axis(0));
    float fAy = kCDiff.Dot(rkBox.Axis(1));
    float fAz = kCDiff.Dot(rkBox.Axis(2));
    float fVx = kVel.Dot(rkBox.Axis(0));
    float fVy = kVel.Dot(rkBox.Axis(1));
    float fVz = kVel.Dot(rkBox.Axis(2));

    // flip coordinate frame into the first octant
    int iSignX = 1;
    if ( fAx < (float)0.0 )
    {
        fAx = -fAx;
        fVx = -fVx;
        iSignX = -1;
    }

    int iSignY = 1;
    if ( fAy < (float)0.0 )
    {
        fAy = -fAy;
        fVy = -fVy;
        iSignY = -1;
    }

    int iSignZ = 1;
    if ( fAz < (float)0.0 )
    {
        fAz = -fAz;
        fVz = -fVz;
        iSignZ = -1;
    }

    // intersection coordinates
    float fIx, fIy, fIz;
    int iRetVal;

    if ( fAx <= rkBox.Extent(0) )
    {
        if ( fAy <= rkBox.Extent(1) )
        {
            if ( fAz <= rkBox.Extent(2) )
            {
                // sphere center inside box
                rfTFirst = (float)0.0;
                riQuantity = 0;
                return false;
            }
            else
            {
                // sphere above face on axis Z
                iRetVal = FindFaceRegionIntersection(rkBox.Extent(0), 
                    rkBox.Extent(1),rkBox.Extent(2),fAx,fAy,fAz,fVx,fVy,fVz,
                    rfTFirst,rkSphere.Radius(),fIx,fIy,fIz,true);     
            }
        }
        else
        {
            if ( fAz <= rkBox.Extent(2) )
            {
                // sphere above face on axis Y
                iRetVal = FindFaceRegionIntersection(rkBox.Extent(0), 
                    rkBox.Extent(2),rkBox.Extent(1),fAx,fAz,fAy,fVx,fVz,fVy,
                    rfTFirst,rkSphere.Radius(),fIx,fIz,fIy,true);   
            }
            else
            {
                // sphere is above the edge formed by faces y and z
                iRetVal = FindEdgeRegionIntersection(rkBox.Extent(1), 
                    rkBox.Extent(0),rkBox.Extent(2),fAy,fAx,fAz,fVy,fVx,fVz,
                    rfTFirst,rkSphere.Radius(),fIy,fIx,fIz,true);
            }
        }
    }
    else
    {
        if ( fAy <= rkBox.Extent(1) )
        {
            if ( fAz <= rkBox.Extent(2) )
            {
                // sphere above face on axis X
                iRetVal = FindFaceRegionIntersection(rkBox.Extent(1),
                    rkBox.Extent(2),rkBox.Extent(0),fAy,fAz,fAx,fVy,fVz,fVx,
                    rfTFirst,rkSphere.Radius(),fIy,fIz,fIx,true);
            }
            else
            {
                // sphere is above the edge formed by faces x and z
                iRetVal = FindEdgeRegionIntersection(rkBox.Extent(0), 
                    rkBox.Extent(1),rkBox.Extent(2),fAx,fAy,fAz,fVx,fVy,fVz,
                    rfTFirst,rkSphere.Radius(),fIx,fIy,fIz,true);
            }
        }
        else
        {
            if ( fAz <= rkBox.Extent(2) )
            {
                // sphere is above the edge formed by faces x and y
                iRetVal = FindEdgeRegionIntersection(rkBox.Extent(0), 
                    rkBox.Extent(2),rkBox.Extent(1),fAx,fAz,fAy,fVx,fVz,fVy,
                    rfTFirst,rkSphere.Radius(),fIx,fIz,fIy,true);
            }
            else
            {
                // sphere is above the corner formed by faces x,y,z
                iRetVal = FindVertexRegionIntersection(rkBox.Extent(0),
                    rkBox.Extent(1),rkBox.Extent(2),fAx,fAy,fAz,fVx,fVy,fVz,
                    rfTFirst,rkSphere.Radius(),fIx,fIy,fIz);
            }
        }
    }

    if ( iRetVal != 1 || rfTFirst > fTMax )
    {
        riQuantity = 0;
        return false;
    }

    // calculate actual intersection (move point back into world coordinates)
    riQuantity = 1;
    rkP = rkBox.Center() + (iSignX*fIx)*rkBox.Axis(0) +
        (iSignY*fIy)*rkBox.Axis(1) + (iSignZ*fIz)*rkBox.Axis(2);
    return true;
}
//----------------------------------------------------------------------------

}
