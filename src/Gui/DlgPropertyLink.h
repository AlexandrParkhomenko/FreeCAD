/***************************************************************************
 *   Copyright (c) 2014 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGPROPERTYLINK_H
#define GUI_DIALOG_DLGPROPERTYLINK_H

#include <QDialog>
#include <QAbstractItemView>

namespace Gui { namespace Dialog {

class Ui_DlgPropertyLink;
class DlgPropertyLink : public QDialog
{
    Q_OBJECT

public:
    DlgPropertyLink(const QStringList& list, QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgPropertyLink();

    void setSelectionMode(QAbstractItemView::SelectionMode mode);
    void accept();
    QStringList propertyLink() const;
    QVariantList propertyLinkList() const;

private Q_SLOTS:
    void on_checkObjectType_toggled(bool);
    void on_searchBox_textChanged(const QString&);

private:
    void findObjects(bool on, const QString& searchText);

private:
    QStringList link;
    Ui_DlgPropertyLink* ui;
};

} // namespace Dialog
} // namespace Gui


#endif // GUI_DIALOG_DLGPROPERTYLINK_H

