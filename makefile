debug:
	g++ -o bin/dbug src/*.cpp -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

linux:
	g++ -o bin/gremlinMassacre src/*.cpp -O1 -w -Wno-missing-braces -I include/ -L lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
