#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mth_def.h"

/* Math namespace */
namespace mth {
/* Forward declaration */
template <typename Type> class vec3;

/* Ray class */
template <typename Type> class ray {
  static_assert(std::is_arithmetic_v<Type>, "Number type is needed in ray");

public:
  vec3<Type> Org, // Ray origin
      Dir;        // Ray normalized direction

  ray() noexcept = default;
  ray(const vec3<Type> &O, const vec3<Type> &D) noexcept : Org(O), Dir(D) { Dir.Normalize(); }
  auto operator()(const Type T) const noexcept -> vec3<Type> { return Org + Dir * T; }
  auto operator[](const INT No) -> Type & { return *(&Org.X + No); }
  auto Intersect(const vec3<Type> &Center, const FLT Radius) const noexcept -> FLT {
    const FLT oc2 = (Center - Org) & (Center - Org);
    const FLT ok = (Center - Org) & Dir;
    const FLT h2 = Radius * Radius - (oc2 - ok * ok);

    if (oc2 < Radius * Radius) {
      return ok + sqrtf(h2);
    }
    if (ok < 0 || h2 < 0) {
      return -1;
    }
    return ok - sqrtf(h2);
  } /* End of 'Intersect' function */

}; /* End of 'ray' class */
} // namespace mth

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FILE */
