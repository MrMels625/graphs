#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

template< class T, class ID = size_t >
struct Vertex
{
  ID id;
  T value;
  std::vector< ID > neighbors;
};

#endif

