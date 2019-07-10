/***************************************************************************
 *   Copyright (c) 2017 Peter Lama (peterldev94@gmail.com)                 *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "Gui/Application.h"
#include "Gui/Control.h"
#include "Gui/ViewProviderDocumentObject.h"

#include "PropertyEnumAttacherItem.h"

using namespace PartGui;

PROPERTYITEM_SOURCE(PartGui::PropertyEnumAttacherItem)

PropertyEnumAttacherItem::PropertyEnumAttacherItem()
{
}

QWidget* PropertyEnumAttacherItem::createEditor(QWidget* parent, const QObject* receiver, const char* method) const
{
    Gui::LabelButton* modeEditor = new Gui::LabelButton(parent);
    QObject::connect(modeEditor, SIGNAL(valueChanged(const QVariant &)), receiver, method);
    QObject::connect(modeEditor, SIGNAL(buttonClicked()), this, SLOT(openTask()));
    modeEditor->setDisabled(isReadOnly());
    return modeEditor;
}

void PropertyEnumAttacherItem::setEditorData(QWidget *editor, const QVariant& data) const
{
    Gui::LabelButton* modeEditor = qobject_cast<Gui::LabelButton*>(editor);
    modeEditor->setValue(data);
}

QVariant PropertyEnumAttacherItem::editorData(QWidget *editor) const
{
    Gui::LabelButton* modeEditor = qobject_cast<Gui::LabelButton*>(editor);
    return modeEditor->value();
}

void PropertyEnumAttacherItem::openTask()
{
    Gui::TaskView::TaskDialog* dlg = Gui::Control().activeDialog();
    TaskDlgAttacher* task;
    task = qobject_cast<TaskDlgAttacher*>(dlg);

    if (dlg && !task) {
        // there is already another task dialog which must be closed first
        Gui::Control().showDialog(dlg);
        return;
    }
    if (!task) {
        const App::Property* prop = getFirstProperty();
        if (prop) {
            App::PropertyContainer* parent = prop->getContainer();

            if (parent->getTypeId().isDerivedFrom(App::DocumentObject::getClassTypeId())) {
                App::DocumentObject* obj = static_cast<App::DocumentObject*>(parent);
                Gui::ViewProvider* view = Gui::Application::Instance->getViewProvider(obj);

                if (view->getTypeId().isDerivedFrom(Gui::ViewProviderDocumentObject::getClassTypeId())) {
                    task = new TaskDlgAttacher(static_cast<Gui::ViewProviderDocumentObject*>(view));
                }
            }
        }
        if (!task) {
            return;
        }
    }
    
    Gui::Control().showDialog(task);
}

#include "moc_PropertyEnumAttacherItem.cpp"
