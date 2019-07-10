/***************************************************************************
 *   Copyright (c) 2018 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESH_FUNCTIONAL_H
#define MESH_FUNCTIONAL_H

#include <algorithm>
#include <QtConcurrentRun>
#include <QFuture>
#include <QThread>

namespace MeshCore
{
    template <class Iter, class Pred>
    static void parallel_sort(Iter begin, Iter end, Pred comp, int threads)
    {
        if (threads < 2 || end - begin < 2)
        {
            std::sort(begin, end, comp);
        }
        else
        {
            Iter mid = begin + (end - begin) / 2;
            if (threads == 2)
            {
                QFuture<void> future = QtConcurrent::run(parallel_sort<Iter, Pred>, begin, mid, comp, threads / 2);
                std::sort(mid, end, comp);
                future.waitForFinished();
            }
            else
            {
                QFuture<void> a = QtConcurrent::run(parallel_sort<Iter, Pred>, begin, mid, comp, threads / 2);
                QFuture<void> b = QtConcurrent::run(parallel_sort<Iter, Pred>, mid, end, comp, threads / 2);
                a.waitForFinished();
                b.waitForFinished();
            }
            std::inplace_merge(begin, mid, end, comp);
        }
    }

} // namespace MeshCore


#endif  // MESH_FUNCTIONAL_H 
