/***************************************************************************
 *   Copyright (c) 2015 Thomas Anderson <blobfish[at]gmx.com>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef BOOST_BIND_BIND_HPP_INCLUDED
#include <boost/bind/bind.hpp>
#endif
#include <QAbstractEventDispatcher>
#include <QVBoxLayout>

#include <memory>

#include <sstream>

#include "Base/Console.h"

#include "App/Document.h"
#include "Gui/Document.h"
#include "Gui/Application.h"

#include "DAGModel.h"
#include "DAGView.h"

using namespace Gui;
using namespace DAG;
namespace bp = boost::placeholders;

DAG::DockWindow::DockWindow(Gui::Document* gDocumentIn, QWidget* parent): Gui::DockWindow(gDocumentIn, parent)
{
  dagView = new View(this);
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(dagView);
  this->setLayout(layout);
}

View::View(QWidget* parentIn): QGraphicsView(parentIn)
{
  this->setRenderHint(QPainter::Antialiasing, true);
  this->setRenderHint(QPainter::TextAntialiasing, true);
  Application::Instance->signalActiveDocument.connect(boost::bind(&View::slotActiveDocument, this, bp::_1));
  Application::Instance->signalDeleteDocument.connect(boost::bind(&View::slotDeleteDocument, this, bp::_1));
  
  //just update the dagview when the gui process is idle.
  connect(QAbstractEventDispatcher::instance(), SIGNAL(awake()), this, SLOT(awakeSlot()));
}

View::~View()
{
  // Application::Instance->signalActiveDocument.disconnect(boost::bind(&View::slotActiveDocument, this, bp::_1));
  // Application::Instance->signalDeleteDocument.disconnect(boost::bind(&View::slotDeleteDocument, this, bp::_1));
}

void View::slotActiveDocument(const Document &documentIn)
{
  if (Gui::Selection().hasSelection())
      return;
  ModelMap::const_iterator it = modelMap.find(&documentIn);
  if (it == modelMap.end())
  {
    ModelMap::value_type entry(std::make_pair(&documentIn, std::make_shared<Model>(this, documentIn)));
    modelMap.insert(entry);
    this->setScene(entry.second.get());
  }
  else
  {
    this->setScene(it->second.get());
  }
}

void View::slotDeleteDocument(const Document &documentIn)
{
  ModelMap::iterator it = modelMap.find(&documentIn);
  if (it != modelMap.end())
    modelMap.erase(it);
}

void View::awakeSlot()
{
  Model *model = dynamic_cast<Model *>(this->scene());
  if (model)
    model->awake();
}

void View::onSelectionChanged(const SelectionChanges& msg)
{
  switch(msg.Type) {
  case SelectionChanges::AddSelection:
  case SelectionChanges::RmvSelection:
  case SelectionChanges::SetSelection:
    if (!msg.pDocName || !msg.pDocName[0])
      return;
    break;
  case SelectionChanges::ClrSelection:
    if (!msg.pDocName || !msg.pDocName[0]) {
      for (auto &v : modelMap) {
        v.second->selectionChanged(msg);
      }
      return;
    }
    break;
  default:
    return;
  }
  auto doc = Gui::Application::Instance->getDocument(msg.pDocName);
  if (!doc) return;
  auto &model = modelMap[doc];
  if(!model)
    model = std::make_shared<Model>(this, *doc);
  this->setScene(model.get());
  model->selectionChanged(msg);
}



#include "moc_DAGView.cpp"
