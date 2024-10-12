#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

// Returns the first element in the range that satisfies pred, or other if none do.
template <std::ranges::input_range R, class Proj = std::identity,
          std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<R>, Proj>> Pred>
constexpr auto find_if_or(R &&r, Pred pred,
                          const std::ranges::range_value_t<R> &other) -> std::ranges::range_value_t<R> {
  auto f = std::ranges::find_if(r, pred);
  if (f == r.end()) {
    return other;
  }
  return *f;
}
