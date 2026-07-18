#include <boost/test/unit_test.hpp>
#include "graph.hpp"

BOOST_AUTO_TEST_CASE(basic_tests)
{
  Graph< int > gr1;
  BOOST_TEST(gr1.empty());
  BOOST_TEST(gr1.vertices() == 0ull);
  BOOST_TEST(gr1.edges() == 0ull);
  BOOST_TEST(gr1.degree(1) == 0ull);

  gr1.add_vertex(1);
  BOOST_TEST(!gr1.empty());
  BOOST_TEST(gr1.vertices() == 1ull);
  BOOST_TEST(gr1.edges() == 0ull);
  BOOST_TEST(gr1.degree(1) == 0ull);

  gr1.add_vertex(3);
  BOOST_TEST(gr1.vertices() == 2ull);

  gr1.add_edge(1, 3);
  BOOST_TEST(gr1.edges() == 1ull);
  BOOST_TEST(gr1.degree(1) == 1ull);
  BOOST_TEST(gr1.degree(3) == 1ull);

  gr1.add_vertex(3);
  BOOST_TEST(gr1.vertices() == 2ull);

  gr1.add_edge(1, 3);
  BOOST_TEST(gr1.edges() == 1ull);
  BOOST_TEST(gr1.degree(1) == 1ull);
  BOOST_TEST(gr1.degree(3) == 1ull);

  gr1.add_vertex(2);
  BOOST_TEST(gr1.vertices() == 3ull);

  gr1.add_edge(3, 2);
  gr1.add_edge(3, 3);
  BOOST_TEST(gr1.edges() == 3ull);

  gr1.clear();
  BOOST_TEST(gr1.empty());
}

