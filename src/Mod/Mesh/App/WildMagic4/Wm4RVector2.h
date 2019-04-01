// Wild Magic Source Code
// David Eberly
// http://www.geometrictools.com
// Copyright (c) 1998-2007
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.  The license is available for reading at
// either of the locations:
//     http://www.gnu.org/copyleft/lgpl.html
//     http://www.geometrictools.com/License/WildMagicLicense.pdf
// The license applies to versions 0 through 4 of Wild Magic.
//
// Version: 4.0.0 (2006/06/28)

#ifndef WM4RVECTOR2_H
#define WM4RVECTOR2_H

#include "Wm4FoundationLIB.h"
#include "Wm4TRVector.h"

namespace Wm4
{

template <int ISIZE>
class RVector2 : public TRVector<2,ISIZE>
{
public:
    // construction
    RVector2 ();
    RVector2 (const RVector2& rkV);
    RVector2 (const TRVector<2,ISIZE>& rkV);
    RVector2 (const TRational<ISIZE>& rkX, const TRational<ISIZE>& rkY);

    // member access
    TRational<ISIZE> X () const;
    TRational<ISIZE>& X ();
    TRational<ISIZE> Y () const;
    TRational<ISIZE>& Y ();

    // assignment
    RVector2& operator= (const RVector2& rkV);
    RVector2& operator= (const TRVector<2,ISIZE>& rkV);

    // returns Dot(this,V)
    TRational<ISIZE> Dot (const RVector2& rkV) const;

    // returns (y,-x)
    RVector2 Perp () const;

    // returns Cross((x,y,0),(V.x,V.y,0)) = x*V.y - y*V.x
    TRational<ISIZE> DotPerp (const RVector2& rkV) const;

protected:
    using TRVector<2,ISIZE>::m_akTuple;
};

}

#include "Wm4RVector2.inl"


#endif

