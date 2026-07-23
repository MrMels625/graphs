#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stack>
#include <queue>
#include "vertex.hpp"

template< class T, class ID = size_t >
class Graph
{
public:
  using V = Vertex< T, ID >;

  void add_edge(const V&, const V&);
  void add_vertex(const V&);

  void remove_edge(const V&, const V&);
  void remove_vertex(const V&);

  size_t degree(const V&) noexcept;

  void clear() noexcept;

  size_t vertices() const noexcept;
  size_t edges() const noexcept;
  bool empty() const noexcept;

  template< class F >
  void dfs(const V&, F);
  template< class F >
  void bfs(const V&, F);

  bool operator==(const Graph& other) const;
  bool operator!=(const Graph& other) const;

private:
  std::unordered_map< ID, V > adjacent_list;
};

template< class T >
void Graph< T >::add_edge(const V& first, const V& second)
{
  adjacent_list[first.value].push_back(second);
  if (first != second)
  {
    adjacent_list[second].push_back(first);
  }
}

template< class T >
void Graph< T >::add_vertex(const V& vertex)
{
  adjacent_list[vertex];
}

template< class T >
void Graph< T >::remove_edge(const V& first, const V& second)
{
  if (adjacent_list.contains(first) && adjacent_list.contains(second))
  {
    adjacent_list[first].remove(second);
    if (first != second)
    {
      adjacent_list[second].remove(first);
    }
  }
}

template< class T >
void Graph< T >::remove_vertex(const V& vertex)
{
  if (adjacent_list.contains(vertex))
  {
    adjacent_list.erase(vertex);
  }
}

template< class T >
size_t Graph< T >::degree(const V& vertex) noexcept
{
  return adjacent_list.contains(vertex) ? adjacent_list[vertex].size() : 0ull;
}

template< class T >
void Graph< T >::clear() noexcept
{
  adjacent_list.clear();
}

template< class T >
size_t Graph< T >::vertices() const noexcept
{
  return adjacent_list.size();
}

template< class T >
size_t Graph< T >::edges() const noexcept
{
  size_t count = 0;
  for (auto pair: adjacent_list)
  {
    count += pair.second.size();
  }
  return count / 2;
}

template< class T >
bool Graph< T >::empty() const noexcept
{
  return adjacent_list.empty();
}

template< class T >
template< class F >
void Graph< T >::dfs(const V& vertex, F f)
{
  auto it = adjacent_list.find(vertex);
  if (!it)
  {
    return;
  }

  std::stack< ID > stack;
  stack.push(it->first);
  std::unordered_set< T > visited;

  while (!stack.empty())
  {
    f(adjacent_list[stack.top()].second);
    ID id = stack.top();
    visited.insert(id);
    stack.pop();
    for (size_t i = adjacent_list[id].second.size() - 1; i >= 0; --i)
    {
      ID idd = adjacent_list[id].second.neighbors[i];
      if (!visited.contains(idd))
      {
        stack.push(idd);
      }
    }
  }
}

template< class T >
template< class F >
void Graph< T >::bfs(const V&, F f)
{
}

template< class T >
bool Graph< T >::operator==(const Graph& other) const
{
  if (vertices() != other.vertices())
  {
    return false;
  }
  if (edges() != other.edges())
  {
    return false;
  }
  return true;
}

template< class T >
bool Graph< T >::operator!=(const Graph& other) const
{
  return !operator==(other);
}

#endif

