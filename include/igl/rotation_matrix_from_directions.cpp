// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2014 Daniele Panozzo <daniele.panozzo@gmail.com>, Olga Diamanti <olga.diam@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "rotation_matrix_from_directions.h"

template <typename Scalar>
IGL_INLINE Eigen::Matrix<Scalar, 3, 3> igl::rotation_matrix_from_directions(Eigen::Matrix<Scalar, 3, 1> v0,
                                                                        Eigen::Matrix<Scalar, 3, 1> v1,
                                                                        bool normalized)
{
  Eigen::Matrix<Scalar, 3, 3> rotM;
  const double epsilon=0.00001;
  if (!normalized)
  {
    v0.normalize();
    v1.normalize();
  }
  Scalar dot=v0.dot(v1);
  ///control if there is no rotation
  if (dot>((double)1-epsilon))
  {
    rotM = Eigen::Matrix<Scalar, 3, 3>::Identity();
    return rotM;
  }
  
  ///find the axis of rotation
  Eigen::Matrix<Scalar, 3, 1> axis;
  axis=v0.cross(v1);
  axis.normalize();
  
  ///construct rotation matrix
  Scalar u=axis(0);
  Scalar v=axis(1);
  Scalar w=axis(2);
  Scalar phi=acos(dot);
  Scalar rcos = cos(phi);
  Scalar rsin = sin(phi);
  
  rotM(0,0) =      rcos + u*u*(1-rcos);
  rotM(1,0) =  w * rsin + v*u*(1-rcos);
  rotM(2,0) = -v * rsin + w*u*(1-rcos);
  rotM(0,1) = -w * rsin + u*v*(1-rcos);
  rotM(1,1) =      rcos + v*v*(1-rcos);
  rotM(2,1) =  u * rsin + w*v*(1-rcos);
  rotM(0,2) =  v * rsin + u*w*(1-rcos);
  rotM(1,2) = -u * rsin + v*w*(1-rcos);
  rotM(2,2) =      rcos + w*w*(1-rcos);
  
  return rotM;
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template specialization
#endif

