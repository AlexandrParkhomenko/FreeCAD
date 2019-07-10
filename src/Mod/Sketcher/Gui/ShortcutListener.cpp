/***************************************************************************
 *   Copyright (c) 2018 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com      *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <QKeyEvent>

#include "ShortcutListener.h"
#include "ViewProviderSketch.h"

using namespace SketcherGui;

ShortcutListener::ShortcutListener(ViewProviderSketch * vp)
{
    pViewProvider = vp;
}

ShortcutListener::~ShortcutListener()
{
}

bool ShortcutListener::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::ShortcutOverride) {
        QKeyEvent * kevent = static_cast<QKeyEvent*>(event);
        if (kevent->modifiers() == Qt::NoModifier ||
            kevent->modifiers() == Qt::ShiftModifier ||
            kevent->modifiers() == Qt::KeypadModifier) {
            switch (kevent->key()) {
                case Qt::Key_Delete:
                    kevent->accept();
                    pViewProvider->deleteSelected(); // this takes a list of objects
                    return true;
                default:
                    break;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
