/***************************************************************************
 *   Copyright (c) 2015 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DOCUMENTRECOVERY_H
#define GUI_DIALOG_DOCUMENTRECOVERY_H

#include <QDialog>
#include <QScopedPointer>
#include <QList>
#include <QFileInfo>
#include <string>

namespace Gui { namespace Dialog {

class DocumentRecoveryPrivate;

/*!
 @author Werner Mayer
 */
class DocumentRecovery : public QDialog
{
    Q_OBJECT

public:
    DocumentRecovery(const QList<QFileInfo>&, QWidget* parent = 0);
    virtual ~DocumentRecovery();

    void accept();
    bool foundDocuments() const;

protected:
    void closeEvent(QCloseEvent*);
    void contextMenuEvent(QContextMenuEvent*);
    QString createProjectFile(const QString&);
    void clearDirectory(const QFileInfo&);

protected Q_SLOTS:
    void on_buttonCleanup_clicked();
    void onDeleteSection();

private:
    static std::string doctools;
    QScopedPointer<DocumentRecoveryPrivate> d_ptr;
    Q_DISABLE_COPY(DocumentRecovery)
    Q_DECLARE_PRIVATE(DocumentRecovery)
};

} //namespace Dialog

} //namespace Gui


#endif //GUI_DIALOG_DOCUMENTRECOVERY_H
