#include <iostream>
#include <chrono>
#include <random>

using namespace s
int main()
{
  // construct a trivial random generator engine from a time-based seed:
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);

  uniform_real_distribution<double> distribution (0.0,1.0);

  cout << "some random numbers between 0.0 and 100.0: " << endl;
  for (int i=0; i<10; ++i)
    cout << distribution(generator) << endl;

  return 0;
}