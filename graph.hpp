#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>

template< class T >
class Graph
{
public:

private:
  std::unordered_map< T, std::vector< T > > adjacent_list;
};

#endif

