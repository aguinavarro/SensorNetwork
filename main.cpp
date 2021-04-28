// Agui Navarro
// Sensor Network
// main.cpp

#include <iostream>

#define INITIAL_INDEX 0
#define INITIAL_NODES -1
#define INITIAL_ENERGY 0

#define INITIAL_CONNECTIONS 10

using namespace std;
using std::this_thread::sleep_for;

typedef struct Node {
  struct Node * next;
  int index = 0;
  int numconnections = 0;
  float energy = 10.0;
  int distance = 0;
  float rate = 0.0;
  bool power = true;
} Node;

typedef struct SensorNetwork {
  Node * front;
  Node * back;
} SensorNetwork;

int totalindex = INITIAL_INDEX;
int numnodes = INITIAL_NODES;
float totalbitrate = INITIAL_ENERGY;

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

  cout << endl;
  cout << "A sensor network is in place. There are nodes within this network.\n"
       << "Each node is supplied with a certain amount of energy. Nodes transmit\n"
       << "packets at a certain rate. Each time they transmit packets, energy\n"
       << "supply decreases. There is a stopwatch to see how long the nodes can\n"
       << "stay active. If a single node fails, the stopwatch ends.\n" << endl;

  cout << "Press enter to begin.";
  cin.ignore();

  recursivenodes(network, INITIAL_CONNECTIONS, 0, 1024);

  float maxpackets = (float)totalbitrate/1024;
  float maxenergy = (float)numnodes*10;
  cout << endl;
  cout << "Number of nodes: " << numnodes << endl;
  cout << "Maximum transmission rate: " << maxpackets
       << " packets per second" << endl;
  cout << "Maximum energy: " << maxenergy << " joules" << endl;

  cout << endl << "Beginning test..." << endl;
  cout << "3... " << endl;
  sleep_for(chrono::milliseconds(1000));
  cout << "2... " << endl;
  sleep_for(chrono::milliseconds(1000));
  cout << "1... " << endl;
  sleep_for(chrono::milliseconds(1000));
  cout << endl;

  cout << "Time elapsed: 0 seconds" << endl;
  cout << "Current rate: " << maxpackets << " packets per second" << endl;
  cout << "Percentage of max rate: " << "100.00%" << endl;
  cout << "Current energy: " << maxenergy << " joules" << endl;
  cout << "Percentage of max energy: " << "100.00%" << endl;

  clock_t t, u;
  time_t start1, start2, start4, start8;
  time_t start3;
  t = clock();
  start1 = time(0);
  start2 = time(0);
  start4 = time(0);
  start8 - time(0);

  start3 = time(0);

  bool termination = false;
  int terminationindex;
  while (!termination) {
    if (!network) {
      cout << endl << "No network." << endl;
      break;
    }

    if (time(0) - start1 == 1) {
      for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
        if (ptr->distance == 0) {
          ptr->energy -= ptr->rate/1024;
          if (ptr->energy <= 0){
            ptr->power = false;
            terminationindex = ptr->index;
            termination = true;
            break;
          }
        }

        ptr->energy += 0.3;
        if (ptr->energy < 3)
          ptr->rate = ptr->rate*0.8;
        if ((ptr->energy > 7) && (ptr->rate < 1024/(pow(2.0, ptr->distance))))
          ptr->rate = ptr->rate*3;

        if (ptr->energy > 10)
          ptr->energy = ptr->energy - (ptr->energy - 10);
        if (ptr->rate > 1024/(pow(2.0, ptr->distance)))
          ptr->rate = ptr->rate - (ptr->rate - 1024/pow(2.0, ptr->distance));

      }
      start1 = start1+1;
    }

    if (time(0) - start2 == 2) {
      for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
        if (ptr->distance == 1) {
          ptr->energy -= ptr->rate/512;
          if (ptr->energy <= 0){
            ptr->power = false;
            terminationindex = ptr->index;
            termination = true;
            break;
          }
        }
      }
      start2 = start2+2;
    }

    if (time(0) - start4 == 4) {
      for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
        if (ptr->distance == 2) {
          ptr->energy -= ptr->rate/256;
          if (ptr->energy <= 0){
            ptr->power = false;
            terminationindex = ptr->index;
            termination = true;
            break;
          }
        }
      }
      start4 = start4+4;
    }

    if (time(0) - start8 == 8) {
      for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
        if (ptr->distance == 3) {
          ptr->energy -= ptr->rate/128;
          if (ptr->energy <= 0){
            ptr->power = false;
            terminationindex = ptr->index;
            termination = true;
            break;
          }
        }
      }
      start8 = start8+8;
    }

    float currentrate = 0.0;
    float currentenergy = 0.0;
    for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
      currentrate += ptr->rate;
      currentenergy += ptr->energy;
    }

    currentrate = (float)currentrate/1024;
    float percentmaxrate = currentrate/maxpackets*100;
    float percentmaxenergy = currentenergy/maxenergy*100;
    if (time(0) - start3 == 3) {
      u = clock() - t;
      cout << endl;
      cout << "Time elapsed: " << (int)(((u)/CLOCKS_PER_SEC)+1)
           << " seconds" << endl;
      cout << "Current rate: " << currentrate << " packets per second" << endl;
      cout << "Percentage of max rate: " << setprecision(2) << fixed
           << percentmaxrate << "%" << endl;
      cout << "Current energy: " << currentenergy << " joules" << endl;
      cout << "Percentage of max energy: " << setprecision(2) << fixed
           << percentmaxenergy << "%" << endl;
      start3 = start3+3;
    }

  }

  u = clock() - t;
  cout << endl;
  cout << "Node " << setw(2) << left << terminationindex
       << " was deactivated. Network terminated." << endl;
  cout << "Time elapsed: " << (int)(((u)/CLOCKS_PER_SEC)+1) << " seconds" << endl;

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
    cout << endl << "No network to print." << endl;
    return;
  } else {
    cout << endl << "Printing network..." << endl;

    for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
      cout << "Index: " << setw(5) << left << ptr->index;
      cout << " Connections: " << setw(5) << left << ptr->numconnections;
      cout << " Energy: " << setw(5) << left << ptr->energy;
      cout << " Distance: " << setw(5) << left << ptr->distance;
      cout << " Rate: " << setw(5) << left << ptr->rate << endl;
    }
  }
  return;
}

void printnode(Node * node) {
  cout << "Index: " << setw(3) << left << node->index;
  cout << " Connections: " << setw(2) << left << node->numconnections;
  cout << " Energy: " << setw(3) << left << node->energy;
  cout << " Distance: " << setw(2) << left << node->distance;
  cout << " Rate: " << setw(5) << left << node->rate << endl;
}

Node * find(SensorNetwork * network, int index) {
  if (!network)
    return NULL;

  for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
    if (ptr->index == index)
      return ptr;
  }
  cout << "Could not find node" << endl;
  return NULL;
}

void recursivenodes(SensorNetwork * network, int connections, int distance,
                    float rate) {
  numnodes++;
  totalbitrate += rate;
  if (connections == 0)
    return;
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
    recursivenodes(network, newconnections, distance+1, (float)rate/2);
  }
  return;
}
