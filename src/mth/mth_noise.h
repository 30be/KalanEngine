#ifndef __mth_noise_h_
#define __mth_noise_h_

#include "mth_def.h"
#include <cmath>

#include <array>

template <typename Type1, INT Size> using array2 = std::array<std::array<Type1, Size>, Size>;
/* Math namespace */
namespace mth {
/* Noise class */
template <typename Type> class noise {
  static_assert(std::is_arithmetic_v<Type>, "Number type is needed in noise");

public:
  static const INT TAB_BITS = 8;
  static const INT TAB_SIZE = 1 << TAB_BITS;
  static const INT TAB_MASK = TAB_SIZE - 1;

  array2<Type, TAB_SIZE> TabNoise;

  noise() noexcept {
    for (INT i = 0; i < TAB_SIZE; i++) {
      for (INT j = 0; j < TAB_SIZE; j++) {
        TabNoise[j][i] = static_cast<Type>(rand()) / RAND_MAX;
      }
    }
  } /* End of 'noise' function */

  auto Noise1D(const Type X) const noexcept -> Type {
    INT ix = floor(X);
    INT ix1 = 0;
    const Type fx = X - ix;

    ix &= TAB_MASK;
    ix1 = (ix + 1) & TAB_MASK;
    return TabNoise[0][ix] * (1 - fx) + TabNoise[0][ix1] * fx;
  } /* End of 'Noise1D' function */
  auto NoiseTurb1D(const Type X, const INT Octaves) const noexcept -> Type {
    INT frac = 1;
    Type val = 0;

    for (int i = 0; i < Octaves; i++) {
      val += Noise1D(X) / frac;
      X = (X + 29.47) * 2;
      frac *= 2;
    }
    return val * (1 << (Octaves - 1)) / ((1 << Octaves) - 1);
  }

  [[nodiscard]] auto Noise2D(const FLT X, const FLT Y) const noexcept -> FLT {
    INT ix = static_cast<INT>(floor(X));
    INT ix1 = 0;
    INT iy = static_cast<INT>(floor(Y));
    INT iy1 = 0;
    FLT fx = X - static_cast<FLT>(ix);
    FLT fy = Y - static_cast<FLT>(iy);

    fx = (3 - 2 * fx) * fx * fx;
    fy = (3 - 2 * fy) * fy * fy;
    ix &= TAB_MASK;
    ix1 = (ix + 1) & TAB_MASK;
    iy &= TAB_MASK;
    iy1 = (iy + 1) & TAB_MASK;

    return TabNoise[ix][iy] * (1 - fx) * (1 - fy) + TabNoise[ix1][iy] * fx * (1 - fy) +
           TabNoise[ix][iy1] * (1 - fx) * fy + TabNoise[ix1][iy1] * fx * fy;
  }

  [[nodiscard]] auto NoiseTurb2D(const FLT X, const FLT Y, const INT Octaves) const noexcept -> FLT {
    INT frac = 1;
    FLT val = 0;

    for (int i = 0; i < Octaves; i++) {
      val += Noise2D(X, Y) / frac;
      this->X = (X + 29.47) * 2;
      this->Y = (Y + 18.102) * 2;
      frac *= 2;
    }
    return val * static_cast<FLT>(1 << (Octaves - 1)) / static_cast<FLT>((1 << Octaves) - 1);
  }

}; /* End of 'noise' class */
} // namespace mth

#endif /* __mth_noise_h_ */
