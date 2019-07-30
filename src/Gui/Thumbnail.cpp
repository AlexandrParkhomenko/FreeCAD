/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <QApplication>
# include <QBuffer>
# include <QByteArray>
# include <QDateTime>
# include <QImage>

#include <QtOpenGL.h>
#include "Thumbnail.h"
#include "BitmapFactory.h"
#include "View3DInventorViewer.h"
#include "Base/Writer.h"
#include "Base/Reader.h"
#include "App/Application.h"

using namespace Gui;

Thumbnail::Thumbnail(int s) : viewer(0), size(s)
{
}

Thumbnail::~Thumbnail()
{
}

void Thumbnail::setViewer(View3DInventorViewer* v)
{
    this->viewer = v;
}

void Thumbnail::setSize(int s)
{
    this->size = s;
}

void Thumbnail::setFileName(const char* fn)
{
    this->uri = QUrl::fromLocalFile(QString(fn));
}

unsigned int Thumbnail::getMemSize (void) const
{
    return 0;
}

void Thumbnail::Save (Base::Writer &writer) const
{
    // It's only possible to add extra information if force of XML is disabled
    if (writer.isForceXML() == false)
        writer.addFile("thumbnails/Thumbnail.png", this);
}

void Thumbnail::Restore(Base::XMLReader &reader)
{
    Q_UNUSED(reader); 
    //reader.addFile("Thumbnail.png",this);
}

void Thumbnail::SaveDocFile (Base::Writer &writer) const
{
    if (!this->viewer)
        return;
    QImage img;
    if (this->viewer->isActiveWindow()) {
        QColor invalid;
        this->viewer->imageFromFramebuffer(this->size, this->size, 0, invalid, img);
    }

    QPixmap px = Gui::BitmapFactory().pixmap(App::Application::Config()["AppIcon"].c_str());
    if (!img.isNull()) {
        if (App::GetApplication().GetParameterGroupByPath
            ("User parameter:BaseApp/Preferences/Document")->GetBool("AddThumbnailLogo",true))
            px = BitmapFactory().merge(QPixmap::fromImage(img),px,BitmapFactoryInst::BottomRight);
        else
            px = QPixmap::fromImage(img);
    }

    if (!px.isNull()) {
        // according to specification add some meta-information to the image
        uint mt = QDateTime::currentDateTime().toTime_t();
        QString mtime = QString("%1").arg(mt);
        img.setText(QString("Software"), qApp->applicationName());
        img.setText(QString("Thumb::Mimetype"), QString("application/x-extension-freecad"));
        img.setText(QString("Thumb::MTime"), mtime);
        img.setText(QString("Thumb::URI"), this->uri.toString());

        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        px.save(&buffer, "PNG");
        writer.Stream().write(ba.constData(), ba.length());
    }
}

void Thumbnail::RestoreDocFile(Base::Reader &reader)
{
    Q_UNUSED(reader); 
}
