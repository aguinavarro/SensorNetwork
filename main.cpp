// Agui Navarro
// Sensor Network
// main.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

#define INITIAL_CONNECTIONS 10

using namespace std;

int totalindex = 0;
int numnodes = -1;
int totalenergy = 0;
float bandwith = 0.0;

typedef struct Node {
  struct Node * next;
  int index = 0;
  int numconnections = 0;
  int maxenergy = 0;
  int distance = 0;
  float rate = 0.0;
  bool power = true;
} Node;

typedef struct SensorNetwork {
  Node * front;
  Node * back;
} SensorNetwork;

SensorNetwork * create();
void remove(SensorNetwork * network);
void add(SensorNetwork * network, int connections, int distance, float rate);
void del(SensorNetwork * network);
void printnetwork(SensorNetwork * network);
void printnode(Node * node);
Node * find(SensorNetwork * network, int index);
void recursivenodes(SensorNetwork * network, int connections, int distance,
                    float rate);

int main() {
  SensorNetwork * network = create();
  srand(time(NULL));
  recursivenodes(network, INITIAL_CONNECTIONS, 0, 1);
  cout << "Number of nodes: " << numnodes << endl;
  cout << "Total energy: " << totalenergy << endl;

  int random = rand() % numnodes + 0;
  /*cout << "Finding node " << random << "..." << endl;
  Node * randomnode = find(network, random);
  if (!randomnode) {
  } else {
    printnode(randomnode);
  }*/

  cout << "Printing network..." << endl;
  printnetwork(network);
  return 0;
}

SensorNetwork * create() {
  SensorNetwork * network = new SensorNetwork;
  network->front = NULL;
  network->back = NULL;
  return network;
}

void remove(SensorNetwork * network) {
  if (!network)
    return;
  while (network->front) {
    del(network);
  }
  delete network;
}

void add(SensorNetwork * network, int connections, int distance, float rate) {
  Node * newnode = new Node;
  newnode->index = totalindex++;
  newnode->numconnections = connections;
  newnode->maxenergy = (connections+1) * 10;
  newnode->distance = distance;
  newnode->rate = rate;
  newnode->power = true;

  if (!network->front) {
    network->front = newnode;
    network->back = newnode;
    network->back->next = NULL;
  } else {
    network->back->next = newnode;
    network->back = newnode;
    network->back->next = NULL;
  }
}

void del(SensorNetwork * network) {
  Node * ptr;
  if (!network->front)
    return;
  else {
    ptr = network->front;
    network->front = network->front->next;
    delete ptr;
  }
}

void printnetwork(SensorNetwork * network) {
  if (!network) {
    cout << "No network to print." << endl;
    return;
  } else {
    Node * ptr = network->front;
    while (ptr && ptr->next) {
      cout << "Index: " << setw(5) << left << ptr->index;
      cout << " Connections: " << setw(5) << left << ptr->numconnections;
      cout << " Max energy: " << setw(5) << left << ptr->maxenergy;
      cout << " Distance: " << setw(5) << left << ptr->distance;
      cout << " Rate: " << setw(5) << left << ptr->rate << endl;
      ptr = ptr->next;
    }
  }
  return;
}

void printnode(Node * node) {
  cout << "Index: " << setw(3) << left << node->index;
  cout << " Connections: " << setw(2) << left << node->numconnections;
  cout << " Max energy: " << setw(3) << left << node->maxenergy;
  cout << " Distance: " << setw(2) << left << node->distance;
  cout << " Rate: " << setw(5) << left << node->rate << endl;
}

Node * find(SensorNetwork * network, int index) {
  if (!network)
    return NULL;
  Node * ptr = network->front;
  while (ptr && ptr->next) {
    if (ptr->index == index) {
      return ptr;
    } else {
      ptr = ptr->next;
    }
  }
  cout << "Could not find node" << endl;
  return NULL;
}

void recursivenodes(SensorNetwork * network, int connections, int distance,
                    float rate) {
  numnodes++;
  if (connections == 0) {
    return;
  }
  if (connections == INITIAL_CONNECTIONS) {
    add(network, connections, distance, rate);
    distance++;
  }
  for (int i = 0; i < connections; i++) {
    int dummy = (int)(INITIAL_CONNECTIONS/(pow(2.0, distance)));
    if (dummy == 0)
      return;
    int newconnections = rand() % dummy + 0;
    add(network, newconnections, distance, rate/2);
    totalenergy += (newconnections+1)*10;
    recursivenodes(network, newconnections, distance+1, rate/2);
  }
  return;
}
