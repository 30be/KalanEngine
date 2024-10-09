#ifndef __mth_solver_h_
#define __mth_solver_h_

#include "mth_def.h"

/* Math namespace */

/* Solver namespace */
namespace mth::solver {
inline auto Sign(const DBL X) noexcept -> INT { return static_cast<INT>(X > 0) - static_cast<INT>(X < 0); }
inline void SquareSolver(const DBL a, const DBL b, const DBL c, DBL *S) noexcept {
  if (a == 0) {
    if (b == 0) {
      return;
    }
    S[0] = S[1] = -c / b;
    return;
  }

  const DBL D = b * b - a * c * 4;
  const DBL Rev2a = 1 / (2 * a);
  if (D > 0) {
    const DBL SqrtD = sqrt(D);
    S[0] = (-b + SqrtD) * Rev2a;
    S[1] = (-b - SqrtD) * Rev2a;
  } else if (D == 0) {
    S[0] = S[1] = -b * Rev2a;
  }
}

inline void CubicSolver(const DBL a, const DBL b, const DBL c, const DBL d, DBL *S) noexcept {
  constexpr DBL Rev2 = 1.0F / 2;
  constexpr DBL Rev3 = 1.0F / 3;

  if (a == 0) {
    SquareSolver(b, c, d, S);
    S[2] = S[1];
  }

  const DBL p = (3 * a * c - b * b) / (3 * a * a);
  const DBL q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a);
  const DBL D = (p * Rev3) * (p * Rev3) * (p * Rev3) + (q * Rev2) * (q * Rev2);

  if (D > 0) {
    const DBL gamma = sqrt(D);
    const DBL alpha = cbrt(-q * Rev2 + gamma);
    const DBL beta = cbrt(-q * Rev2 - gamma);

    S[0] = S[1] = S[2] = (alpha + beta) - (b / (3 * a));
  } else if (D == 0) {
    const DBL alpha = cbrt(-q * Rev2);

    S[0] = 2 * alpha - (b / (3 * a));
    S[1] = S[2] = (-alpha) - (b / (3 * a));
  } else if (D < 0) {
    const DBL r = sqrt(-(p * p * p) / 27);
    const DBL phi = acos(-q / (2 * r));

    S[0] = 2 * sqrt(-p * Rev3) * cos(phi * Rev3) - (b / (3 * a));
    S[1] = 2 * sqrt(-p * Rev3) * cos((phi + 2 * std::numbers::pi) * Rev3) - (b / (3 * a));
    S[2] = 2 * sqrt(-p * Rev3) * cos((phi + 4 * std::numbers::pi) * Rev3) - (b / (3 * a));
  }
} /* End of 'CubicSolver' function */

} // namespace mth::solver

#endif /* __mth_solver_h_ */

/* END OF 'mth_solver.h' FILE */
