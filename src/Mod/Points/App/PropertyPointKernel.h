/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef POINTS_PROPERTYPOINTKERNEL_H
#define POINTS_PROPERTYPOINTKERNEL_H

#include "Points.h"

namespace Points
{

/** The point kernel property
 */
class Standard_EXPORT PropertyPointKernel : public App::PropertyComplexGeoData
{
    TYPESYSTEM_HEADER();

public:
    PropertyPointKernel();
    ~PropertyPointKernel();

    /** @name Getter/setter */
    //@{
    /// Sets the points to the property
    void setValue( const PointKernel& m);
    /// get the points (only const possible!)
    const PointKernel &getValue(void) const;
    const Data::ComplexGeoData* getComplexData() const;
    //@}

    /** @name Getting basic geometric entities */
    //@{
    /** Returns the bounding box around the underlying mesh kernel */
    Base::BoundBox3d getBoundingBox() const;
    //@}

    /** @name Python interface */
    //@{
    PyObject* getPyObject(void);
    void setPyObject(PyObject *value);
    //@}

    /** @name Undo/Redo */
    //@{
    /// returns a new copy of the property (mainly for Undo/Redo and transactions)
    App::Property *Copy(void) const;
    /// paste the value from the property (mainly for Undo/Redo and transactions)
    void Paste(const App::Property &from);
    unsigned int getMemSize (void) const;
    //@}

    /** @name Save/restore */
    //@{
    void Save (Base::Writer &writer) const;
    void Restore(Base::XMLReader &reader);
    void SaveDocFile (Base::Writer &writer) const;
    void RestoreDocFile(Base::Reader &reader);
    //@}

    /** @name Modification */
    //@{
    PointKernel* startEditing();
    void finishEditing();
    /// Transform the real 3d point kernel
    void transformGeometry(const Base::Matrix4D &rclMat);
    void removeIndices( const std::vector<unsigned long>& );
    //@}

private:
    Base::Reference<PointKernel> _cPoints;
};

} // namespace Points


#endif // POINTS_PROPERTYPOINTKERNEL_H 
