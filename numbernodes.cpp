// Agui Navarro
// Sensor Node Test
// numbernodes.cpp

// This file was the initial brainstorming file. The network had to
// be created before any further tasks were implemented. After around
// one hour, thoughts of a recursive implementation circled.
// A few hours later, this file was completed and the network
// was in place.

// Details for the implementation are in main.cpp

#include <iostream>
#include <cmath> // pow()

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
