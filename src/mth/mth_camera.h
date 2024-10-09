#ifndef __mth_camera_h_
#define __mth_camera_h_

#include "mth_def.h"

/* Math namespace */
namespace mth {
/* Forward declaration */
template <typename Type> class matr;
template <typename Type> class vec3;

/* 3D camera class */
template <class Type> class camera {
  static_assert(std::is_arithmetic_v<Type>, "Number type is needed in camera");

  template <typename Type2> friend class matr;

public:
  INT FrameW{}, FrameH{}; /* Frame width and height */
  vec3<Type> Loc,         /* Camera location */
      Dir,                /* Camera direction */
      Right,              /* Camera right vector */
      Up,                 /* Camera up vector */
      At;                 /* Camera privot point */

  /* Camera projection data */
  Type FarClip,        /* Distance to project far clip plane (far) */
      Wp, Hp,          /* Projection plane size */
      ProjDist,        /* Distance to projection plane */
      ProjSize;        /* Projection size */
  matr<Type> MatrView, /* View coordinate system matrix */
      MatrProj,        /* Projection coordinate system matrix */
      MatrVP;          /* View and projection matrix precalculate value */

  camera() : Loc(200), At(0), ProjDist(0.1), Up(0, 1, 0), Hp(0.1), Wp(0.1), FarClip(10000), ProjSize(0.1) {
    Dir = (At - Loc).Normalizing();
    Right = (Dir % Up).Normalizing();
  } /* End of 'camera' function */

  void ProjSet() {
    Wp = Hp = ProjSize;

    /* Correct aspect ratio */
    if (FrameW > FrameH) {
      Wp *= static_cast<DBL>(FrameW) / FrameH;
    } else {
      Hp *= static_cast<DBL>(FrameH) / FrameW;
    }

    MatrProj = matr<Type>::Frustum(-Wp / 2, Wp / 2, -Hp / 2, Hp / 2, ProjDist, FarClip);
    MatrProj.A[1][1] *= -1;
    MatrVP = MatrView * MatrProj;
  }

  auto Resize(const INT Width, const INT Height) -> camera & {
    FrameW = Width;
    FrameH = Height;
    ProjSet();
    return *this;
  }

  auto Set(const vec3<Type> &Loc1, const vec3<Type> &At1, const vec3<Type> &Up1) -> camera & {
    MatrView = mth::matr<Type>::View(Loc1, At1, Up1);

    Dir = mth::vec3<Type>(-MatrView.A[0][2], -MatrView.A[1][2], -MatrView.A[2][2]);
    Up = mth::vec3<Type>(MatrView.A[0][1], MatrView.A[1][1], MatrView.A[2][1]);
    Right = mth::vec3<Type>(MatrView.A[0][0], MatrView.A[1][0], MatrView.A[2][0]);

    Loc = Loc1;
    At = At1;
    MatrVP = MatrView * MatrProj;
    return *this;
  }
};
} // namespace mth

#endif /* __mth_camera_h_ */
