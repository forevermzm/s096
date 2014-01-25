#include <queue>
#include <stack>
#include <iostream>

int main() {
  std::queue<float> floatQueue;
  std::stack<float> floatStack;

  for( int i = 0; i < 10; ++i ) {
    floatQueue.push( (float) i );
    floatStack.push( (float) i );
  }

  while( !floatStack.empty() ) {
    std::cout << floatStack.top() << "\n";
    floatStack.pop();
  }
  /*while( !floatQueue.empty() ) {
    std::cout << floatQueue.front() << "\n";
    floatQueue.pop();
  }*/

  return 0;
}
