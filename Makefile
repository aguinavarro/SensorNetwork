# Sensor Network
# Agui Navarro
# makefile

default: test

all: numbernodes.cpp main.cpp
	g++ -o numbernodes numbernodes.cpp
	g++ -o sensornetwork main.cpp

numbernodes: numbernodes.cpp
	g++ -o numbernodes numbernodes.cpp

sensornetwork: main.cpp
	g++ -o sensornetwork main.cpp

clean:
	rm -f main numbernodes sensornetwork out.txt

test: sensornetwork
	./sensornetwork
