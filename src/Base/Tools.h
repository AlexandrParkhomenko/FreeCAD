/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef BASE_TOOLS_H
#define BASE_TOOLS_H

#include "stdexport.h"
#include <functional>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <boost/signals2.hpp>
#include <QString>
#include <QObject>

namespace Base
{

template <class T>
struct iotaGen
{
public:
    T operator()() { return n++; }
    iotaGen(T v) : n(v) {}

private:
    T n;
};

// ----------------------------------------------------------------------------

template <class T>
class manipulator
{
    T i_;
    std::ostream& (*f_)(std::ostream&, T);

public:
    manipulator(std::ostream& (*f)(std::ostream&, T), T i) : i_(i), f_(f)
    {
    }
    friend std::ostream& operator<<( std::ostream& os, manipulator m)
    {
        return m.f_(os, m.i_);
    }
};

inline std::ostream& tabsN(std::ostream& os, int n)
{
    for (int i=0;i<n;i++)
        os << "\t";
    return os;
}

inline std::ostream& blanksN(std::ostream& os, int n)
{
    for (int i=0;i<n;i++)
        os << " ";
    return os;
}

inline manipulator<int> tabs(int n)
{
    return manipulator<int>(&tabsN, n);
}

inline manipulator<int> blanks(int n)
{
    return manipulator<int>(&blanksN, n);
}

// ----------------------------------------------------------------------------

template<class T>
inline T clamp (T num, T lower, T upper)
{
    return std::max<T>(std::min<T>(upper,num),lower);
}

template<class T>
inline T sgn (T t)
{
    if (t == 0)
        return T(0);
    else
        return (t > 0) ? T(1) : T(-1);
}

template<class T>
inline T toRadians(T d)
{
    return static_cast<T>((d*M_PI)/180.0);
}

template<class T>
inline T toDegrees(T r)
{
    return static_cast<T>((r/M_PI)*180.0);
}

template<class T>
inline T fmod(T numerator, T denominator)
{
    T modulo = std::fmod(numerator, denominator);
    return (modulo >= T(0)) ? modulo : modulo + denominator;
}

// ----------------------------------------------------------------------------

class BaseExport StopWatch
{
public:
    StopWatch();
    ~StopWatch();

    void start();
    int restart();
    int elapsed();
    std::string toString(int ms) const;

private:
    struct Private;
    Private* d;
};

// ----------------------------------------------------------------------------

template<typename Status, class Object>
class ObjectStatusLocker
{
public:
    ObjectStatusLocker(Status s, Object* o, bool value = true) : status(s), obj(o)
    { old_value = obj->testStatus(status); obj->setStatus(status, value); }
    ~ObjectStatusLocker()
    { obj->setStatus(status, old_value); }
private:
    Status status;
    Object* obj;
    bool old_value;
};

// ----------------------------------------------------------------------------

class StateLocker
{
public:
    StateLocker(bool& flag, bool value = true) : lock(flag)
    { old_value = lock; lock = value; }
    ~StateLocker()
    { lock = old_value; }
private:
    bool& lock;
    bool old_value;
};

// ----------------------------------------------------------------------------

class ConnectionBlocker {
    typedef boost::signals2::connection Connection;
    typedef boost::signals2::shared_connection_block ConnectionBlock;
    ConnectionBlock blocker;

public:
    ConnectionBlocker(Connection& c) : blocker(c) {
    }
    ~ConnectionBlocker() {
    }
};

// ----------------------------------------------------------------------------

struct BaseExport Tools
{
    static std::string getUniqueName(const std::string&, const std::vector<std::string>&,int d=0);
    static std::string addNumber(const std::string&, unsigned int, int d=0);
    static std::string getIdentifier(const std::string&);
    static std::wstring widen(const std::string& str);
    static std::string narrow(const std::wstring& str);
    static std::string escapedUnicodeFromUtf8(const char *s);
    static std::string escapedUnicodeToUtf8(const std::string& s);

    /**
     * @brief toStdString Convert a QString into a UTF-8 encoded std::string.
     * @param s String to convert.
     * @return A std::string encoded as UTF-8.
     */
    static inline std::string toStdString(const QString& s) { QByteArray tmp = s.toUtf8(); return std::string(tmp.constData(), tmp.size()); }

    /**
     * @brief fromStdString Convert a std::string encoded as UTF-8 into a QString.
     * @param s std::string, expected to be UTF-8 encoded.
     * @return String represented as a QString.
     */
    static inline QString fromStdString(const std::string & s) { return QString::fromUtf8(s.c_str(), s.size()); }
};


} // namespace Base

#endif // BASE_TOOLS_H
