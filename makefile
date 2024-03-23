debug:
	g++ -o bin/dbug src/*.cpp -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lm -lpthread -ldl -lrt

linux:
	g++ -o bin/gremlinMassacre src/*.cpp -O1 -w -Wno-missing-braces -I include/ -L lib/ -lraylib -lm -lpthread -ldl -lrt
