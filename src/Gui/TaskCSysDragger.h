/***************************************************************************
 *   Copyright (c) 2015 Thomas Anderson         <blobfish[at]gmx.com>      *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef TASKCSYSDRAGGER_H
#define TASKCSYSDRAGGER_H

#include "Gui/TaskView/TaskDialog.h"
#include "App/DocumentObserver.h"

class QuantitySpinBox;

namespace Gui
{
  class SoFCCSysDragger;
  class ViewProviderDragger;
  
  class TaskCSysDragger : public Gui::TaskView::TaskDialog
  {
      Q_OBJECT
    public:
      TaskCSysDragger(ViewProviderDragger *vpObjectIn, SoFCCSysDragger *draggerIn);
      virtual ~TaskCSysDragger() override;
      virtual QDialogButtonBox::StandardButtons getStandardButtons() const override
        { return QDialogButtonBox::Ok;}
      virtual void open() override;
      virtual bool accept() override;
    private Q_SLOTS:
      void onTIncrementSlot(double freshValue);
      void onRIncrementSlot(double freshValue);
    private:
      void setupGui();
      App::DocumentObjectT vpObject;
      SoFCCSysDragger *dragger;
      QuantitySpinBox *tSpinBox;
      QuantitySpinBox *rSpinBox;
  };
}

#endif // TASKCSYSDRAGGER_H
