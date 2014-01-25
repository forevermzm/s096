int f(void) {
  int a = 1;
  ++a;
  a++;
  return a;
}

int main(void) {
  int array[10];
  array[0] = 1;
  array[9] = 2;
  f();
}
