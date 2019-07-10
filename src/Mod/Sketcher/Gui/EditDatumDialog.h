/***************************************************************************
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef SKETCHERGUI_EditDatumDialog_H
#define SKETCHERGUI_EditDatumDialog_H

#include <QObject>

namespace Sketcher {
class Constraint;
class SketchObject;
}

namespace SketcherGui {
class ViewProviderSketch;

class EditDatumDialog : public QObject {
    Q_DECLARE_TR_FUNCTIONS(SketcherGui::EditDatumDialog)
public:
    EditDatumDialog(ViewProviderSketch* vp, int ConstrNbr);
    EditDatumDialog(Sketcher::SketchObject* pcSketch, int ConstrNbr);
    ~EditDatumDialog();

    void exec(bool atCursor=true);
    void customEvent(QEvent*);

private:
    Sketcher::SketchObject* sketch;
    Sketcher::Constraint* Constr;
    int ConstrNbr;
};

}
#endif // SKETCHERGUI_DrawSketchHandler_H
