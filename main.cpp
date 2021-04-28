// Agui Navarro
// Sensor Network
// main.cpp

#include <iostream> // cin, cout
#include <cmath>    // pow()
#include <iomanip>  // setw(), setprecision()
#include <thread>   // chrono

// global variable constants
#define INITIAL_INDEX 0
#define INITIAL_NODES -1
#define INITIAL_ENERGY 0

// change for sink node number of connections
// ** program will not work if this is 32 or higher **
#define INITIAL_CONNECTIONS 10

// namespaces
using namespace std;
using std::this_thread::sleep_for; // sleep_for in lines 78-82

// node type definition
typedef struct Node {
  struct Node * next;
  int index = 0;           // index of node
  int numconnections = 0;  // number of children the node has
  float energy = 10.0;     // maximum energy of node in joules
  int distance = 0;        // distance of node from sink node
  float rate = 0.0;        // bitrate of node, in bits
  bool power = true;       // power of node, if false, program terminates
} Node;

// sensor network type definition (queue)
typedef struct SensorNetwork {
  Node * front;
  Node * back;
} SensorNetwork;

// global variables
int totalindex = INITIAL_INDEX;
int numnodes = INITIAL_NODES;
float totalbitrate = INITIAL_ENERGY;

// function prototypes
SensorNetwork * create();
void remove(SensorNetwork * network);
void add(SensorNetwork * network, int connections, int distance, float rate);
void del(SensorNetwork * network);
void printnetwork(SensorNetwork * network);
void printnode(Node * node);
Node * find(SensorNetwork * network, int index);
void recursivenodes(SensorNetwork * network, int connections, int distance,
                    float rate);

