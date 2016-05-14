#ifndef POINT_TEMPLATE_HPP
#define POINT_TEMPLATE_HPP

#include <array>

namespace astar {

template<typename T, unsigned int D>
using Point = std::array<T, D>;

}

#endif
