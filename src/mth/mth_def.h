#ifndef __mth_def_h_
#define __mth_def_h_

#include <cmath>
#include <numbers>
using INT = int;
/* Real numbers types */
using FLT = float;
using DBL = double;

namespace mth {
template <typename Type> inline auto D2R(Type Angle) noexcept -> FLT {
  return Angle * std::numbers::pi / 180;
} /* End of 'D2R' function */
template <typename Type> inline auto R2D(Type Angle) noexcept -> FLT {
  return Angle * 180 / std::numbers::pi;
} /* End of 'R2D' function */
template <typename Type> class vec4;
template <typename Type> class vec3;
template <typename Type> class vec2;
template <typename Type> class matr;
} // namespace mth

#endif /* __mth_def_h_ */