// main
int main() {
  SensorNetwork * network = create(); // network is created with no values
  srand(time(NULL)); // random seed initialized for function recursivenodes()

  // program information
  cout << endl;
  cout << "A sensor network is in place. There are nodes within this network.\n"
       << "Each node is supplied with a certain amount of energy. Nodes transmit\n"
       << "packets at a certain rate. Each time they transmit packets, energy\n"
       << "supply decreases. There is a stopwatch to see how long the nodes can\n"
       << "stay active. If a single node fails, the stopwatch ends.\n"
       << "The program may run indefinitely. Press Ctrl+C to exit.\n" << endl;

  cout << "Press enter to begin.";
  cin.ignore();

  // functioning network is created
  recursivenodes(network, INITIAL_CONNECTIONS, 0, 1024);

  // maximum packets that can be transmitted
  // totalbitrate is updated in recursivenodes().
  // One packet is 1024 bits, so divide by 24 to get maximum packets.
  float maxpackets = (float)totalbitrate/1024;

  // Each node can have up to 10 joules within it.
  // The maximum amount of energy is all of the nodes, modified in
  // recursivenodes(), then multipled by 10 joules.
  float maxenergy = (float)numnodes*10;

  // calculations made above are outputted to console for user to see
  cout << endl;
  cout << "Number of nodes: " << numnodes << endl;
  cout << "Maximum transmission rate: " << maxpackets
       << " packets per second" << endl;
  cout << "Maximum energy: " << maxenergy << " joules" << endl;

  // grace period before test
  cout << endl << "Beginning test..." << endl;
  cout << "3... " << endl;
  sleep_for(chrono::milliseconds(1000));
  cout << "2... " << endl;
  sleep_for(chrono::milliseconds(1000));
  cout << "1... " << endl;
  sleep_for(chrono::milliseconds(1000));
  cout << endl;

  // This is shown so that the user doesn't think the program crashed
  // before output after three seconds.
  cout << "Time elapsed: 0 seconds" << endl;
  cout << "Current rate: " << maxpackets << " packets per second" << endl;
  cout << "Percentage of max rate: " << "100.00%" << endl;
  cout << "Current energy: " << maxenergy << " joules" << endl;
  cout << "Percentage of max energy: " << "100.00%" << endl;


  // Start of infinite loop section
  // clock and time definitions
  // The clock is used so that the user knows how long the program has been
  // running for, and the time the program runs before it is terminated, if
  // termination occurs.

  // Each if statment within the while loop below corresponds to a time_t type.
  // start1 is for the first if statement, start2 is for the second, and so on.
  // start3 is for the last if statement of console output.
  clock_t t, u;
  time_t start1, start2, start4, start8;
  time_t start3;
  t = clock();
  start1 = time(0);
  start2 = time(0);
  start4 = time(0);
  start8 - time(0);

  start3 = time(0);

  // The while loop will run until one of the nodes is turned off. When the
  // while loop gets notified of a power outage, it will immediately terminate
  // and inform the user. This is the only time the program will actually
  // fully run and return 0.
  bool termination = false;
  int terminationindex;
  while (!termination) {
    if (!network) {
      cout << endl << "No network." << endl;
      break;
    }

    // runs every second
    if (time(0) - start1 == 1) {
      for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
        // This only runs for the sink node.
        if (ptr->distance == 0) {
          // The bitrate of the sink node is 1024 bits/s, or 1 packet/s.
          // For the sink node, one joule is subtracted per second.
          ptr->energy -= ptr->rate/1024;
          // This runs if the node is out of energy.
          if (ptr->energy <= 0){
            ptr->power = false; // power is set to false
            terminationindex = ptr->index; // index of node is saved
            termination = true; // termination bool is set to true
            break; // break while loop
          }
        }

        // This section runs one per second, however it runs for all nodes,
        // rather than only the sink node.
        // Each node receives 0.3 joules per second.
        // It is 0.3 because a relatively high average transmittion rate
        // was achieved with this number.
        ptr->energy += 0.3;

        // The following if statements are the network telling the nodes
        // to either increase or decrease their rate based on the amount
        // of energy that is stored within them.

        // If the energy of the node is less than 3 joules, its bitrate
        // is decreased by 20 percent.
        if (ptr->energy < 3)
          ptr->rate = ptr->rate*0.8;
        // If the energy of the node is greater than 7 joules, and
        // its bitrate is not at its maximum capacity, the node's bitrate
        // is multipled by 3. The second condition is in place so that
        // the bitrate does not infinitely multiply while the node still
        // has over 7 joules near the beginning of its transmissions.
        if ((ptr->energy > 7) && (ptr->rate < 1024/(pow(2.0, ptr->distance))))
          ptr->rate = ptr->rate*3;

        // There were occurences where the maximum energy and the maximum
        // bitrate were exceeded. The following if statements are in place
        // so that the maximums are not exceeded. Overloading is a serious
        // issue and it should not be achieved.
        if (ptr->energy > 10)
          ptr->energy = ptr->energy - (ptr->energy - 10);
        if (ptr->rate > 1024/(pow(2.0, ptr->distance)))
          ptr->rate = ptr->rate - (ptr->rate - 1024/pow(2.0, ptr->distance));

      }
      // Each statement has one of these statements at its end.
      // These statements reset the time to 0, so that when the while loop
      // reiterates, the if statement will still be gone through.
      // Otherwise, the console output will be infinitely the same.
      start1 = start1+1;
    }

    // runs every two seconds
    if (time(0) - start2 == 2) {
      for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
        if (ptr->distance == 1) {
          // This is 512 because the maximum bitrate of a node with distance 1
          // is 512.
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

    // runs every four seconds
    if (time(0) - start4 == 4) {
      for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
        if (ptr->distance == 2) {
          // This is 256 because the maximum bitrate of a node with distance 2
          // is 256.
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

    // runs every eight seconds
    if (time(0) - start8 == 8) {
      for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
        if (ptr->distance == 3) {
          // This is 128 because the maximum bitrate of a node with distance 3
          // is 128.
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

    // This next section, still within the massive while loop is to calculate
    // the values for the console output that runs every 3 seconds.

    // These two values are always reinitialized.
    float currentrate = 0.0;
    float currentenergy = 0.0;

    // This for loop adds to the currentrate and currentenergy values, which
    // are used in the console output.
    for (Node * ptr = network->front; ptr && ptr->next; ptr = ptr->next) {
      currentrate += ptr->rate;
      currentenergy += ptr->energy;
    }

    // The current rate must be divided by 1024 because it is the number of
    // packets per second, not the number of bits per second.
    currentrate = (float)currentrate/1024;

    // These are the percentages, so that the user knows how well the
    // network is performing.
    float percentmaxrate = currentrate/maxpackets*100;
    float percentmaxenergy = currentenergy/maxenergy*100;

    // runs every 3 seconds
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

      // same as previous if statements to reset the counter to 0
      start3 = start3+3;
    }

  }

  // If the while loop is broken, the user must know which node was the problem.
  // The time elapsed before termination is also outputted.
  u = clock() - t;
  cout << endl;
  cout << "Node " << setw(2) << left << terminationindex
       << " was deactivated. Network terminated." << endl;
  cout << "Time elapsed: " << (int)(((u)/CLOCKS_PER_SEC)+1) << " seconds" << endl;

  // Only now is the network removed,
  remove(network);

  // and the program exits.
  return 0;
}

// create network implementation (queue)
SensorNetwork * create() {
  SensorNetwork * network = new SensorNetwork;
  network->front = NULL;
  network->back = NULL;
  return network;
}

// removing network
void remove(SensorNetwork * network) {
  if (!network)
    return;
  while (network->front) {
    del(network);
  }
  delete network;
}

// adding node to a network
void add(SensorNetwork * network, int connections, int distance, float rate) {
  Node * newnode = new Node;
  newnode->index = totalindex++;
  newnode->numconnections = connections;
  newnode->distance = distance;
  newnode->rate = rate;
  newnode->power = true;

  if (!network->front) { // if network is empty
    network->front = newnode;
    network->back = newnode;
    network->back->next = NULL;
  } else { // if network is not empty
    network->back->next = newnode;
    network->back = newnode;
    network->back->next = NULL;
  }
}

// deleting nodes
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

// printing the network, used for debugging
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

// printing node, used for debugging
void printnode(Node * node) {
  cout << "Index: " << setw(3) << left << node->index;
  cout << " Connections: " << setw(2) << left << node->numconnections;
  cout << " Energy: " << setw(3) << left << node->energy;
  cout << " Distance: " << setw(2) << left << node->distance;
  cout << " Rate: " << setw(5) << left << node->rate << endl;
}

// finding node, also used for debugging
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

// recursive function for adding nodes to the network
void recursivenodes(SensorNetwork * network, int connections, int distance,
                    float rate) {
  // Each time the function is recursively called, the number of nodes
  // is increased, no matter what, starting from its original global value.
  numnodes++;

  // The total bitrate is also increased from its initial global value.
  totalbitrate += rate;

  // base condition
  if (connections == 0)
    return;

  // only runs for sink node
  if (connections == INITIAL_CONNECTIONS) {
    add(network, connections, distance, rate);
    distance++;
  }

  // runs for all other nodes
  for (int i = 0; i < connections; i++) {
    // Based on the distance from the sink node, a temporary value is created
    // to be the upper limit of the random number generator.
    int dummy = (int)(INITIAL_CONNECTIONS/(pow(2.0, distance)));
    // Floating point exceptions were in place before the insertion of this
    // if statement.
    if (dummy == 0)
      return;
    // The new amount of connections is a number between 0 and the temporary
    // dummy variable above.
    int newconnections = rand() % dummy + 0;
    // Based on the distance and the new number of connections, a new node
    // is created.
    add(network, newconnections, distance, rate/2);

    // recursive call to make children
    recursivenodes(network, newconnections, distance+1, (float)rate/2);
  }
  return;
}
