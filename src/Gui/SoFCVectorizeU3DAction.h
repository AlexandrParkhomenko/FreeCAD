/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_SOFCVECTORIZEU3DACTION_H
#define GUI_SOFCVECTORIZEU3DACTION_H

#include "stdexport.h"
#ifndef __InventorAll__
# include "InventorAll.h"
#endif

#include <fstream>


namespace Gui {

class GuiExport SoU3DVectorOutput : public SoVectorOutput {
public:
    SoU3DVectorOutput();
    virtual ~SoU3DVectorOutput();

    virtual SbBool openFile (const char *filename);
    virtual void closeFile (void);
    std::fstream& getFileStream();

private:
    std::fstream file;
};

/**
 * @author Werner Mayer
 */
class SoFCVectorizeU3DActionP;
class GuiExport SoFCVectorizeU3DAction : public SoVectorizeAction {
    typedef SoVectorizeAction inherited;

    SO_ACTION_HEADER(SoFCVectorizeU3DAction);

public:
    SoFCVectorizeU3DAction(void);
    virtual ~SoFCVectorizeU3DAction();

    static void initClass(void);
    SoU3DVectorOutput * getU3DOutput(void) const;

protected:
    virtual void beginTraversal(SoNode * node);
    virtual void endTraversal(SoNode *node);
    virtual void printHeader(void) const;
    virtual void printFooter(void) const;
    virtual void printBackground(void) const;
    virtual void printItem(const SoVectorizeItem * item) const;
    virtual void printViewport(void) const;

private:
    static void actionMethod(SoAction *, SoNode *);

private:
    SoFCVectorizeU3DActionP* p;
    friend class SoFCVectorizeU3DActionP;
};

} // namespace Gui

#endif // GUI_SOFCVECTORIZEU3DACTION_H
