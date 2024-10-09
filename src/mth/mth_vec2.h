#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mth_def.h"

#include <format>

/* Math namespace */
namespace mth {
/* Forward declaration */
template <typename Type> class vec3;
template <typename Type> class vec4;

/* Vector 2D */
template <typename Type> class vec2 {
  static_assert(std::is_arithmetic_v<Type>, "Number type is needed in vec2");

public:
  Type X, Y;

  vec2() noexcept : X(0), Y(0) {}                                      /* End of 'vec2' constructor */
  explicit vec2(const Type A) noexcept : X(A), Y(A) {}                 /* End of 'vec2' constructor */
  vec2(const Type A, const Type B) noexcept : X(A), Y(B) {}            /* End of 'vec2' constructor */
  vec2(const vec2<Type> &V) noexcept : X(V.X), Y(V.Y) {}               /* End of 'vec2' constructor */
  explicit vec2(const vec3<Type> &V) noexcept : X(V.X), Y(V.Y) {}      /* End of 'vec2' constructor */
  explicit vec2(const vec4<Type> &V) noexcept : X(V.X), Y(V.Y) {}      /* End of 'vec2' constructor */
  explicit operator Type *() const noexcept { return &X; }             /* End of 'operator Type*' function */
  auto operator[](const INT Ind) const -> Type { return *(&X + Ind); } /* End of 'operator[]' function */
  auto operator[](const INT Ind) -> Type & { return *(&X + Ind); }     /* End of 'operator[]' function */
  auto operator+(const vec2 &V) const noexcept -> vec2 { return vec2(X + V.X, Y + V.Y); }
  auto operator+=(const vec2 &V) noexcept -> vec2 & {
    X += V.X;
    Y += V.Y;
    return *this;
  }
  auto operator-(const vec2 &V) const noexcept -> vec2 { return vec2(X - V.X, Y - V.Y); }
  auto operator-=(const vec2 &V) noexcept -> vec2 & {
    X -= V.X;
    Y -= V.Y;
    return *this;
  }
  auto operator-() const noexcept -> vec2 { return vec2(-X, -Y); } /* End of 'operator-' function */
  auto operator*(const vec2 &V) const noexcept -> vec2 {
    return vec2(X * V.X, Y * V.Y);
  } /* End of 'operator*' function */
  auto operator*=(const vec2 &V) noexcept -> vec2 & {
    X *= V.X;
    Y *= V.Y;
    return *this;
  }
  auto operator*(const Type N) const noexcept -> vec2 { return vec2(X * N, Y * N); } /* End of 'operator*' function */
  auto operator*=(const Type N) noexcept -> vec2 & {
    X *= N;
    Y *= N;
    return *this;
  }
  auto operator/(const vec2 &V) const -> vec2 { return vec2(X / V.X, Y / V.Y); } /* End of 'operator/' function */
  auto operator/=(const vec2 &V) -> vec2 & {
    X /= V.X;
    Y /= V.Y;
    return *this;
  }
  auto operator/(const Type N) const -> vec2 { return vec2(X / N, Y / N); } /* End of 'operator/' function */
  auto operator/=(const Type N) -> vec2 & {
    X /= N;
    Y /= N;
    return *this;
  }
  auto operator&(const vec2 &V) const noexcept -> Type { return X * V.X + Y * V.Y; } /* End of 'operator&' function */
  auto Length2() const noexcept -> Type { return X * X + Y * Y; }
  auto Length() const noexcept -> Type {
    return (std::is_same_v<Type, FLT>) ? sqrtf(X * X + Y * Y) : sqrt(X * X + Y * Y);
  }
  auto operator!() const noexcept -> Type { return sqrt(X * X + Y * Y); }
  auto Normalize() noexcept -> vec2 & { return (X == 0 && Y == 0) ? *this : *this /= Length(); }
  auto Normalizing() const noexcept -> vec2 { return (X == 0 && Y == 0) ? vec2(0) : *this / Length(); }
  auto MaxC() const noexcept -> Type { return max(X, Y); }                     /* End of 'MaxC' function */
  auto MinC() const noexcept -> Type { return min(X, Y); }                     /* End of 'MinC' function */
  auto Distance(const vec2 &V) const noexcept -> Type { return !(*this - V); } /* End of 'Distance' function */
  auto Lerp(const vec2 &V, const Type T) const noexcept -> vec2 { return {std::lerp(X, V.X, T), std::lerp(Y, V.Y, T)}; }
  auto Max(const vec2 &V) const noexcept -> vec2 { return vec2(max(V.X, X), max(V.Y, Y)); } /* End of 'Max' function */
  auto Min(const vec2 &V) const noexcept -> vec2 { return vec2(min(V.X, X), min(V.Y, Y)); } /* End of 'Min' function */
  auto Ceil() const noexcept -> vec2 { return vec2(std::ceil(X), std::ceil(Y)); }           /* End of 'Ceil' function */
  auto Floor() const noexcept -> vec2 { return vec2(std::floor(X), std::floor(Y)); } /* End of 'Floor' function */
  auto Angle(const vec2 &V) const noexcept -> Type {
    const Type MulLen2 = Length2() * V.Length2();
    if (MulLen2 == 0) {
      return 0;
    }

    const Type angle = acos((*this & V) / sqrt(MulLen2));
    return R2D(((-X * V.Y + Y * V.X) < 0) ? -angle : angle);
  }
  auto Square() const noexcept -> Type { return X * Y; }
  static auto Rnd0() noexcept -> vec2 {
    return {static_cast<DBL>(rand()) / RAND_MAX, static_cast<DBL>(rand()) / RAND_MAX};
  }
  static auto Rnd1() noexcept -> vec2 {
    return vec2(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1, static_cast<DBL>(rand()) / RAND_MAX * 2 - 1);
  }
  [[nodiscard]] auto ToString() const noexcept -> std::string { return std::format("{} {}", X, Y); }
}; /* End of 'vec2' class */

class ivec2 : public vec2<INT> {}; /* End of 'ivec2' class */
} // namespace mth

#endif /* __mth_vec2_h_ */
