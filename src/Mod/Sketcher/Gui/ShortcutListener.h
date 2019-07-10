/***************************************************************************
 *   Copyright (c) 2018 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com      *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef SKETCHERGUI_SHORTCUTLISTENER_H
#define SKETCHERGUI_SHORTCUTLISTENER_H

#include <QObject>


namespace SketcherGui {

class ViewProviderSketch;


class ShortcutListener: public QObject
{
    //Q_OBJECT

public:
    ShortcutListener(ViewProviderSketch * vp);
    ~ShortcutListener();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

    ViewProviderSketch * pViewProvider;
};

} // namespace SketcherGui


#endif // SKETCHERGUI_SHORTCUTLISTENER_H

