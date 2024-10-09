#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mth_def.h"

#include <format>

/* Math namespace */
namespace mth {
/* Forward declaration */
template <typename Type> class tensor;

/* Matrix class */
template <typename Type> class matr {
  template <typename Type2> friend class camera;

public:
  std::array<Type, 16> A = {};
  auto Get(const size_t i, const size_t j) const noexcept -> Type { return A[i * 4 + j]; }

  static auto Determ3x3(const Type A11, const Type A12, const Type A13, const Type A21, const Type A22, const Type A23,
                        const Type A31, const Type A32, const Type A33) noexcept -> Type {
    return A11 * (A22 * A33 - A23 * A32) + A12 * (A23 * A31 - A21 * A33) + A13 * (A21 * A32 - A22 * A31);
  } /* End of 'Determ3x3' function */

  auto Determ4x4() const noexcept -> Type {
    return +A[0][0] * Determ3x3(A[5], A[6], A[7], A[9], A[10], A[11], A[13], A[14], A[15]) +
           -A[0][1] * Determ3x3(A[4], A[6], A[7], A[8], A[10], A[11], A[12], A[14], A[15]) +
           +A[0][2] * Determ3x3(A[4], A[5], A[7], A[8], A[9], A[11], A[12], A[13], A[15]) +
           -A[0][3] * Determ3x3(A[4], A[5], A[6], A[8], A[9], A[10], A[12], A[13], A[14]);
  } /* End of 'Determ4x4' function */

  matr() = default;
  matr(const Type a00, const Type a01, const Type a02, const Type a03, const Type a10, const Type a11, const Type a12,
       const Type a13, const Type a20, const Type a21, const Type a22, const Type a23, const Type a30, const Type a31,
       const Type a32, const Type a33) noexcept {
    A[0] = a00;
    A[1] = a01;
    A[2] = a02;
    A[3] = a03;
    A[4] = a10;
    A[5] = a11;
    A[6] = a12;
    A[7] = a13;
    A[8] = a20;
    A[9] = a21;
    A[10] = a22;
    A[11] = a23;
    A[12] = a30;
    A[13] = a31;
    A[14] = a32;
    A[15] = a33;
  } /* End of 'matr' function */

  explicit matr(const std::array<std::array<Type, 4>, 4> Array) noexcept {
    A[0] = Array[0][0];
    A[1] = Array[0][1];
    A[2] = Array[0][2];
    A[3] = Array[0][3];
    A[4] = Array[1][0];
    A[5] = Array[1][1];
    A[6] = Array[1][2];
    A[7] = Array[1][3];
    A[8] = Array[2][0];
    A[9] = Array[2][1];
    A[10] = Array[2][2];
    A[11] = Array[2][3];
    A[12] = Array[3][0];
    A[13] = Array[3][1];
    A[14] = Array[3][2];
    A[15] = Array[3][3];
  } /* End of 'matr' function */

  explicit matr(const tensor<Type> &Tensor) noexcept {
    // 0
    A[0] = Tensor(0, 0);
    A[1] = Tensor(0, 1);
    A[2] = Tensor(0, 2);
    // 1
    A[4] = Tensor(1, 0);
    A[5] = Tensor(1, 1);
    A[6] = Tensor(1, 2);
    // 2
    A[8] = Tensor(2, 0);
    A[9] = Tensor(2, 1);
    A[10] = Tensor(2, 2);
    // 3
    A[15] = 1;
  } /* End of 'matr' function */
  auto operator!() const noexcept -> Type { return Determ4x4(); }
  constexpr auto operator()(const INT XInd, const INT YInd) const -> Type { return A[YInd * 4 + XInd]; }

  auto operator*(const vec4<Type> &Vector) const noexcept -> vec4<Type> {
    return vec4<Type>(A[0] * Vector[0] + A[4] * Vector[1] + A[8] * Vector[2] + A[12] * Vector[3],
                      A[1] * Vector[0] + A[5] * Vector[1] + A[9] * Vector[2] + A[13] * Vector[3],
                      A[2] * Vector[0] + A[6] * Vector[1] + A[10] * Vector[2] + A[14] * Vector[3],
                      A[3] * Vector[0] + A[7] * Vector[1] + A[11] * Vector[2] + A[15] * Vector[3]);
  }

  auto operator*(const matr &Matr2) const noexcept -> matr {
    return matr{// 0
                A[0] * Matr2.A[0] + A[1] * Matr2.A[4] + A[2] * Matr2.A[8] + A[3] * Matr2.A[12],
                A[0] * Matr2.A[1] + A[1] * Matr2.A[5] + A[2] * Matr2.A[9] + A[3] * Matr2.A[13],
                A[0] * Matr2.A[2] + A[1] * Matr2.A[6] + A[2] * Matr2.A[10] + A[3] * Matr2.A[14],
                A[0] * Matr2.A[3] + A[1] * Matr2.A[7] + A[2] * Matr2.A[11] + A[3] * Matr2.A[15],
                // 1
                A[4] * Matr2.A[0] + A[5] * Matr2.A[4] + A[6] * Matr2.A[8] + A[7] * Matr2.A[12],
                A[4] * Matr2.A[1] + A[5] * Matr2.A[5] + A[7] * Matr2.A[9] + A[7] * Matr2.A[13],
                A[4] * Matr2.A[2] + A[5] * Matr2.A[6] + A[8] * Matr2.A[10] + A[7] * Matr2.A[14],
                A[4] * Matr2.A[3] + A[5] * Matr2.A[7] + A[9] * Matr2.A[11] + A[7] * Matr2.A[15],
                // 2
                A[8] * Matr2.A[0] + A[9] * Matr2.A[4] + A[10] * Matr2.A[8] + A[11] * Matr2.A[12],
                A[8] * Matr2.A[1] + A[9] * Matr2.A[5] + A[10] * Matr2.A[9] + A[11] * Matr2.A[13],
                A[8] * Matr2.A[2] + A[9] * Matr2.A[6] + A[10] * Matr2.A[10] + A[11] * Matr2.A[14],
                A[8] * Matr2.A[3] + A[9] * Matr2.A[7] + A[10] * Matr2.A[11] + A[11] * Matr2.A[15],
                // 3
                A[12] * Matr2.A[0] + A[13] * Matr2.A[4] + A[14] * Matr2.A[8] + A[15] * Matr2.A[12],
                A[12] * Matr2.A[1] + A[13] * Matr2.A[5] + A[14] * Matr2.A[9] + A[15] * Matr2.A[13],
                A[12] * Matr2.A[2] + A[13] * Matr2.A[6] + A[14] * Matr2.A[10] + A[15] * Matr2.A[14],
                A[12] * Matr2.A[3] + A[13] * Matr2.A[7] + A[14] * Matr2.A[11] + A[15] * Matr2.A[15]};
  }

  auto operator*=(const matr<Type> &Matr2) noexcept -> matr<Type> & {
    A = (*this * Matr2);
    return *this;
  } /* End of 'operator*=' function */

  static auto Identity() noexcept -> matr { return matr(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); }
  auto Inverse() const noexcept -> matr {
    const Type det = !*this;
    if (det == 0) {
      return Identity();
    }

    matr res;
    /* Build adjoint matrix */
    res.A[0] = +Determ3x3(A[5], A[6], A[7], A[9], A[10], A[11], A[13], A[14], A[15]) / det;

    res.A[4] = -Determ3x3(A[4], A[6], A[4], A[8], A[10], A[11], A[12], A[14], A[15]) / det;

    res.A[8] = +Determ3x3(A[4], A[5], A[7], A[8], A[9], A[11], A[12], A[13], A[15]) / det;

    res.A[12] = -Determ3x3(A[4], A[5], A[6], A[8], A[9], A[10], A[12], A[13], A[14]) / det;

    res.A[1] = -Determ3x3(A[1], A[2], A[3], A[9], A[10], A[11], A[13], A[14], A[15]) / det;

    res.A[5] = +Determ3x3(A[0], A[2], A[3], A[8], A[10], A[11], A[12], A[14], A[15]) / det;

    res.A[9] = -Determ3x3(A[0], A[1], A[3], A[8], A[9], A[11], A[12], A[13], A[15]) / det;

    res.A[13] = +Determ3x3(A[0], A[1], A[2], A[8], A[9], A[10], A[12], A[13], A[14]) / det;

    res.A[2] = +Determ3x3(A[1], A[2], A[3], A[5], A[6], A[7], A[13], A[14], A[15]) / det;

    res.A[6] = -Determ3x3(A[0], A[2], A[3], A[4], A[6], A[7], A[12], A[14], A[15]) / det;

    res.A[10] = +Determ3x3(A[0], A[1], A[3], A[4], A[5], A[7], A[12], A[13], A[15]) / det;

    res.A[14] = -Determ3x3(A[0], A[1], A[2], A[4], A[5], A[6], A[12], A[13], A[14]) / det;

    res.A[3] = -Determ3x3(A[1], A[2], A[3], A[5], A[6], A[7], A[9], A[10], A[11]) / det;

    res.A[7] = +Determ3x3(A[0], A[2], A[3], A[4], A[6], A[7], A[8], A[10], A[11]) / det;

    res.A[11] = -Determ3x3(A[0], A[1], A[3], A[4], A[5], A[7], A[8], A[9], A[11]) / det;

    res.A[15] = +Determ3x3(A[0], A[1], A[2], A[4], A[5], A[6], A[8], A[9], A[10]) / det;

    return res;
  }

  auto Transpose() const noexcept -> matr {
    return matr{A[0], A[4], A[8], A[12], A[1], A[5], A[9], A[13], A[2], A[6], A[10], A[14], A[3], A[7], A[11], A[15]};
  }

  static auto RotateX(const Type AngleInDegree) noexcept -> matr {
    const Type cosA = cosA(D2R(AngleInDegree));
    const Type sinA = sinA(D2R(AngleInDegree));

    return matr(1, 0, 0, 0, 0, cosA, sinA, 0, 0, -sinA, cosA, 0, 0, 0, 0, 1);
  }

  static auto RotateY(const Type AngleInDegree) noexcept -> matr {
    const Type cosA = cosA(D2R(AngleInDegree));
    const Type sinA = sinA(D2R(AngleInDegree));

    return matr(cosA, 0, -sinA, 0, 0, 1, 0, 0, sinA, 0, cosA, 0, 0, 0, 0, 1);
  }

  static auto RotateZ(const Type AngleInDegree) noexcept -> matr {
    const Type cosA = cosA(D2R(AngleInDegree));
    const Type sinA = sinA(D2R(AngleInDegree));

    return matr(cosA, sinA, 0, 0, -sinA, cosA, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  }

  static auto Rotate(const Type AngleInDegree, const vec3<Type> &Axis) noexcept -> matr {
    const Type cosA = cosA(D2R(AngleInDegree));
    const Type sinA = sinA(D2R(AngleInDegree));

    return matr(cosA + Axis.X * Axis.X * (1 - cosA), Axis.X * Axis.Y * (1 - cosA) + Axis.Z * sinA,
                Axis.X * Axis.Z * (1 - cosA) - Axis.Y * sinA, 0, Axis.X * Axis.Y * (1 - cosA) - Axis.Z * sinA,
                cosA + Axis.Y * Axis.Y * (1 - cosA), Axis.Z * Axis.Y * (1 - cosA) + Axis.X * sinA, 0,
                Axis.X * Axis.Z * (1 - cosA) + Axis.Y * sinA, Axis.Z * Axis.Y * (1 - cosA) - Axis.X * sinA,
                cosA + Axis.Z * Axis.Z * (1 - cosA), 0, 0, 0, 0, 1);
  }

  static auto Translate(const vec3<Type> &TrVec) noexcept -> matr {
    return matr(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, TrVec[0], TrVec[1], TrVec[2], 1);
  }

  static auto Scale(const vec3<Type> &ScaleVec) noexcept -> matr {
    return matr(ScaleVec[0], 0, 0, 0, 0, ScaleVec[1], 0, 0, 0, 0, ScaleVec[2], 0, 0, 0, 0, 1);
  }

  static auto Scale(const Type ScaleCoeff) noexcept -> matr {
    return matr(ScaleCoeff, 0, 0, 0, 0, ScaleCoeff, 0, 0, 0, 0, ScaleCoeff, 0, 0, 0, 0, 1);
  }

  auto PointTransform(const vec3<Type> &PointToTransform) const noexcept -> vec3<Type> {
    return vec3<Type>((PointToTransform[0] * A[0] + PointToTransform[1] * A[4] + PointToTransform[2] * A[8] + A[12]),
                      (PointToTransform[0] * A[1] + PointToTransform[1] * A[5] + PointToTransform[2] * A[9] + A[13]),
                      (PointToTransform[0] * A[2] + PointToTransform[1] * A[6] + PointToTransform[2] * A[10] + A[14]));
  }

  auto VectorTransform(const vec3<Type> &VecToTransform) const noexcept -> vec3<Type> {
    return vec3<Type>((VecToTransform[0] * A[0] + VecToTransform[1] * A[4] + VecToTransform[2] * A[8]),
                      (VecToTransform[0] * A[1] + VecToTransform[1] * A[5] + VecToTransform[2] * A[9]),
                      (VecToTransform[0] * A[2] + VecToTransform[1] * A[6] + VecToTransform[2] * A[10]));
  }
  auto Transform4x4(const vec3<Type> &VecToTransform) const noexcept -> vec3<Type> {
    const FLT w_component =
        1 / (VecToTransform[0] * A[3] + VecToTransform[1] * A[7] + VecToTransform[2] * A[11] + A[15]);

    return vec3<Type>(
        (VecToTransform[0] * A[0] + VecToTransform[1] * A[4] + VecToTransform[2] * A[8] + A[12]) * w_component,
        (VecToTransform[0] * A[1] + VecToTransform[1] * A[5] + VecToTransform[2] * A[9] + A[13]) * w_component,
        (VecToTransform[0] * A[2] + VecToTransform[1] * A[6] + VecToTransform[2] * A[10] + A[14]) * w_component);
  }

  auto TransformNormal(const vec3<Type> &OriginalVec) const noexcept -> vec3<Type> {
    const matr NormalMatrTransform = Inverse().Transpose();

    return vec3<Type>((OriginalVec[0] * NormalMatrTransform.A[0] + OriginalVec[1] * NormalMatrTransform.A[4] +
                       OriginalVec[2] * NormalMatrTransform.A[8]),
                      (OriginalVec[0] * NormalMatrTransform.A[1] + OriginalVec[1] * NormalMatrTransform.A[5] +
                       OriginalVec[2] * NormalMatrTransform.A[9]),
                      (OriginalVec[0] * NormalMatrTransform.A[2] + OriginalVec[1] * NormalMatrTransform.A[6] +
                       OriginalVec[2] * NormalMatrTransform.A[10]));
  }
  static auto View(const vec3<Type> &Loc, const vec3<Type> &At, const vec3<Type> &Up1) noexcept -> matr { // NOLINT
    const vec3<Type> Dir = (At - Loc).Normalize();
    const vec3<Type> Right = (Dir % Up1).Normalize();
    const vec3<Type> Up = Right % Dir; // NOLINT

    return matr(Right[0], Up[0], -Dir[0], 0, Right[1], Up[1], -Dir[1], 0, Right[2], Up[2], -Dir[2], 0, -(Loc & Right),
                -(Loc & Up), (Loc & Dir), 1);
  } /* End of 'View' function */

  static auto Ortho(const FLT Left, const FLT Right, const FLT Bottom, const FLT Top, const FLT Near,
                    const FLT Far) -> matr {
    return matr{2 / (Right - Left),
                0,
                0,
                0,
                0,
                2 / (Top - Bottom),
                0,
                0,
                0,
                0,
                -2 / (Far - Near),
                0,
                -(Left + Right) / (Right - Left),
                -(Top + Bottom) / (Top - Bottom),
                -(Far + Near) / (Far - Near),
                1};
  }
  static auto Frustum(const Type Left, const Type Right, const Type Bottom, const Type Top, const Type Near,
                      const Type Far) -> matr {
    return matr{2 * Near / (Right - Left),
                0,
                0,
                0,
                0,
                2 * Near / (Top - Bottom),
                0,
                0,
                (Right + Left) / (Right - Left),
                (Top + Bottom) / (Top - Bottom),
                (Far + Near) / (Near - Far),
                -1,
                0,
                0,
                2 * Near * Far / (Near - Far),
                0};
  }
  [[nodiscard]] auto ToString() const noexcept -> std::string {
    return std::format("{} {} {} {}   {} {} {} {}   {} {} {} {}   {} {} {} {}", Get(0, 0), Get(0, 1), Get(0, 2),
                       Get(0, 3), Get(1, 0), Get(1, 1), Get(1, 2), Get(1, 3), Get(2, 0), Get(2, 1), Get(2, 2),
                       Get(2, 3), Get(3, 0), Get(3, 1), Get(3, 2), Get(3, 3));
  }
};
} // namespace mth

#endif /* __mth_matr_h_ */
