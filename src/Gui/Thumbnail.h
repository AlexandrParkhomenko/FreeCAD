/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_THUMBNAIL_H
#define GUI_THUMBNAIL_H

#include "Base/Persistence.h"
#include <QUrl>

class QImage;

namespace Gui {
class View3DInventorViewer;

class Thumbnail : public Base::Persistence
{
public:
    Thumbnail(int s = 128);
    ~Thumbnail();

    void setViewer(View3DInventorViewer*);
    void setSize(int);
    void setFileName(const char*);

    /** @name I/O of the document */
    //@{
    unsigned int getMemSize (void) const;
    /// This method is used to save properties or very small amounts of data to an XML document.
    void Save (Base::Writer &writer) const;
    /// This method is used to restore properties from an XML document.
    void Restore(Base::XMLReader &reader);
    /// This method is used to save large amounts of data to a binary file.
    void SaveDocFile (Base::Writer &writer) const;
    /// This method is used to restore large amounts of data from a binary file.
    void RestoreDocFile(Base::Reader &reader);
    //@}

private:
    QUrl uri;
    View3DInventorViewer* viewer;
    int size;
};

}

#endif // GUI_THUMBNAIL_H
