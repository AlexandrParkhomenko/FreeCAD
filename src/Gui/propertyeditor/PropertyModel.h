/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PROPERTYMODEL_H
#define PROPERTYMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include <vector>
#include <map>

namespace App {
class Property;
}
namespace Gui {
namespace PropertyEditor {

class PropertyItem;
class PropertyModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    typedef std::vector< std::pair< std::string, std::vector<App::Property*> > > PropertyList;

    PropertyModel(QObject* parent);
    virtual ~PropertyModel();

    QModelIndex buddy (const QModelIndex & index) const;
    int columnCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData (const QModelIndex & idx, const QVariant & value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index (int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent (const QModelIndex & index) const;
    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setHeaderData (int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole);
    void buildUp(const PropertyList& props);

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

    void updateProperty(const App::Property&);
    void appendProperty(const App::Property&);
    void removeProperty(const App::Property&);

    QStringList propertyPathFromIndex(const QModelIndex&) const;
    QModelIndex propertyIndexFromPath(const QStringList&) const;

private:
    void updateChildren(PropertyItem* item, int column, const QModelIndex& parent);

private:
    PropertyItem *rootItem;
};

} //namespace PropertyEditor
} //namespace Gui


#endif //PROPERTYMODEL_H
