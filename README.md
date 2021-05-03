# SensorNetwork

This project is a sensor network simulation with a focus on energy conservation.
There is a sensor network with multiple nodes. Each node has a certain amount of 
energy given to it every second, and each node uses a certain amoount of energy 
each second. There is a sink node where all transmission occurs. The sink node
transmits packets the fastest, while nodes attached to it transmit packets at half
its rate, nodes connected to these nodes transmit packets a quarter the rate of the
sink node, and so on and so forth. The goal of this proam is to transmit packets
at the highest capacity while keeping the network active in the process. The entire
network fails if one single node loses all its energy and its power shuts off.

An infinite while loop is in place, and every three seconds, terminal output is posted.
The output consists of the current packet transmission rate, its percentage of the
theoretical maximum rate, the current energy in the network, and the percentage of
energy compared to the maximum theoretical energy. While running the program, one
can notice the changes in rate and energy, flucuating nearly every output. One can
also compare this output to a download of a video game or large file, where the
download speed fluctuates frequently, as well. Similarly to how a download speed may
stay low for a few seconds, the transmission rate for this program may stay low for
a few outputs, then finally raising back up to a higher amount.

Techniques used in this project are structures, the queue data type, and recursion.
The language used is C++, compiled in C++20. One can run the program by simply typing
"make". This project was a solo project. The algorithm can be seen in the file "main.cpp"
and extensive explanation comments are provided.
