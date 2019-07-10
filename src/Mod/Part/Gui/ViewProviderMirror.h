/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERMIRROR_H
#define PARTGUI_VIEWPROVIDERMIRROR_H

#include "stdexport.h"
#include "Mod/Part/Gui/ViewProvider.h"

namespace PartGui {


class PartGuiExport ViewProviderMirror : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderMirror);

public:
    ViewProviderMirror();
    virtual ~ViewProviderMirror();
    /** @name Edit methods */
    //@{
    void setupContextMenu(QMenu*, QObject*, const char*);
    std::vector<App::DocumentObject*> claimChildren() const;
    bool onDelete(const std::vector<std::string> &);
    
protected:
    bool setEdit(int ModNum);
    void unsetEdit(int ModNum);
    //@}

private:
    static void dragStartCallback(void * data, SoDragger * d);
    static void dragFinishCallback(void * data, SoDragger * d);
    static void dragMotionCallback(void * data, SoDragger * d);

private:
    SoSeparator* pcEditNode;
};

class PartGuiExport ViewProviderFillet : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderFillet);

public:
    ViewProviderFillet();
    virtual ~ViewProviderFillet();
    /** @name Edit methods */
    //@{
    void setupContextMenu(QMenu*, QObject*, const char*);
    std::vector<App::DocumentObject*> claimChildren() const;
    bool onDelete(const std::vector<std::string> &);

protected:
    void updateData(const App::Property*);
    bool setEdit(int ModNum);
    void unsetEdit(int ModNum);
    //@}
};

class ViewProviderChamfer : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderChamfer);

public:
    /// constructor
    ViewProviderChamfer();
    /// destructor
    virtual ~ViewProviderChamfer();
    /** @name Edit methods */
    //@{
    void setupContextMenu(QMenu*, QObject*, const char*);
    std::vector<App::DocumentObject*> claimChildren() const;
    bool onDelete(const std::vector<std::string> &);

protected:
    void updateData(const App::Property*);
    bool setEdit(int ModNum);
    void unsetEdit(int ModNum);
    //@}
};

class ViewProviderRevolution : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderRevolution);

public:
    /// constructor
    ViewProviderRevolution();
    /// destructor
    virtual ~ViewProviderRevolution();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
    bool onDelete(const std::vector<std::string> &);
};

class ViewProviderLoft : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderLoft);

public:
    /// constructor
    ViewProviderLoft();
    /// destructor
    virtual ~ViewProviderLoft();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
    bool onDelete(const std::vector<std::string> &);
};

class ViewProviderSweep : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderSweep);

public:
    /// constructor
    ViewProviderSweep();
    /// destructor
    virtual ~ViewProviderSweep();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
    bool onDelete(const std::vector<std::string> &);
};

class ViewProviderOffset : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderOffset);

public:
    /// constructor
    ViewProviderOffset();
    /// destructor
    virtual ~ViewProviderOffset();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
    void setupContextMenu(QMenu*, QObject*, const char*);
    bool onDelete(const std::vector<std::string> &);

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);
};

class ViewProviderOffset2D : public ViewProviderOffset
{
    PROPERTY_HEADER(PartGui::ViewProviderOffset2D);

public:
    ViewProviderOffset2D(){
        sPixmap = "Part_Offset2D";
    }
};

class ViewProviderThickness : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderThickness);

public:
    /// constructor
    ViewProviderThickness();
    /// destructor
    virtual ~ViewProviderThickness();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
    void setupContextMenu(QMenu*, QObject*, const char*);
    bool onDelete(const std::vector<std::string> &);

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);
};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERMIRROR_H
