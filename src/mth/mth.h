/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth.h
 * PURPOSE     : Animation project.
 *               Math support module.
 * PROGRAMMER  : CGSG'2024.
 * LAST UPDATE : 23.08.2024.
 * NOTE        : Namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_h_
#define __mth_h_

#include "mth_camera.h"
#include "mth_matr.h"
#include "mth_noise.h"
#include "mth_quat.h"
#include "mth_ray.h"
#include "mth_tensor.h"
#include "mth_vec2.h"
#include "mth_vec3.h"
#include "mth_vec4.h"

using vec2 = mth::vec2<FLT>;
using vec3 = mth::vec3<FLT>;
using vec4 = mth::vec4<FLT>;
using matr = mth::matr<FLT>;
using tensor = mth::tensor<FLT>;
using camera = mth::camera<FLT>;
using ray = mth::ray<FLT>;
using noise = mth::noise<FLT>;
using quat = mth::quat<FLT>;

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */
