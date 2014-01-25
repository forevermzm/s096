#include <memory>
#include <vector>
#include <iostream>

class Directory;
class Node;
//typedef std::unique_ptr<Node> NodePtr;
typedef Node* NodePtr;

class Node {
public:
  virtual ~Node() {}
  virtual void ls() = 0;
  virtual void lsIndented( int indent ) = 0;
  virtual Directory* getDirectory() { return nullptr; }
};

class Directory : public Node {
  std::string _name;
  std::vector<NodePtr> _children;
public:
  Directory() : 
    _name{ "/" }, 
    _children{} {}
  Directory( std::string dirname ) : 
    _name{dirname + "/"}, 
    _children{} {}
  void add( NodePtr item ) { _children.push_back( item ); }
  void ls();
  void lsIndented( int indent );
  virtual Directory* getDirectory() { return this; }

  static NodePtr create( std::string dirname );
};

void Directory::ls() {
  lsIndented( 0 );
}

void Directory::lsIndented( int indent ) {
  for( int i = 0; i < indent; ++i ) {
    std::cout << '\t';
  }
  std::cout << _name << '\n';
  for( auto child : _children ) {
    child->lsIndented( indent + 1 );
  }
}

class File : public Node {
  std::string _name;
  File() = delete;
  void lsIndented( int indent );
public:
  File( std::string filename ) : 
    _name(filename) {}
  void ls();

  static NodePtr create( std::string filename );
};

void File::lsIndented( int indent ) {
  for( int i = 0; i < indent; ++i ) {
    std::cout << '\t';
  }
  std::cout << _name << '\n';
}

void File::ls() {
  lsIndented( 0 );
}

NodePtr Directory::create( std::string dirname ) {
  return NodePtr( new Directory{ dirname } );
}

NodePtr File::create( std::string filename ) {
  return NodePtr( new File{ filename } );
}

int main() {
  auto projectDir = Directory::create( "project" );
  auto makefile = File::create( "Makefile" );
  auto graderInfo = File::create( "GRADER_INFO.txt" );

  auto srcDir = Directory::create( "src" );
  auto includeDir = Directory::create( "include" );
  auto listH =  File::create( "list.h" );
  auto listC =  File::create( "list.c" );
  auto testC =  File::create( "test.c" );

  auto dirPtr = projectDir->getDirectory();
  if( dirPtr != nullptr ) {
    dirPtr->add( makefile );
    dirPtr->add( graderInfo );
    dirPtr->add( srcDir );
    dirPtr->add( includeDir );
  }

  dirPtr = srcDir->getDirectory();
  if( dirPtr != nullptr ) {
    dirPtr->add( listC );
    dirPtr->add( testC );
  }

  dirPtr = includeDir->getDirectory();
  if( dirPtr != nullptr ) {
    dirPtr->add( listH );
  }

  projectDir->ls();
  return 0;
}
