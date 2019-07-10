/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


//# NEED USING C++11

/*

# include <sstream>
# include <QDateTime>

#include "TimeInfo.h"


using namespace Base;


TimeInfo::TimeInfo()
{
    setCurrent();
}

TimeInfo::~TimeInfo()
{
}


// **************************************************************************
// separator for other implementation aspects

void TimeInfo::setCurrent(void)
{
#if defined (FC_OS_BSD)
    struct timeval t;
    gettimeofday(&t, NULL);
    timebuffer.time = t.tv_sec;
    timebuffer.millitm = t.tv_usec / 1000;
#elif defined(FC_OS_WIN32)
    _ftime(&timebuffer);
#else
    ftime(&timebuffer);
#endif
}

void TimeInfo::setTime_t (uint64_t seconds)
{
    timebuffer.time = seconds;
}

std::string TimeInfo::currentDateTimeString()
{
    return QDateTime::currentDateTime().toTimeSpec(Qt::OffsetFromUTC)
        .toString(Qt::ISODate).toStdString();
}

std::string TimeInfo::diffTime(const TimeInfo &timeStart,const TimeInfo &timeEnd )
{
   std::stringstream str;
   str << diffTimeF(timeStart,timeEnd);
   return str.str();
}

float TimeInfo::diffTimeF(const TimeInfo &timeStart,const TimeInfo &timeEnd )
{
    int64_t ds = int64_t(timeEnd.getSeconds() - timeStart.getSeconds());
    int dms = int(timeEnd.getMiliseconds()) - int(timeStart.getMiliseconds());

    return float(ds) + float(dms) * 0.001;
}

TimeInfo TimeInfo::null()
{
    TimeInfo ti;
    ti.timebuffer.time = 0;
    ti.timebuffer.millitm = 0;
    return ti;
}

bool TimeInfo::isNull() const
{
    return (*this) == TimeInfo::null();
}
*/
