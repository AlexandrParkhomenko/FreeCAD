/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <algorithm>
# include <Inventor/SbMatrix.h>
# include <Inventor/SbTesselator.h>
# include <QAbstractItemModel>
# include <QAbstractItemView>
# include <QItemSelection>
# include <QItemSelectionModel>
#include "Utilities.h"
#include "App/DocumentObject.h"

using namespace Gui;


ViewVolumeProjection::ViewVolumeProjection (const SbViewVolume &vv)
  : viewVolume(vv)
  , hasTransform(false)
{
    matrix = viewVolume.getMatrix();
    invert = matrix.inverse();
}

Base::Vector3f ViewVolumeProjection::operator()(const Base::Vector3f &pt) const
{
    SbVec3f pt3d(pt.x,pt.y,pt.z);
    if (hasTransform) {
        Base::Vector3f ptt = transform * pt;
        pt3d.setValue(ptt.x, ptt.y, ptt.z);
    }

    // See SbViewVolume::projectToScreen
    matrix.multVecMatrix(pt3d, pt3d);

    return Base::Vector3f(0.5*pt3d[0]+0.5, 0.5*pt3d[1]+0.5, 0.5*pt3d[2]+0.5);
}

Base::Vector3d ViewVolumeProjection::operator()(const Base::Vector3d &pt) const
{
    Base::Vector3f ptf = Base::convertTo<Base::Vector3f>(pt);
    ptf = operator()(ptf);
    return Base::convertTo<Base::Vector3d>(ptf);
}

Base::Vector3f ViewVolumeProjection::inverse (const Base::Vector3f &pt) const
{
    SbVec3f pt3d(2.0f*pt.x-1.0f, 2.0f*pt.y-1.0f, 2.0f*pt.z-1.0f);
    invert.multVecMatrix(pt3d, pt3d);
    return Base::Vector3f(pt3d[0],pt3d[1],pt3d[2]);
}

Base::Vector3d ViewVolumeProjection::inverse (const Base::Vector3d &pt) const
{
    Base::Vector3f ptf = Base::convertTo<Base::Vector3f>(pt);
    ptf = inverse(ptf);
    return Base::convertTo<Base::Vector3d>(ptf);
}

/*!
 * \brief This method applies an additional transformation to the input points
 * passed with the () operator.
 * \param mat
 */
void ViewVolumeProjection::setTransform(const Base::Matrix4D& mat)
{
    transform = mat;
    hasTransform = (mat != Base::Matrix4D());
}

Base::Matrix4D ViewVolumeProjection::getProjectionMatrix () const
{
    // Inventor stores the transposed matrix
    Base::Matrix4D mat;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++)
            mat[i][j] = matrix[j][i];
    }

    // Compose the object transform, if defined
    if (hasTransform) {
        mat = mat * transform;
    }

    return mat;
}

// ----------------------------------------------------------------------------

void Tessellator::tessCB(void * v0, void * v1, void * v2, void * cbdata)
{
    int * vtx0 = (int *)v0; 
    int * vtx1 = (int *)v1; 
    int * vtx2 = (int *)v2;

    std::vector<int>* array = (std::vector<int> *)cbdata;
    array->push_back(*vtx0);
    array->push_back(*vtx1);
    array->push_back(*vtx2);
    array->push_back(-1);
}

Tessellator::Tessellator(const std::vector<SbVec2f>& poly) : polygon(poly)
{
}

std::vector<int> Tessellator::tessellate() const
{
    std::vector<int> indices(polygon.size());
    std::vector<int> face_indices;

    SbTesselator tessellator(tessCB, &face_indices);
    tessellator.beginPolygon();

    int index = 0;
    for (std::vector<SbVec2f>::const_iterator it = polygon.begin(); it != polygon.end(); ++it, index++) {
        indices[index] = index;
        tessellator.addVertex(SbVec3f((*it)[0], (*it)[1], 0.0f), &(indices[index]));
    }

    // run the triangulation now
    tessellator.endPolygon();
    return face_indices;
}

// ----------------------------------------------------------------------------

class ItemViewSelection::MatchName {
public:
    MatchName(const QString& n) : name(n)
    {}
    bool operator() (const App::DocumentObject* obj) {
        return name == QLatin1String(obj->getNameInDocument());
    }
private:
    QString name;
};

ItemViewSelection::ItemViewSelection(QAbstractItemView* view)
  : view(view)
{
}

void ItemViewSelection::applyFrom(const std::vector<App::DocumentObject*> objs)
{
    QAbstractItemModel* model = view->model();
    QItemSelection range;
    for (int i=0; i<model->rowCount(); i++) {
        QModelIndex item = model->index(i,0);
        if (item.isValid()) {
            QVariant name = model->data(item, Qt::UserRole);
            std::vector<App::DocumentObject*>::const_iterator it;
            it = std::find_if(objs.begin(), objs.end(), MatchName(name.toString()));
            if (it != objs.end())
                range.select(item, item);
        }
    }

    view->selectionModel()->select(range, QItemSelectionModel::Select);
}
