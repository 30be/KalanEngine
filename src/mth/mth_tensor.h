#ifndef __mth_tensor_h_
#define __mth_tensor_h_

#include "mth_def.h"
#include <array>

/* Math namespace */
namespace mth {
/* Matrix 3x3 representation type */
template <typename Type> class tensor {
  static_assert(std::is_arithmetic_v<Type>, "Number type is needed in tensor");

  template <typename Type2> friend class matr;

private:
  std::array<Type, 9> A{};

public:
  tensor() = default;
  tensor(const Type A00, const Type A01, const Type A02, const Type A10, const Type A11, const Type A12, const Type A20,
         const Type A21, const Type A22) noexcept {
    A[0] = A00;
    A[1] = A01;
    A[2] = A02;
    A[3] = A10;
    A[4] = A11;
    A[5] = A12;
    A[6] = A20;
    A[7] = A21;
    A[8] = A22;
  }
  explicit tensor(const std::array<std::array<Type, 3>, 3> a) noexcept {
    A[0] = a[0][0];
    A[1] = a[0][1];
    A[2] = a[0][2];
    A[3] = a[1][0];
    A[4] = a[1][1];
    A[5] = a[1][2];
    A[6] = a[2][0];
    A[7] = a[2][1];
    A[8] = a[2][2];
  }
  auto operator()(const INT N1, const INT N2) const -> Type { return A[N1 * 3 + N2]; }
  auto operator()(const INT N1, const INT N2) -> Type & { return A[N1 * 3 + N2]; } /* End of 'operator()' function */
  auto operator+(const tensor &T) const noexcept -> tensor {
    return tensor(A[0][0] + T.A[0][0], A[0][1] + T.A[0][1], A[0][2] + T.A[0][2], A[1][0] + T.A[1][0],
                  A[1][1] + T.A[1][1], A[1][2] + T.A[1][2], A[2][0] + T.A[2][0], A[2][1] + T.A[2][1],
                  A[2][2] + T.A[2][2]);
  }
  auto operator*(const Type T) const noexcept -> tensor<Type> {
    return tensor<Type>(A[0][0] * T, A[0][1] * T, A[0][2] * T, A[1][0] * T, A[1][1] * T, A[1][2] * T, A[2][0] * T,
                        A[2][1] * T, A[2][2] * T);
  }
  auto operator*(const tensor &m) const noexcept -> tensor {
    return tensor{A[0] * m.A[0] + A[1] * m.A[3] + A[2] * m.A[6], A[0] * m.A[1] + A[1] * m.A[4] + A[2] * m.A[7],
                  A[0] * m.A[2] + A[1] * m.A[5] + A[2] * m.A[8], A[3] * m.A[0] + A[4] * m.A[3] + A[5] * m.A[6],
                  A[3] * m.A[1] + A[4] * m.A[4] + A[5] * m.A[7], A[3] * m.A[2] + A[4] * m.A[5] + A[5] * m.A[8],
                  A[6] * m.A[0] + A[7] * m.A[3] + A[8] * m.A[6], A[6] * m.A[1] + A[7] * m.A[4] + A[8] * m.A[7],
                  A[6] * m.A[2] + A[7] * m.A[5] + A[8] * m.A[8]};
  }

  auto operator*=(const tensor &m) noexcept -> tensor & {
    const tensor s = *this;

    A[0] = s.A[0] * m.A[0] + s.A[1] * m.A[3] + s.A[2] * m.A[6];
    A[1] = s.A[0] * m.A[1] + s.A[1] * m.A[4] + s.A[2] * m.A[7];
    A[2] = s.A[0] * m.A[2] + s.A[1] * m.A[5] + s.A[2] * m.A[8];
    A[3] = s.A[3] * m.A[0] + s.A[4] * m.A[3] + s.A[5] * m.A[6];
    A[4] = s.A[3] * m.A[1] + s.A[4] * m.A[4] + s.A[5] * m.A[7];
    A[5] = s.A[3] * m.A[2] + s.A[4] * m.A[5] + s.A[5] * m.A[8];
    A[6] = s.A[6] * m.A[0] + s.A[7] * m.A[3] + s.A[8] * m.A[6];
    A[7] = s.A[6] * m.A[1] + s.A[7] * m.A[4] + s.A[8] * m.A[7];
    A[8] = s.A[6] * m.A[2] + s.A[7] * m.A[5] + s.A[8] * m.A[8];
    return *this;
  }
  auto operator*(const vec3<Type> &V) const noexcept -> vec3<Type> {
    return vec3<Type>((V[0] * A[0] + V[1] * A[3] + V[2] * A[6]), (V[0] * A[1] + V[1] * A[4] + V[2] * A[7]),
                      (V[0] * A[2] + V[1] * A[5] + V[2] * A[8]));
  }
  auto Determ3x3() const noexcept -> Type {
    return A[0] * (A[4] * A[8] - A[5] * A[7]) + A[1] * (A[5] * A[6] - A[3] * A[8]) + A[2] * (A[3] * A[7] - A[4] * A[6]);
  }
  auto operator!() const noexcept -> Type { return Determ3x3(); } /* End of 'operator!' function */
  static auto Identity() noexcept -> tensor { return tensor(1, 0, 0, 0, 1, 0, 0, 0, 1); }
  auto Transpose() const noexcept -> tensor { return tensor{A[0], A[3], A[6], A[1], A[4], A[7], A[2], A[5], A[8]}; }
  auto Inverse() const noexcept -> tensor {
    const Type det = !(*this);
    if (det == 0) {
      return Identity();
    }

    const Type RevDet = 1 / det;
    return tensor{(A[4] * A[8] - A[5] * A[7]) * RevDet, (A[2] * A[7] - A[1] * A[7]) * RevDet,
                  (A[1] * A[5] - A[2] * A[4]) * RevDet, (A[5] * A[6] - A[3] * A[8]) * RevDet,
                  (A[0] * A[8] - A[2] * A[6]) * RevDet, (A[2] * A[3] - A[0] * A[5]) * RevDet,
                  (A[3] * A[7] - A[4] * A[6]) * RevDet, (A[1] * A[6] - A[0] * A[7]) * RevDet,
                  (A[0] * A[4] - A[1] * A[3]) * RevDet};
  }
  static auto Star(const vec3<Type> &W) noexcept -> tensor { return {0, -W[2], W[1], W[2], 0, -W[0], -W[1], W[0], 0}; }

}; /* End of 'tensor' class */
} // namespace mth

#endif /* __mth_tensor_h_ */

/* END OF 'mth_tensor.h' FILE */
