
#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mth_def.h"

#include <format>

/* Math namespace */
namespace mth {
/* Forward declaration */
template <typename Type> class vec2;
template <typename Type> class vec4;

/* Vector 3D */
template <typename Type> class vec3 {
  static_assert(std::is_arithmetic_v<Type>, "Number type is needed in vec3");

public:
  Type X, Y, Z;

  vec3() noexcept : X(0), Y(0), Z(0) {} /* End of 'vec3' constructor */
  vec3(vec3 &&) = delete;
  auto operator=(const vec3 &) -> vec3 & = delete;
  auto operator=(vec3 &&) -> vec3 & = delete;
  explicit vec3(const Type A) noexcept : X(A), Y(A), Z(A) {}                    /* End of 'vec3' constructor */
  vec3(const Type A, const Type B, const Type C) noexcept : X(A), Y(B), Z(C) {} /* End of 'vec3' constructor */
  explicit vec3(const vec2<Type> &V, const Type C = 0) noexcept : X(V.X), Y(V.Y), Z(C) {}
  vec3(const vec3<Type> &V) noexcept : X(V.X), Y(V.Y), Z(V.Z) {}          /* End of 'vec3' constructor */
  explicit vec3(const vec4<Type> &V) noexcept : X(V.X), Y(V.Y), Z(V.Z) {} /* End of 'vec3' constructor */
  explicit operator Type *() const noexcept { return &X; }
  auto operator[](const INT Ind) const -> Type { return *(&X + Ind); } /* End of 'operator[]' function */
  auto operator[](const INT Ind) -> Type & { return *(&X + Ind); }     /* End of 'operator[]' function */
  auto operator+(const vec3 &V) const noexcept -> vec3 { return vec3(X + V.X, Y + V.Y, Z + V.Z); }
  auto operator+=(const vec3 &V) noexcept -> vec3 & {
    X += V.X;
    Y += V.Y;
    Z += V.Z;
    return *this;
  }
  auto operator-(const vec3 &V) const noexcept -> vec3 { return vec3(X - V.X, Y - V.Y, Z - V.Z); }
  auto operator-=(const vec3 &V) noexcept -> vec3 & {
    X -= V.X;
    Y -= V.Y;
    Z -= V.Z;
    return *this;
  }
  auto operator-() const noexcept -> vec3 { return vec3(-X, -Y, -Z); }
  auto operator*(const vec3 &V) const noexcept -> vec3 { return vec3(X * V.X, Y * V.Y, Z * V.Z); }
  auto operator*=(const vec3 &V) noexcept -> vec3 & {
    X *= V.X;
    Y *= V.Y;
    Z *= V.Z;
    return *this;
  }
  auto operator*(const Type N) const noexcept -> vec3 { return vec3(X * N, Y * N, Z * N); }
  auto operator*=(const Type N) noexcept -> vec3 & {
    X *= N;
    Y *= N;
    Z *= N;
    return *this;
  }
  auto operator/(const vec3 &V) const -> vec3 { return vec3(X / V.X, Y / V.Y, Z / V.Z); }
  auto operator/=(const vec3 &V) -> vec3 & {
    X /= V.X;
    Y /= V.Y;
    Z /= V.Z;
    return *this;
  }
  auto operator/(const Type N) const -> vec3 { return vec3(X / N, Y / N, Z / N); } /* End of 'operator/' function */
  auto operator/=(const Type N) -> vec3 & {
    X /= N;
    Y /= N;
    Z /= N;
    return *this;
  }
  auto operator&(const vec3 &V) const noexcept -> Type { return X * V.X + Y * V.Y + Z * V.Z; }
  auto operator%(const vec3 &V) const noexcept -> vec3 {
    return vec3(Y * V.Z - Z * V.Y, -X * V.Z + Z * V.X, X * V.Y - Y * V.X);
  }
  auto operator%=(const vec3 &V) noexcept -> vec3 & {
    const vec3 Saved = *this;

    X = Saved.Y * V.Z - Saved.Z * V.Y;
    Y = -Saved.X * V.Z + Saved.Z * V.X;
    Z = Saved.X * V.Y - Saved.Y * V.X;
    return *this;
  }
  auto Length2() const noexcept -> Type { return X * X + Y * Y + Z * Z; }
  auto Length() const noexcept -> Type {
    if constexpr (std::is_same_v<Type, FLT>) {
      return sqrtf(X * X + Y * Y + Z * Z);
    } else {
      return sqrt(X * X + Y * Y + Z * Z);
    }
  }
  auto operator!() const noexcept -> Type {
    return std::is_same_v<Type, FLT> ? sqrtf(X * X + Y * Y + Z * Z) : sqrt(X * X + Y * Y + Z * Z);
  }
  auto Normalize() noexcept -> vec3 & { return (X == 0 && Y == 0 && Z == 0) ? *this : *this /= Length(); }
  auto Normalizing() const noexcept -> vec3 {
    if (X == 0 && Y == 0 && Z == 0) {
      return vec3(0);
    }
    return *this / Length();
  }
  auto MaxC() const noexcept -> Type { return max(max(X, Y), Z); }             /* End of 'MaxC' function */
  auto MinC() const noexcept -> Type { return min(min(X, Y), Z); }             /* End of 'MinC' function */
  auto Distance(const vec3 &V) const noexcept -> Type { return !(*this - V); } /* End of 'Distance' function */
  auto Lerp(const vec3 &V, const Type T) const noexcept -> vec3 {
    return vec3(std::lerp(X, V.X, T), std::lerp(Y, V.Y, T), std::lerp(Z, V.Z, T));
  }
  auto Max(const vec3 &V) const noexcept -> vec3 { return vec3(max(V.X, X), max(V.Y, Y), max(V.Z, Z)); }
  auto Min(const vec3 &V) const noexcept -> vec3 { return vec3(min(V.X, X), min(V.Y, Y), min(V.Z, Z)); }
  auto Ceil() const noexcept -> vec3 { return vec3(std::ceil(X), std::ceil(Y), std::ceil(Z)); }
  auto Floor() const noexcept -> vec3 { return vec3(std::floor(X), std::floor(Y), std::floor(Z)); }
  auto Angle(const vec3 &V) const noexcept -> Type {
    const Type MulLen2 = Length2() * V.Length2();
    if (MulLen2 == 0) {
      return 0;
    }
    const Type angle = acos((*this & V) / sqrt(MulLen2));
    return R2D(((-X * V.Z + Z * V.X) < 0) ? -angle : angle);
  }
  static auto Rnd0() noexcept -> vec3 {
    return vec3(static_cast<DBL>(rand()) / RAND_MAX, static_cast<DBL>(rand()) / RAND_MAX,
                static_cast<DBL>(rand()) / RAND_MAX);
  }
  static auto Rnd1() noexcept -> vec3 {
    return vec3(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1, static_cast<DBL>(rand()) / RAND_MAX * 2 - 1,
                static_cast<DBL>(rand()) / RAND_MAX * 2 - 1);
  }
  static auto Rnd() noexcept -> vec3 { return vec3(rand(), rand(), rand()); }
  [[nodiscard]] auto Index3D(const vec3<INT> &Size) const noexcept -> INT {
    return Size.X * (static_cast<INT>(Y) * Size.Z + static_cast<INT>(Z)) + static_cast<INT>(X);
  }
  [[nodiscard]] auto ToString() const noexcept -> std::string { return std::format("{} {} {}", X, Y, Z); }
}; /* End of 'vec3' class */

/* Integer vector 3D */
class ivec3 : public vec3<INT> {}; /* End of 'ivec3' class */
} // namespace mth

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */
