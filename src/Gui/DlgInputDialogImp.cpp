/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <QPushButton>

#include "DlgInputDialogImp.h"
#include "SpinBox.h"


using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgInputDialogImp */

/**
 *  Constructs a Gui::Dialog::DlgInputDialogImp as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgInputDialogImp::DlgInputDialogImp( const QString& labelTxt, QWidget* parent, bool modal, Type type )
  : QDialog( parent )
{
    this->setModal(modal);
    this->setupUi(this);
    label->setText(labelTxt);

    QSize sh = sizeHint();
    setType(type);
    resize(qMax(sh.width(), 400), 1);

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(tryAccept()));
    connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
}

/**
 *  Destroys the object and frees any allocated resources
 */
DlgInputDialogImp::~DlgInputDialogImp()
{
    // no need to delete child widgets, Qt does it all for us
}

void DlgInputDialogImp::textChanged( const QString &s )
{
    bool on = true;

    if (lineEdit->validator()) {
        QString str = lineEdit->text();
        int index = lineEdit->cursorPosition();
        on = ( lineEdit->validator()->validate(str, index) == QValidator::Acceptable );
    }
    else if ( type() != LineEdit ) {
        on = !s.isEmpty();
    }

    buttonBox->button(QDialogButtonBox::Ok)->setEnabled( on );
}

void DlgInputDialogImp::tryAccept()
{
    if (!lineEdit->text().isEmpty())
        accept();
}

void DlgInputDialogImp::setType( DlgInputDialogImp::Type t )
{
    inputtype = t;

    QWidget *input = 0;
    switch (inputtype)
    {
    case LineEdit:
        input = lineEdit;
        break;
    case SpinBox:
        input = spinBox;
        break;
    case UIntBox:
        input = uIntSpinBox;
        break;
    case FloatSpinBox:
        input = floatSpinBox;
        break;
    case ComboBox:
        input = comboBox;
        break;
    default:
        break;
    }

    if (input) {
        stack->setCurrentWidget(input->parentWidget());
        stack->setFixedHeight( input->sizeHint().height() );
        input->setFocus();
        label->setBuddy( input );
    }
}

DlgInputDialogImp::Type DlgInputDialogImp::type() const
{
    return inputtype;
}

QSpinBox *DlgInputDialogImp::getSpinBox() const
{
    return spinBox;
}

Gui::UIntSpinBox *DlgInputDialogImp::getUIntBox() const
{
    return uIntSpinBox;
}

QDoubleSpinBox *DlgInputDialogImp::getFloatSpinBox() const
{
    return floatSpinBox;
}

QLineEdit *DlgInputDialogImp::getLineEdit() const
{
    return lineEdit;
}

QComboBox *DlgInputDialogImp::getComboBox() const
{
    return comboBox;
}

#include "moc_DlgInputDialogImp.cpp"
