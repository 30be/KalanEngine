#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mth_def.h"

#include <format>

/* Math namespace */
namespace mth {
/* Forward declaration */
template <typename Type> class vec2;
template <typename Type> class vec3;

/* Vector 4D */
template <typename Type> class vec4 {
  static_assert(std::is_arithmetic_v<Type>, "Number type is needed in vec4");

public:
  Type X{}, Y{}, Z{}, W{};
  vec4() = default;
  explicit vec4(const Type Component) noexcept : X(Component), Y(Component), Z(Component), W(Component) {}

  vec4(const Type A, const Type B, const Type C, const Type D) noexcept // NOLINT
      : X(A), Y(B), Z(C), W(D) {}

  vec4(const vec2<Type> &V, const Type C = 0, const Type D = 0) noexcept // NOLINT
      : X(V.X), Y(V.Y), Z(C), W(D) {}

  vec4(const vec3<Type> &V, const Type D = 0) noexcept : X(V.X), Y(V.Y), Z(V.Z), W(D) {} // NOLINT

  vec4(const vec4<Type> &V) noexcept : X(V.X), Y(V.Y), Z(V.Z), W(V.W) {} // NOLINT

  explicit operator Type *() const noexcept { return &X; }

  auto operator[](const INT Ind) const -> Type { return *(&X + Ind); }

  auto operator[](const INT Ind) -> Type & { return *(&X + Ind); }

  auto operator+(const vec4 &V) const noexcept -> vec4 { return vec4(X + V.X, Y + V.Y, Z + V.Z, W + V.W); } // NOLINT
  vec4 &operator+=(const vec4 &V) noexcept {                                                                // NOLINT
    X += V.X;
    Y += V.Y;
    Z += V.Z;
    W += V.W;
    return *this;
  }
  auto operator-(const vec4 &V) const noexcept -> vec4 { return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W); } // NOLINT

  auto operator-=(const vec4 &V) noexcept -> vec4 & { // NOLINT
    X -= V.X;
    Y -= V.Y;
    Z -= V.Z;
    W -= V.W;
    return *this;
  }

  vec4 operator-() const noexcept { return vec4(-X, -Y, -Z, -W); }                                          // NOLINT
  auto operator*(const vec4 &V) const noexcept -> vec4 { return vec4(X * V.X, Y * V.Y, Z * V.Z, W * V.W); } // NOLINT

  auto operator*=(const vec4 &V) noexcept -> vec4 & {
    X *= V.X;
    Y *= V.Y;
    Z *= V.Z;
    W *= V.W;
    return *this;
  }

  auto operator*(const Type N) const noexcept -> vec4 { return vec4(X * N, Y * N, Z * N, W * N); }

  auto operator*=(const Type N) noexcept -> vec4 & {
    X *= N;
    Y *= N;
    Z *= N;
    W *= N;
    return *this;
  }

  auto operator/(const vec4 &V) const -> vec4 { return vec4(X / V.X, Y / V.Y, Z / V.Z, W / V.W); }

  auto operator/=(const vec4 &V) -> vec4 & {
    X /= V.X;
    Y /= V.Y;
    Z /= V.Z;
    W /= V.W;
    return *this;
  }

  auto operator/(const Type N) const -> vec4 { return vec4(X / N, Y / N, Z / N, W / N); }

  auto operator/=(const Type N) -> vec4 & {
    X /= N;
    Y /= N;
    Z /= N;
    W /= N;
    return *this;
  }

  auto operator&(const vec4 &V) const noexcept -> Type { return X * V.X + Y * V.Y + Z * V.Z + W * V.W; }

  [[nodiscard]] auto Length2() const noexcept -> Type { return X * X + Y * Y + Z * Z + W * W; }
  [[nodiscard]] auto Length() const noexcept -> Type {
    if constexpr (std::is_same_v<Type, FLT>) {
      return sqrtf(X * X + Y * Y + Z * Z + W * W);
    } else {
      return sqrt(X * X + Y * Y + Z * Z + W * W);
    }
  }

  auto Normalize() noexcept -> vec4 & {
    if (X == 0 && Y == 0 && Z == 0 && W == 0) {
      return *this;
    }
    return *this /= Length();
  }
  [[nodiscard]] auto Normalized() const noexcept -> vec4 {
    if (X == 0 && Y == 0 && Z == 0 && W == 0) {
      return vec4(0);
    }
    return *this / Length();
  }

  [[nodiscard]] auto MaxC() const noexcept -> Type { return max(max(X, Y), max(Z, W)); }

  [[nodiscard]] auto MinC() const noexcept -> Type { return min(min(X, Y), min(Z, W)); }

  [[nodiscard]] auto Distance(const vec4 &V) const noexcept -> Type { return !(*this - V); }

  [[nodiscard]] auto Lerp(const vec4 &V, const Type T) const noexcept -> vec4 {
    return vec4(std::lerp(X, V.X, T), std::lerp(Y, V.Y, T), std::lerp(Z, V.Z, T), std::lerp(W, V.W, T));
  }

  [[nodiscard]] auto Max(const vec4 &V) const noexcept -> vec4 {
    return vec4(max(V.X, X), max(V.Y, Y), max(V.Z, Z), max(W, V.W));
  }
  [[nodiscard]] auto Min(const vec4 &V) const noexcept -> vec4 {
    return vec4(min(V.X, X), min(V.Y, Y), min(V.Z, Z), min(W, V.W));
  }

  [[nodiscard]] auto Ceil() const noexcept -> vec4 {
    return vec4(std::ceil(X), std::ceil(Y), std::ceil(Z), std::ceil(W));
  }

  [[nodiscard]] auto Floor() const noexcept -> vec4 {
    return vec4(std::floor(X), std::floor(Y), std::floor(Z), std::floor(W));
  }

  [[nodiscard]] auto Volume() const noexcept -> Type { return X * Y * Z * W; } /* End of 'Volume' function */

  static auto Rnd0() noexcept -> vec4 {
    return vec4(static_cast<DBL>(std::rand()) / RAND_MAX, static_cast<DBL>(std::rand()) / RAND_MAX,
                static_cast<DBL>(rand()) / RAND_MAX, static_cast<DBL>(rand()) / RAND_MAX);
  }

  static auto Rnd1() noexcept -> vec4 {
    return vec4(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1, static_cast<DBL>(rand()) / RAND_MAX * 2 - 1,
                static_cast<DBL>(rand()) / RAND_MAX * 2 - 1, static_cast<DBL>(rand()) / RAND_MAX * 2 - 1);
  } /* End of 'Rnd1' function */

  static auto Rnd() noexcept -> vec4 { return vec4(rand(), rand(), rand(), rand()); }

  [[nodiscard]] auto ToString() const noexcept -> std::string { return std::format("{} {} {} {}", X, Y, Z, W); }
};

class ivec4 : public vec4<INT> {};
} // namespace mth

#endif /* __mth_vec4_h_ */
