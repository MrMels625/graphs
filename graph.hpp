#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <list>

template< class T >
class Graph
{
public:
  void add_edge(const T&, const T&);
  void add_vertex(const T&);

  void remove_edge(const T&, const T&);
  void remove_vertex(const T&);

  size_t degree(const T&) noexcept;

  void clear() noexcept;

  size_t vertices() const noexcept;
  size_t edges() const noexcept;
  bool empty() const noexcept;

private:
  std::unordered_map< T, std::list< T > > adjacent_list;
};

template< class T >
void Graph< T >::add_edge(const T& first, const T& second)
{
  adjacent_list[first].push_back(second);
  if (first != second)
  {
    adjacent_list[second].push_back(first);
  }
}

template< class T >
void Graph< T >::add_vertex(const T& vertex)
{
  adjacent_list[vertex];
}

template< class T >
void Graph< T >::remove_edge(const T& first, const T& second)
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
void Graph< T >::remove_vertex(const T& vertex)
{
  if (adjacent_list.contains(vertex))
  {
    adjacent_list.erase(vertex);
  }
}

template< class T >
size_t Graph< T >::degree(const T& vertex) noexcept
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
  return 0ull;
}

template< class T >
bool Graph< T >::empty() const noexcept
{
  return adjacent_list.empty();
}

#endif

