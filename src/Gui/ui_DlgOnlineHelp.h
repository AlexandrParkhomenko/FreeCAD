/********************************************************************************
** Form generated from reading UI file 'DlgOnlineHelp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGONLINEHELP_H
#define UI_DLGONLINEHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgOnlineHelp
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *spacerItem;
    QGroupBox *GroupBoxOther;
    QGridLayout *gridLayout1;
    QLabel *TextLabelURL;
    Gui::PrefFileChooser *prefStartPage;

    void setupUi(QWidget *Gui__Dialog__DlgOnlineHelp)
    {
        if (Gui__Dialog__DlgOnlineHelp->objectName().isEmpty())
            Gui__Dialog__DlgOnlineHelp->setObjectName(QString("Gui__Dialog__DlgOnlineHelp"));
        Gui__Dialog__DlgOnlineHelp->resize(395, 440);
        gridLayout = new QGridLayout(Gui__Dialog__DlgOnlineHelp);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout->setObjectName(QString("gridLayout"));
        spacerItem = new QSpacerItem(373, 291, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 1, 0, 1, 1);

        GroupBoxOther = new QGroupBox(Gui__Dialog__DlgOnlineHelp);
        GroupBoxOther->setObjectName(QString("GroupBoxOther"));
        gridLayout1 = new QGridLayout(GroupBoxOther);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        gridLayout1->setObjectName(QString("gridLayout1"));
        TextLabelURL = new QLabel(GroupBoxOther);
        TextLabelURL->setObjectName(QString("TextLabelURL"));

        gridLayout1->addWidget(TextLabelURL, 0, 0, 1, 1);

        prefStartPage = new Gui::PrefFileChooser(GroupBoxOther);
        prefStartPage->setObjectName(QString("prefStartPage"));
        prefStartPage->setProperty("prefEntry", QVariant(QByteArray("Startpage")));
        prefStartPage->setProperty("prefPath", QVariant(QByteArray("OnlineHelp")));

        gridLayout1->addWidget(prefStartPage, 1, 0, 1, 1);


        gridLayout->addWidget(GroupBoxOther, 0, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgOnlineHelp);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgOnlineHelp);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgOnlineHelp)
    {
        Gui__Dialog__DlgOnlineHelp->setWindowTitle(QApplication::translate("Gui::Dialog::DlgOnlineHelp", "On-line help", nullptr));
        GroupBoxOther->setTitle(QApplication::translate("Gui::Dialog::DlgOnlineHelp", "Help viewer", nullptr));
        TextLabelURL->setText(QApplication::translate("Gui::Dialog::DlgOnlineHelp", "Location of start page", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgOnlineHelp: public Ui_DlgOnlineHelp {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGONLINEHELP_H
