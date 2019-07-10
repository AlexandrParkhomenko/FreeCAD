/***************************************************************************
 *   Copyright (c) Konstantinos Poulios      (logari81@gmail.com) 2011     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/
#include <Eigen/Dense>

int qp_eq(Eigen::MatrixXd &H, Eigen::VectorXd &g, Eigen::MatrixXd &A, Eigen::VectorXd &c,
          Eigen::VectorXd &x, Eigen::MatrixXd &Y, Eigen::MatrixXd &Z);
