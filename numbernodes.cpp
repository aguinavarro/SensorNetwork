// Agui Navarro
// Sensor Node Test
// numbernodes.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define INITIAL_CONNECTIONS 10

using namespace std;

int numnodes = INITIAL_CONNECTIONS;
int totalenergy = 0;

void recursivenodes(int connections, int distance);

int main() {
  srand(time(NULL));
  recursivenodes(INITIAL_CONNECTIONS, 0);
  cout << "Number of nodes: " << numnodes << endl;
  cout << "Total energy: " << totalenergy << endl;
  return 0;
}

void recursivenodes(int connections, int distance) {
  if (connections <= 1)
    return;

  for (int i = 0; i < connections; i++) {
    int dummy = (int)(connections/(pow(2.0, distance)));
    if (dummy == 0)
      return;
    int connect = rand() % dummy + 0;
    numnodes += connect;
    totalenergy += (connect+1)*10;
    recursivenodes(connect, distance+1);
  }
  return;
}
