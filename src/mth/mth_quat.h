#ifndef __mth_quat_h_
#define __mth_quat_h_

#include "mth_def.h"

/* Math namespace */
namespace mth {
/* Forward declaration */
template <typename Type> class vec3;
template <typename Type> class matr;
template <typename Type> class tensor;

/* Quaternion class */
template <typename Type> class quat {
  static_assert(std::is_arithmetic_v<Type>, "Number type is needed in quat");

public:
  union {
    struct { // Four numbers implementation
      Type W, X, Y, Z;
    };
    struct { // Number and vec3 implementation
      Type Im;
      vec3<Type> Vec;
    };
  }; /* End of 'quat' union */

  quat() noexcept {}                                               /* End of 'quat' function */
  explicit quat(const Type A) noexcept : X(A), Y(A), Z(A), W(A) {} /* End of 'quat' function */
  quat(const Type A, const Type B, const Type C, const Type D) noexcept : W(A), X(B), Y(C), Z(D) {}
  quat(const Type A, const vec3<Type> &V) noexcept : W(A), X(V.X), Y(V.Y), Z(V.Z) {} /* End of 'quat' function */
  auto operator+(const quat &Q) const noexcept -> quat { return quat(W + Q.W, X + Q.X, Y + Q.Y, Z + Q.Z); }
  auto operator+=(const quat &Q) noexcept -> quat & {
    W += Q.W;
    X += Q.X;
    Y += Q.Y;
    Z += Q.Z;
    return *this;
  }
  [[nodiscard]] auto operator-(const quat &Q) const noexcept -> quat { return {W - Q.W, X - Q.X, Y - Q.Y, Z - Q.Z}; }
  auto operator-=(const quat &Q) noexcept -> quat & {
    W -= Q.W;
    X -= Q.X;
    Y -= Q.Y;
    Z -= Q.Z;
    return *this;
  }

  auto operator-() const noexcept -> quat { return quat(-W, -X, -Y, -Z); } /* End of 'operator-' function */
  auto operator*(const quat &Q) const noexcept -> quat {
    return quat(W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z, W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,
                W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X, W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W);
  }
  auto operator*=(const quat &Q) noexcept -> quat & {
    const quat q = *this;

    W = q.W * Q.W - q.X * Q.X - q.Y * Q.Y - q.Z * Q.Z;
    X = q.W * Q.X + q.X * Q.W + q.Y * Q.Z - q.Z * Q.Y;
    Y = q.W * Q.Y - q.X * Q.Z + q.Y * Q.W + q.Z * Q.X;
    Z = q.W * Q.Z + q.X * Q.Y - q.Y * Q.X + q.Z * Q.W;
    return *this;
  }
  auto operator*(const Type Q) const noexcept -> quat { return quat(W * Q, X * Q, Y * Q, Z * Q); }
  auto operator*=(const Type Q) noexcept -> quat & {
    W *= Q;
    X *= Q;
    Y *= Q;
    Z *= Q;
    return *this;
  }
  auto operator/(const quat &Q) const noexcept -> quat { return (*this) * (quat(Q.W, -Q.Vec) / !Q); }
  auto operator/(const Type Q) const noexcept -> quat { return quat(W / Q, X / Q, Y / Q, Z / Q); }
  auto operator!() const noexcept -> Type { return W * W + X * X + Y * Y + Z * Z; } /* End of 'operator!' function */
  auto Normalized() const noexcept -> quat { return quat(W, X, Y, Z) / sqrt(!*this); }
  auto RotateQuat(const Type Angle) const noexcept -> quat { return {cos(Angle / 2.0F), Vec * sin(Angle / 2.0F)}; }
  auto RotateMatr() const noexcept -> matr<Type> {
    const Type X2 = 2 * X * X;
    const Type Y2 = 2 * Y * Y;
    const Type Z2 = 2 * Z * Z;
    const Type XZ = 2 * X * Z;
    const Type XY = 2 * X * Y;
    const Type YZ = 2 * Y * Z;
    const Type WX = 2 * W * X;
    const Type WY = 2 * W * Y;
    const Type WZ = 2 * W * Z;

    return matr<Type>(1 - Y2 - Z2, XY + WZ, XZ - WY, 0, // 1 string
                      XY - WZ, 1 - X2 - Z2, YZ + WX, 0, // 2 string
                      XZ + WY, YZ - WX, 1 - X2 - Y2, 0, // 3 string
                      0, 0, 0, 1);                      // 4 string
  }
  auto RotateTensor() const noexcept -> tensor<Type> {
    const Type X2 = 2 * X * X;
    const Type Y2 = 2 * Y * Y;
    const Type Z2 = 2 * Z * Z;
    const Type XY = 2 * X * Y;
    const Type WZ = 2 * W * Z;
    const Type WY = 2 * W * Y;
    const Type XZ = 2 * X * Z;
    const Type YZ = 2 * Y * Z;
    const Type WX = 2 * W * X;

    return tensor<Type>(1 - Y2 - Z2, XY + WZ, XZ - WY,  // 1 string
                        XY - WZ, 1 - X2 - Z2, YZ + WX,  // 2 string
                        XZ + WY, YZ - WX, 1 - X2 - Y2); // 3 string
  }

  static auto SLerp(const Type T, const quat &Q1, const quat &Q2) noexcept -> quat {
    Type cos_a = Q1.W * Q2.W + Q1.X * Q2.X + Q1.Y * Q2.Y + Q1.Z * Q2.Z;
    quat a = Q1;
    quat b = Q2;
    if (cos_a < 0) {
      cos_a = -cos_a, b = -b;
    }

    const Type alpha = acos(cos_a);
    const Type sin_a_rev = 1 / sin(alpha);
    const Type sin_ta = sin(T * alpha);
    const Type sin_1_ta = sin((1 - T) * alpha);

    return quat((a.W * sin_1_ta + b.W * sin_ta) * sin_a_rev, (a.X * sin_1_ta + b.X * sin_ta) * sin_a_rev,
                (a.Y * sin_1_ta + b.Y * sin_ta) * sin_a_rev, (a.Z * sin_1_ta + b.Z * sin_ta) * sin_a_rev);
  }

}; /* End of 'quat' class */
} // namespace mth

#endif /* __mth_quat_h_ */
