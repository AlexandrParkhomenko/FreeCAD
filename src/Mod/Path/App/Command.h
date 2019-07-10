/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PATH_COMMAND_H
#define PATH_COMMAND_H

#include "stdexport.h"
#include <map>
#include <string>
#include "Base/Persistence.h"
#include "Base/Placement.h"
#include "Base/Vector3D.h"

namespace Path
{
    /** The representation of a cnc command in a path */
    class Standard_EXPORT Command : public Base::Persistence
    {
    TYPESYSTEM_HEADER();
    
    public:
        //constructors
        Command();
        Command(const char* name,
                const std::map<std::string,double>& parameters);
        ~Command();
        // from base class
        virtual unsigned int getMemSize (void) const;
        virtual void Save (Base::Writer &/*writer*/) const;
        virtual void Restore(Base::XMLReader &/*reader*/);
        
        // specific methods
        Base::Placement getPlacement (void) const; // returns a placement from the x,y,z,a,b,c parameters
        Base::Vector3d getCenter (void) const; // returns a 3d vector from the i,j,k parameters
        void setCenter(const Base::Vector3d&, bool clockwise=true); // sets the center coordinates and the command name
        std::string toGCode (int precision=6, bool padzero=true) const; // returns a GCode string representation of the command
        void setFromGCode (const std::string&); // sets the parameters from the contents of the given GCode string
        void setFromPlacement (const Base::Placement&); // sets the parameters from the contents of the given placement
        bool has(const std::string&) const; // returns true if the given string exists in the parameters
        Command transform(const Base::Placement); // returns a transformed copy of this command
        double getValue(const std::string &name) const; // returns the value of a given parameter
        void scaleBy(double factor); // scales the receiver - use for imperial/metric conversions

        // this assumes the name is upper case
        inline double getParam(const std::string &name) const {
            auto it = Parameters.find(name);
            return it==Parameters.end()?0.0:it->second;
        }

        // attributes
        std::string Name;
        std::map<std::string,double> Parameters;
    };
    
} //namespace Path

#endif // PATH_COMMAND_H
