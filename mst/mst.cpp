#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstring>
#include <iterator>
#include <initializer_list>

const int MAXN = 100005;

class State {
  size_t _node;
  double _dist;
public:
  State( const State& state ) : _node{state._node}, _dist{state._dist} {}
  State( size_t aNode, double aDist ) : _node{aNode}, _dist{aDist} {}
  inline size_t node() const { return _node; }
  inline double dist() const { return _dist; }

};

class AdjacencyList {
  size_t _size;
  std::vector< std::vector<State> > _list;
  AdjacencyList();
public:
  AdjacencyList( std::istream &input );
  inline size_t size() const { return _size; }
  inline std::vector<State> list( size_t node ) const { return _list[node]; }
};

bool operator<( const State &a, const State &b ) {
  return a.dist() < b.dist();
}

AdjacencyList::AdjacencyList( std::istream &input ) : _size{}, _list{} {
  input >> _size;
  _list.resize( _size );

  for( auto it = std::begin( _list ); it != std::end( _list ); ++it ) {
    size_t node; double weight;
    input >> node >> weight;
    it->push_back( State{ node, weight } );
  }
}

double prim( const AdjacencyList &adj ) {
  double weight = 0.0;
  bool visited[MAXN];
  memset( visited, false, sizeof( visited ) );
  std::priority_queue<State> pq;
  pq.push( State{ 0, 0.0 } );

  while( !pq.empty() ) {
    State top = pq.top(); pq.pop();

    if( !visited[top.node()] ) {
      visited[top.node()] = true;
      weight += top.dist();

      for( auto it = std::begin( adj.list( top.node() ) ); it != std::end( adj.list( top.node() ) ); ++it ) {
        pq.push( State{ *it } );
      }
    }
  }

  return weight;
}

int main() {
  std::ifstream input{ "mst.in" };
  std::ofstream output{ "mst.out" };

  if( input.is_open() ) {
    auto adj = AdjacencyList{ input };
    output << prim( adj ) << "\n";
  } else {
    std::cerr << "Could not open mst.in\n";
    return 1;
  }
  
  return 0;
}
