/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer@users.sourceforge.net>        *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_PROGRESSDIALOG_H
#define GUI_PROGRESSDIALOG_H

#include <QWidget>
#include <QProgressDialog>
#include "Base/Sequencer.h"

namespace Gui {

struct SequencerDialogPrivate;

class ProgressDialog;
class SequencerDialog : public Base::SequencerBase
{
public:
    static SequencerDialog* instance();
    void pause();
    void resume();
    bool isBlocking() const;

protected:
    /** Construction */
    SequencerDialog ();
    /** Destruction */
    ~SequencerDialog ();

    /** Puts text to the progress dialog */
    void setText (const char* pszTxt);
    /** Starts the progress dialog */
    void startStep();
    /** Increase the step indicator of the progress dialog. */
    void nextStep(bool canAbort);
    /** Resets the sequencer */
    void resetData();
    void showRemainingTime();

private:
    /** @name for internal use only */
    //@{
    void setProgress(int step);
    /** Throws an exception to stop the pending operation. */
    void abort();
    //@}

    SequencerDialogPrivate* d;
    static SequencerDialog* _pclSingleton;

    friend class ProgressDialog;
};

class ProgressDialog : public QProgressDialog
{
    Q_OBJECT

public:
    /** Construction */
    ProgressDialog (SequencerDialog* s, QWidget * parent=0);
    /** Destruction */
    ~ProgressDialog ();

    /** Handles all incoming events while the progress bar is running. All key
     * and mouse events are ignored to block user input.
     */
    bool eventFilter(QObject* o, QEvent* e);

protected Q_SLOTS:
    void onCancel();

protected:
    bool canAbort() const;
    /** Gets the events under control */
    void enterControlEvents();
    /** Loses the control over incoming events*/
    void leaveControlEvents();

private:
    SequencerDialog* sequencer;

    friend class SequencerDialog;
};

} // namespace Gui

#endif // GUI_PROGRESSDIALOG_H
