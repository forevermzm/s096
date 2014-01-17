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
  State( size_t aNode, double aDist ) : _node{aNode}, _dist{aDist} {}
  inline size_t node() const { return _node; }
  inline double dist() const { return _dist; }
};

class AdjacencyList {
  size_t _size;
  std::vector< std::vector<State> > _vert;
  AdjacencyList();
public:
  AdjacencyList( std::istream &input );
  inline size_t size() const { return _size; }
  inline const std::vector<State>& vert( size_t node ) const { return _vert[node]; }
  void print();
};

inline bool operator<( const State &a, const State &b ) {
  return a.dist() > b.dist();
}

AdjacencyList::AdjacencyList( std::istream &input ) : _size{}, _vert{} {
  input >> _size;
  _vert.resize( _size );

  for( auto &adj : _vert ) {
    size_t nAdj; input >> nAdj;
    for( size_t i = 0; i < nAdj; ++i ) {
      size_t node; double weight;
      input >> node >> weight;
      adj.push_back( State{ node, weight } );
    }
  }
}

void AdjacencyList::print() {
  for( size_t i = 0; i < _vert.size(); ++i ) {
    std::cout << i << ": ";
    for( auto state : _vert[i] ) {
      std::cout << "(" << state.node() << ", " << state.dist() << ") ";
    }
    std::cout << "\n";
  }
}

double prim( const AdjacencyList &adj ) {
  double weight = 0.0;
  bool visited[MAXN];
  memset( visited, false, sizeof( visited ) );
  std::priority_queue<State> pq;
  pq.push( State{ 0, 0.0 } );

  while( !pq.empty() ) {
    auto top = pq.top(); pq.pop();

    if( !visited[top.node()] ) {
      std::cout << "visiting node " << top.node() << "\n";
      visited[top.node()] = true;
      weight += top.dist();

      for( auto vertex : adj.vert( top.node() ) ) {
        pq.push( vertex );
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
    adj.print();
    output << prim( adj ) << "\n";
  } else {
    std::cerr << "Could not open mst.in\n";
    return 1;
  }
  
  return 0;
}
