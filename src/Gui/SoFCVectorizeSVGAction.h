/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_SOFCVECTORIZESVGACTION_H
#define GUI_SOFCVECTORIZESVGACTION_H

#include "stdexport.h"
#ifndef __InventorAll__
# include "InventorAll.h"
#endif

#include <fstream>


namespace Gui {

class GuiExport SoSVGVectorOutput : public SoVectorOutput {
public:
    SoSVGVectorOutput();
    virtual ~SoSVGVectorOutput();

    virtual SbBool openFile (const char *filename);
    virtual void closeFile (void);
    std::fstream& getFileStream();

private:
    std::fstream file;
};

/**
 * @author Werner Mayer
 */
class SoFCVectorizeSVGActionP;
class GuiExport SoFCVectorizeSVGAction : public SoVectorizeAction {
    typedef SoReplacedElement inherited;

    SO_ACTION_HEADER(SoFCVectorizeSVGAction);

public:
    SoFCVectorizeSVGAction(void);
    virtual ~SoFCVectorizeSVGAction();

    static void initClass(void);
    SoSVGVectorOutput * getSVGOutput(void) const;

protected:
    virtual void printHeader(void) const;
    virtual void printFooter(void) const;
    virtual void printBackground(void) const;
    virtual void printItem(const SoVectorizeItem * item) const;
    virtual void printViewport(void) const;

private:
    SoFCVectorizeSVGActionP* p;
    friend class SoFCVectorizeSVGActionP;
};

} // namespace Gui

#endif // GUI_SOFCVECTORIZESVGACTION_H
