/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PATH_TOOLTABLE_H
#define PATH_TOOLTABLE_H

#include "stdexport.h"
#include <vector>
#include <string>
#include <map>
#include "Base/Persistence.h"

namespace Path
{

    /** The representation of a single tool */
    class Standard_EXPORT Tool : public Base::Persistence
    {
    TYPESYSTEM_HEADER();

    public:
        enum ToolType {
            UNDEFINED,
            DRILL,
            CENTERDRILL,
            COUNTERSINK,
            COUNTERBORE,
            FLYCUTTER,
            REAMER,
            TAP,
            ENDMILL,
            SLOTCUTTER,
            BALLENDMILL,
            CHAMFERMILL,
            CORNERROUND,
            ENGRAVER };

        enum ToolMaterial {
            MATUNDEFINED,
            HIGHSPEEDSTEEL,
            HIGHCARBONTOOLSTEEL,
            CASTALLOY,
            CARBIDE,
            CERAMICS,
            DIAMOND,
            SIALON };

        //constructors
        Tool();
        Tool(const char* name,
             ToolType type=Tool::UNDEFINED,
             ToolMaterial material=Tool::MATUNDEFINED,
             double diameter=10.0,
             double lengthoffset=100,
             double flatradius=0,
             double cornerradius=0,
             double cuttingedgeangle=0,
             double cuttingedgeheight=0);
        ~Tool();

        // from base class
        virtual unsigned int getMemSize (void) const;
        virtual void Save (Base::Writer &/*writer*/) const;
        virtual void Restore(Base::XMLReader &/*reader*/);

        // attributes
        std::string Name;
        ToolType Type;
        ToolMaterial Material;
        double Diameter;
        double LengthOffset;
        double FlatRadius;
        double CornerRadius;
        double CuttingEdgeAngle;
        double CuttingEdgeHeight;

        static const std::vector<std::string> ToolTypes(void);
        static const std::vector<std::string> ToolMaterials(void);
        static const char* TypeName(ToolType typ);
        static ToolType getToolType(std::string type);
        static ToolMaterial getToolMaterial(std::string mat);
        static const char* MaterialName(ToolMaterial mat);
    };

    /** The representation of a table of tools */
    class Standard_EXPORT Tooltable : public Base::Persistence
    {
    TYPESYSTEM_HEADER();

    public:
        //constructors
        Tooltable();
        ~Tooltable();

        // from base class
        virtual unsigned int getMemSize (void) const;
        virtual void Save (Base::Writer &/*writer*/) const;
        virtual void Restore(Base::XMLReader &/*reader*/);

        // new functions
        void addTool(const Tool &tool); // adds a tool at the end
        void setTool(const Tool &tool, int); // inserts a tool
        void deleteTool(int); // deletes a tool

        // auto
        unsigned int getSize(void) const {return Tools.size();}
        const Tool &getTool(int pos) {return *Tools[pos];}
        const std::map<int,Tool*> &getTools(void) const {return Tools;}
        bool hasTool(int pos) const {return (Tools.count(pos) != 0);}

        // attributes
        std::map<int,Tool*> Tools;
    };

} //namespace Path

#endif // PATH_TOOLTABLE_H
