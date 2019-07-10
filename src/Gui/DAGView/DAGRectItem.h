/***************************************************************************
 *   Copyright (c) 2015 Thomas Anderson <blobfish[at]gmx.com>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef DAGRECTITEM_H
#define DAGRECTITEM_H

#include <QGraphicsRectItem>
#include <QBrush>

namespace Gui
{
  namespace DAG
  {
    /*all right I give up! the parenting combined with the zvalues is fubar!
     * you can't control any kind of layering between children of separate parents
     */
    class RectItem : public QGraphicsRectItem
    {
    public:
      RectItem(QGraphicsItem* parent = 0);
      void setBackgroundBrush(const QBrush &brushIn){backgroundBrush = brushIn;}
      void setEditingBrush(const QBrush &brushIn){editBrush = brushIn;}
      void preHighlightOn(){preSelected = true;}
      void preHighlightOff(){preSelected = false;}
      void selectionOn(){selected = true;}
      void selectionOff(){selected = false;}
      bool isSelected(){return selected;}
      bool isPreSelected(){return preSelected;}
      void editingStart(){editing = true;}
      void editingFinished(){editing = false;}
      bool isEditing(){return editing;}
    protected:
      virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    private:
      QBrush backgroundBrush; //!< brush used for background. not used yet.
      QBrush editBrush; //!< brush used when object is in edit mode.
      //start with booleans, may expand to state.
      bool selected;
      bool preSelected;
      bool editing;
    };
  }
}

#endif // DAGRECTITEM_H
