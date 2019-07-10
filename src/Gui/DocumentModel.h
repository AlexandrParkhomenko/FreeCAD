/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DOCUMENTMODEL_H
#define GUI_DOCUMENTMODEL_H

#include <QAbstractItemModel>
#include <vector>
#include <map>

namespace App {
class Property;
}
namespace Gui {
class Document;
class ViewProviderDocumentObject;

class DocumentModel : public QAbstractItemModel
{
public:
    DocumentModel(QObject* parent);
    virtual ~DocumentModel();

    int columnCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData (const QModelIndex & idx, const QVariant & value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index (int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent (const QModelIndex & index) const;
    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setHeaderData (int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole);

private:
    void slotNewDocument(const Gui::Document&);
    void slotDeleteDocument(const Gui::Document&);
    void slotRenameDocument(const Gui::Document&);
    void slotActiveDocument(const Gui::Document&);
    void slotRelabelDocument(const Gui::Document&);
    void slotInEdit(const Gui::ViewProviderDocumentObject& v);
    void slotResetEdit(const Gui::ViewProviderDocumentObject& v);
    void slotNewObject(const Gui::ViewProviderDocumentObject& obj);
    void slotDeleteObject(const Gui::ViewProviderDocumentObject& obj);
    void slotChangeObject(const Gui::ViewProviderDocumentObject& obj, const App::Property& Prop);
    void slotRenameObject(const Gui::ViewProviderDocumentObject& obj);
    void slotActiveObject(const Gui::ViewProviderDocumentObject& obj);

    const Document* getDocument(const QModelIndex&) const;
    bool isPropertyLink(const App::Property&) const;
    std::vector<ViewProviderDocumentObject*> claimChildren
        (const Document&, const ViewProviderDocumentObject&) const;

private:
    struct DocumentModelP *d;
};

} //namespace Gui


#endif //GUI_DOCUMENTMODEL_H
