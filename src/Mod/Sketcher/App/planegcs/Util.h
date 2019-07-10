/***************************************************************************
 *   Copyright (c) Konstantinos Poulios      (logari81@gmail.com) 2011     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PLANEGCS_UTIL_H
#define PLANEGCS_UTIL_H

#include <vector>
#include <map>
#include <set>

namespace GCS
{
    typedef std::vector<double *> VEC_pD;
    typedef std::vector<double> VEC_D;
    typedef std::vector<int> VEC_I;
    typedef std::map<double *, double *> MAP_pD_pD;
    typedef std::map<double *, double> MAP_pD_D;
    typedef std::map<double *, int> MAP_pD_I;
    typedef std::set<double *> SET_pD;
    typedef std::set<int> SET_I;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

} //namespace GCS

#endif // PLANEGCS_UTIL_H
