#pragma once

#include "Vector.h"
#include "TMath.h"

namespace Virgin 
{

class Geometric
{
public:
    static bool DoPenetrationCheck;

public:
    // 평면이 u, v, 그리고 ptOnPlane으로 구성되어 있음
    static float DistanceFromPointToPlane(Vector3 pt, Vector3 u, Vector3 v, Vector3 ptOnPlane)
    {
        Vector3 n = u.Cross(v);
        Vector3 PQ = pt - ptOnPlane;
    
        n.Normalize();

        return PQ.Dot(n);
    }

    static bool	IsPointOnFace(Vector3 pt, Vector3 f[4])
    {
	    Vector3 u, v, n;
	    Vector3 vList[4];
	    int i;
	    Vector3 p;

	    u = f[1] - f[0];
	    v = f[3] - f[0];
        n = u.Cross(v);
	
        if((Math::Abs(n.X) > Math::Abs(n.X)) && (Math::Abs(n.X) > Math::Abs(n.Z)))
	    {
            // flatten in yz plane
		    for(int i = 0; i < 4; i++)
		    {
			    vList[i].X = f[i].Y;	
			    vList[i].Y = f[i].Z;	
			    vList[i].Z = 0.0f;
		    }
		    p.X = pt.Y;
		    p.Y = pt.Z;
		    p.Z = 0.0f;

		    if(pnpoly(4, vList, p) == 1)
			    return true;
	    }
        else if((Math::Abs(n.Y) > Math::Abs(n.X)) && (Math::Abs(n.Y) > Math::Abs(n.Z)))
	    {
            // flatten in xz plane
		    for(i=0; i<4; i++)
		    {
			    vList[i].X = f[i].X;	
			    vList[i].Y = f[i].Z;	
			    vList[i].Z = 0.0f;
		    }
		    p.X = pt.X;
		    p.Y = pt.Z;
		    p.Z = 0.0f;

		    if(pnpoly(4, vList, p) == 1)
			    return true;
	    }
        else if((Math::Abs(n.Z) > Math::Abs(n.X)) && (Math::Abs(n.Z) > Math::Abs(n.Y)))
	    { 
            // flatten in xy plane
		    for(int i = 0; i < 4; i++)
		    {
			    vList[i].X = f[i].X;	
			    vList[i].Y = f[i].Y;	
			    vList[i].Z = 0.0f;
		    }
		    p.X = pt.X;
		    p.Y = pt.Y;
		    p.Z = 0.0f;

		    if(pnpoly(4, vList, p) == 1)
			    return true;
	    }

	    return false;
    }

    
    //------------------------------------------------------------------------//
    // Adapted from Rourke's Computational Geometry FAQ
    //------------------------------------------------------------------------//
    static int pnpoly(int npol, Vector3 *vlist, Vector3 p)
    {
	    int	i, j, c = 0;

	    for (i = 0, j = npol-1; i<npol; j = i++) {
		    if ((((vlist[i].Y <= p.Y) && (p.Y < vlist[j].Y)) ||
			     ((vlist[j].Y <= p.Y) && (p.Y < vlist[i].Y))) &&
			    (p.X < (vlist[j].X - vlist[i].X) * (p.Y - vlist[i].Y) / (vlist[j].Y - vlist[i].Y) + vlist[i].X))

		       c = !c;
	    }
	    return c;
    }


};

}
