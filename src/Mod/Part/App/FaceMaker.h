/***************************************************************************
 *   Copyright (c) 2016 Victor Titov (DeepSOIC)      <vv.titov@gmail.com>  *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PART_FACEMAKER_H
#define PART_FACEMAKER_H

#include "stdexport.h"
#include <BRepBuilderAPI_MakeShape.hxx>
#include "Base/BaseClass.h"
#include <TopoDS_Wire.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Face.hxx>

#include <memory>

namespace Part
{

/**
 * @brief FaceMaker class is the base class for implementing various "smart"
 * face making routines. This was created to address the problem of multiple
 * private implementations of making faces with holes, which are quite complex.
 * The two most important facemaking routines then was: one in Part Extrude,
 * and one in PartDesign (there, it is used in every sketch-based feature).
 * Plus, another one (new) was needed for filling 2D offset.
 */
class Standard_EXPORT FaceMaker: public BRepBuilderAPI_MakeShape, public Base::BaseClass
{
    TYPESYSTEM_HEADER();

public:
    FaceMaker() {}
    virtual ~FaceMaker() {}

    virtual void addWire(const TopoDS_Wire& w);
    /**
     * @brief addShape: add another wire, edge, or compound. If compound is
     * added, its internals will be treated as isolated from the rest, and the
     * compounding structure of result will follow.
     * @param sh
     */
    virtual void addShape(const TopoDS_Shape& sh);
    /**
     * @brief useCompound: add children of compound to the FaceMaker. Note that
     * this is different from addShape(comp) - structure is lost. The compound
     * is NOT expanded recursively.
     * @param comp
     */
    virtual void useCompound(const TopoDS_Compound &comp);

    /**
     * @brief Face: returns the face (result). If result is not a single face,
     * throws Base::TypeError. (hint: use .Shape() instead)
     * @return
     */
    virtual const TopoDS_Face& Face();

    virtual void Build();

    //fails to compile, huh!
    //virtual const TopTools_ListOfShape& Generated(const TopoDS_Shape &S) override {throwNotImplemented();}
    //virtual const TopTools_ListOfShape& Modified(const TopoDS_Shape &S) override {throwNotImplemented();}
    //virtual Standard_Boolean IsDeleted(const TopoDS_Shape &S) override {throwNotImplemented();}

    static std::unique_ptr<FaceMaker> ConstructFromType(const char* className);
    static std::unique_ptr<FaceMaker> ConstructFromType(Base::Type type);

protected:
    std::vector<TopoDS_Shape> mySourceShapes; //wire or compound
    std::vector<TopoDS_Wire> myWires; //wires from mySourceShapes
    std::vector<TopoDS_Compound> myCompounds; //compounds, for recursive processing
    std::vector<TopoDS_Shape> myShapesToReturn;

    /**
     * @brief Build_Essence: build routine that can assume there is no nesting.
     *
     * Implementing instructions:
     * Add new faces (or whatever) to myShapesToReturn. The rest is done by
     * base class's Build(). Please ignore contents of myCompounds in
     * implementation. If special handling of nesting is required, override
     * whole Build().
     */
    virtual void Build_Essence() = 0;

    static void throwNotImplemented();
};

/**
 * @brief The FaceMakerPublic class: derive from it if you want the face maker to be listed in tools that allow choosing one.
 */
class Standard_EXPORT FaceMakerPublic : public FaceMaker
{
    TYPESYSTEM_HEADER();
public:
    virtual std::string getUserFriendlyName() const = 0;
    virtual std::string getBriefExplanation() const = 0;
};



/**
 * @brief The FaceMakerSimple class: make plane faces from all closed wires
 * supplied, ignoring overlaps.
 *
 * Strengths: can work with non-coplanar sets of wires. Will not make broken
 * faces if wires overlap*.
 *
 * Limitations: can't make faces with holes (will generate overlapping faces
 * instead). Can't make faces from nonplanar wires.
 *
 * * Compound of valid but overlapping faces is created. The compound is invalid
 * for BOPs, but the faces themselves are valid, provided that the source wires
 * are valid.
 */
class Standard_EXPORT FaceMakerSimple : public FaceMakerPublic
{
    TYPESYSTEM_HEADER_WITH_OVERRIDE();
public:
    virtual std::string getUserFriendlyName() const override;
    virtual std::string getBriefExplanation() const override;
protected:
    virtual void Build_Essence() override;
};


}//namespace Part
#endif // PART_FACEMAKER_H
