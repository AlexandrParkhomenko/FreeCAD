/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_TIMEINFO_H
#define BASE_TIMEINFO_H

//# NEED USING C++11

/*
#include "stdexport.h"

#include <stdio.h>
#if defined(FC_OS_BSD)
#include <sys/time.h>
#else
#include <sys/timeb.h>
#endif
#include <time.h>

#ifdef __GNUC__
# include <stdint.h>
#endif

#if defined(FC_OS_BSD)
struct timeb
{
    int64_t time;
    unsigned short millitm;
};
#endif

namespace Base
{
/// BaseClass class and root of the type system
class BaseExport TimeInfo
{

public:
    /// Construction
    TimeInfo();
    /// Destruction
    virtual ~TimeInfo();

    /// sets the object to the actual system time
    void setCurrent(void);
    void setTime_t (uint64_t seconds);

    uint64_t getSeconds(void) const; 
    unsigned short  getMiliseconds(void) const; 

    void operator =  (const TimeInfo &time); 
    bool operator == (const TimeInfo &time) const;
    bool operator != (const TimeInfo &time) const;

    bool operator <  (const TimeInfo &time) const;
    bool operator <= (const TimeInfo &time) const;
    bool operator >= (const TimeInfo &time) const;
    bool operator >  (const TimeInfo &time) const;

    static std::string currentDateTimeString();
    static std::string diffTime(const TimeInfo &timeStart,const TimeInfo &timeEnd = TimeInfo());
    static float diffTimeF(const TimeInfo &timeStart,const TimeInfo &timeEnd  = TimeInfo());
    bool isNull() const;
    static TimeInfo null();

protected:
    struct timeb timebuffer;
};


 inline uint64_t TimeInfo::getSeconds(void) const
 {
     return timebuffer.time;
 }

 inline unsigned short  TimeInfo::getMiliseconds(void) const
 {
     return timebuffer.millitm;
 } 

inline bool
TimeInfo::operator != (const TimeInfo &time) const
{
    return (timebuffer.time != time.timebuffer.time || timebuffer.millitm != time.timebuffer.millitm);
}

inline void
TimeInfo::operator = (const TimeInfo &time) 
{
    timebuffer = time.timebuffer;
}

inline bool
TimeInfo::operator == (const TimeInfo &time) const
{
    return (timebuffer.time == time.timebuffer.time && timebuffer.millitm == time.timebuffer.millitm);
}

inline bool
TimeInfo::operator <  (const TimeInfo &time) const
{
    if (timebuffer.time == time.timebuffer.time)
        return timebuffer.millitm < time.timebuffer.millitm;
    else
        return timebuffer.time < time.timebuffer.time;
}

inline bool
TimeInfo::operator <= (const TimeInfo &time) const
{
    if (timebuffer.time == time.timebuffer.time)
        return timebuffer.millitm <= time.timebuffer.millitm;
    else
        return timebuffer.time <= time.timebuffer.time;
}

inline bool
TimeInfo::operator >= (const TimeInfo &time) const
{
    if (timebuffer.time == time.timebuffer.time)
        return timebuffer.millitm >= time.timebuffer.millitm;
    else
        return timebuffer.time >= time.timebuffer.time;
}

inline bool
TimeInfo::operator >  (const TimeInfo &time) const
{
    if (timebuffer.time == time.timebuffer.time)
        return timebuffer.millitm > time.timebuffer.millitm;
    else
        return timebuffer.time > time.timebuffer.time;
}

} //namespace Base
*/

#endif // BASE_TIMEINFO_H

