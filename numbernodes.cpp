// Agui Navarro
// Sensor Node Test
// numbernodes.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define initialconnections 10

using namespace std;

int numnodes = 10;
srand(time(NULL));

void recursivenodes(int connections, int distance);

int main() {
  int dist = 0;
  recursivenodes(initialconnections, dist);
  cout << "Number of nodes: " << numnodes << endl;
  return 0;
}

void recursivenodes(int connections, int distance) {
  if (connections < 1) {
    return;
  }
  srand(time(0));

  for (int i = 0; i < connections; i++) {
    int connect = rand() % (connections/(pow(2.0, distance)) + 0)
    numnodes += connect;
    recursivenodes(connect, distance+1);
  }
}
