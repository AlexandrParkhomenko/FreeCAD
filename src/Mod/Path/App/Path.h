/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PATH_Path_H
#define PATH_Path_H

#include "stdexport.h"
#include "Command.h"
//#include "Mod/Robot/App/kdl_cp/path_composite.hpp"
//#include "Mod/Robot/App/kdl_cp/frames_io.hpp"
#include "Base/Persistence.h"
#include "Base/Vector3D.h"

namespace Path
{

    /** The representation of a CNC Toolpath */
    
    class Standard_EXPORT Toolpath : public Base::Persistence
    {
        TYPESYSTEM_HEADER();
    
        public:
            Toolpath();
            Toolpath(const Toolpath&);
            ~Toolpath();
            
            Toolpath &operator=(const Toolpath&);
        
            // from base class
            virtual unsigned int getMemSize (void) const;
            virtual void Save (Base::Writer &/*writer*/) const;
            virtual void Restore(Base::XMLReader &/*reader*/);
            void SaveDocFile (Base::Writer &writer) const;
            void RestoreDocFile(Base::Reader &reader);
        
            // interface
            void clear(void); // clears the internal data
            void addCommand(const Command &Cmd); // adds a command at the end
            void insertCommand(const Command &Cmd, int); // inserts a command
            void deleteCommand(int); // deletes a command
            double getLength(void); // return the Length (mm) of the Path
            void recalculate(void); // recalculates the points
            void setFromGCode(const std::string); // sets the path from the contents of the given GCode string
            std::string toGCode(void) const; // gets a gcode string representation from the Path
            
            // shortcut functions
            unsigned int getSize(void) const { return vpcCommands.size(); }
            const std::vector<Command*> &getCommands(void) const { return vpcCommands; }
            const Command &getCommand(unsigned int pos)    const { return *vpcCommands[pos]; }
        
            // support for rotation
            const Base::Vector3d& getCenter() const { return center; }
            void setCenter(const Base::Vector3d &c);

            static const int SchemaVersion = 2;

        protected:
            std::vector<Command*> vpcCommands;
            Base::Vector3d center;
            //KDL::Path_Composite *pcPath;
            
        /*
        inline  KDL::Frame toFrame(const Base::Placement &To){
            return KDL::Frame(KDL::Rotation::Quaternion(To.getRotation()[0],
                                                        To.getRotation()[1],
                                                        To.getRotation()[2],
                                                        To.getRotation()[3]),
                                                        KDL::Vector(To.getPosition()[0],
                                                        To.getPosition()[1],
                                                        To.getPosition()[2]));
        }
        inline  Base::Placement toPlacement(const KDL::Frame &To){
            double x,y,z,w;
            To.M.GetQuaternion(x,y,z,w);
            return Base::Placement(Base::Vector3d(To.p[0],To.p[1],To.p[2]),Base::Rotation(x,y,z,w));
        } */
    };

} //namespace Path


#endif // PATH_Path_H
