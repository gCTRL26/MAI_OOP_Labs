#pragma once

#include <type_traits>

template <class T>
concept Arithmetic = std::is_arithmetic_v<T>;