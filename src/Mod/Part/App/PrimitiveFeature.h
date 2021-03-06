/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_PRIMITIVEFEATURE_H
#define PART_PRIMITIVEFEATURE_H

#include "stdexport.h"
#include "App/PropertyUnits.h"
#include "PartFeature.h"
#include "AttachExtension.h"

namespace Part
{

class Standard_EXPORT Primitive : public Part::Feature, public Part::AttachExtension
{
    PROPERTY_HEADER_WITH_EXTENSIONS(Part::Primitive);

public:
    Primitive();
    virtual ~Primitive();

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    PyObject* getPyObject();
    //@}

protected:
    void Restore(Base::XMLReader &reader);
    void onChanged (const App::Property* prop);
};

class Standard_EXPORT Vertex : public Part::Primitive
{
    PROPERTY_HEADER(Part::Vertex);

public:
    Vertex();
    virtual ~Vertex();

    App::PropertyDistance X;
    App::PropertyDistance Y;
    App::PropertyDistance Z;

    /** @name methods override feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    void onChanged(const App::Property*);
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderPointParametric";
    }
    //@}
};

class Standard_EXPORT Line : public Part::Primitive
{
    PROPERTY_HEADER(Part::Line);

public:
    Line();
    virtual ~Line();

    App::PropertyDistance X1;
    App::PropertyDistance Y1;
    App::PropertyDistance Z1;
    App::PropertyDistance X2;
    App::PropertyDistance Y2;
    App::PropertyDistance Z2;

    /** @name methods override feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    void onChanged(const App::Property*);
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderLineParametric";
    }
    //@}
};

class Standard_EXPORT Plane : public Primitive
{
    PROPERTY_HEADER(Part::Plane);

public:
    Plane();

    App::PropertyLength Length;
    App::PropertyLength Width;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderPlaneParametric";
    }
    //@}
};

class Standard_EXPORT Sphere : public Primitive
{
    PROPERTY_HEADER(Part::Sphere);

public:
    Sphere();

    App::PropertyLength Radius;
    App::PropertyAngle Angle1;
    App::PropertyAngle Angle2;
    App::PropertyAngle Angle3;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderSphereParametric";
    }
    //@}
};

class Standard_EXPORT Ellipsoid : public Primitive
{
    PROPERTY_HEADER(Part::Ellipsoid);

public:
    Ellipsoid();

    App::PropertyLength Radius1;
    App::PropertyLength Radius2;
    App::PropertyLength Radius3;
    App::PropertyAngle Angle1;
    App::PropertyAngle Angle2;
    App::PropertyAngle Angle3;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    //@}
    virtual const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderEllipsoid";
    }
};

class Standard_EXPORT Cylinder : public Primitive
{
    PROPERTY_HEADER(Part::Cylinder);

public:
    Cylinder();

    App::PropertyLength Radius;
    App::PropertyLength Height;
    App::PropertyAngle Angle;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderCylinderParametric";
    }
    //@}
};

class Standard_EXPORT Prism : public Primitive
{
    PROPERTY_HEADER(Part::Prism);

public:
    Prism();

    App::PropertyIntegerConstraint Polygon;
    App::PropertyLength Circumradius;
    App::PropertyLength Height;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderPrism";
    }
    //@}
private:
    static App::PropertyIntegerConstraint::Constraints polygonRange;
};

class Standard_EXPORT RegularPolygon : public Primitive
{
    PROPERTY_HEADER(Part::RegularPolygon);

public:
    RegularPolygon();

    App::PropertyIntegerConstraint Polygon;
    App::PropertyLength Circumradius;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderRegularPolygon";
    }
    //@}
private:
    static App::PropertyIntegerConstraint::Constraints polygon;
};

class Standard_EXPORT Cone : public Primitive
{
    PROPERTY_HEADER(Part::Cone);

public:
    Cone();

    App::PropertyLength Radius1;
    App::PropertyLength Radius2;
    App::PropertyLength Height;
    App::PropertyAngle Angle;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderConeParametric";
    }
    //@}
};

class Standard_EXPORT Torus : public Primitive
{
    PROPERTY_HEADER(Part::Torus);

public:
    Torus();

    App::PropertyLength Radius1;
    App::PropertyLength Radius2;
    App::PropertyAngle Angle1;
    App::PropertyAngle Angle2;
    App::PropertyAngle Angle3;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderTorusParametric";
    }
    //@}
};

class Standard_EXPORT Helix : public Primitive
{
    PROPERTY_HEADER(Part::Helix);

public:
    Helix();

    App::PropertyLength Pitch;
    App::PropertyLength Height;
    App::PropertyLength Radius;
    App::PropertyAngle Angle;
    App::PropertyEnumeration     LocalCoord;
    App::PropertyEnumeration     Style;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderHelixParametric";
    }
    //@}

protected:
    void onChanged (const App::Property* prop);

private:
    static const char* LocalCSEnums[];
    static const char* StyleEnums[];
};

class Standard_EXPORT Spiral : public Primitive
{
    PROPERTY_HEADER(Part::Spiral);

public:
    Spiral();

    App::PropertyLength Growth;
    App::PropertyLength Rotations;
    App::PropertyLength Radius;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderSpiralParametric";
    }
    //@}

protected:
    void onChanged (const App::Property* prop);
};

class Standard_EXPORT Wedge : public Primitive
{
    PROPERTY_HEADER(Part::Wedge);

public:
    Wedge();

    App::PropertyDistance Xmin;
    App::PropertyDistance Ymin;
    App::PropertyDistance Zmin;
    App::PropertyDistance Z2min;
    App::PropertyDistance X2min;
    App::PropertyDistance Xmax;
    App::PropertyDistance Ymax;
    App::PropertyDistance Zmax;
    App::PropertyDistance Z2max;
    App::PropertyDistance X2max;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderWedge";
    }
    //@}

protected:
    void onChanged(const App::Property* prop);
};

class Ellipse : public Part::Primitive
{
    PROPERTY_HEADER(Part::Ellipse);

public:
    Ellipse();
    virtual ~Ellipse();

    App::PropertyLength MajorRadius;
    App::PropertyLength MinorRadius;
    App::PropertyAngle Angle0;
    App::PropertyAngle Angle1;

    /** @name methods override feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    void onChanged(const App::Property*);
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderEllipseParametric";
    }
    //@}

private:
    static App::PropertyQuantityConstraint::Constraints angleRange;
};

} //namespace Part


#endif // PART_PRIMITIVEFEATURE_H
