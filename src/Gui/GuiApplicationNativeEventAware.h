/***************************************************************************
 *   Copyright (c) 2010 Thomas Anderson <ta@nextgenengineering>            *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/



#ifndef GUIAPPLICATIONNATIVEEVENTAWARE_H
#define GUIAPPLICATIONNATIVEEVENTAWARE_H

#include <QApplication>
#if QT_VERSION >= 0x050000
#include <QAbstractNativeEventFilter>
#endif

class QMainWindow;

  #include <xcb/xcb.h> // For X11
  #include <xcb/xproto.h>

namespace Gui
{
#if QT_VERSION >= 0x050000
    class RawInputEventFilter : public QAbstractNativeEventFilter
    {
    public:
        typedef bool (*EventFilter)(void *message, long *result);
        RawInputEventFilter(EventFilter filter) : eventFilter(filter) {
        }
        virtual ~RawInputEventFilter() {
        }

        virtual bool nativeEventFilter(const QByteArray & /*eventType*/, void *message, long *result) {
            return eventFilter(message, result);
        }

    private:
        EventFilter eventFilter;
    };
#endif // if QT_VERSION >= 0x050000

    class GUIApplicationNativeEventAware : public QApplication
    {
        Q_OBJECT
    public:
        GUIApplicationNativeEventAware(int &argc, char *argv[]);
        ~GUIApplicationNativeEventAware();
        void initSpaceball(QMainWindow *window);
        bool isSpaceballPresent() const {return spaceballPresent;}
        bool processSpaceballEvent(QObject *object, QEvent *event);
    private:
        bool spaceballPresent;
        QMainWindow *mainWindow;
        int  motionDataArray[6];
        bool setOSIndependentMotionData();
        void importSettings();
        float convertPrefToSensitivity(int value);

// For X11
    public:
        bool xcbEventFilter(const xcb_client_message_event_t *message);
    }; // end class GUIApplicationNativeEventAware
} // end namespace Gui

#endif // GUIAPPLICATIONNATIVEEVENTAWARE_H

