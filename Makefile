all: bin/read_data

bin/read_data: src/read_data.cpp
	g++ src/read_data.cpp -o bin/read_data

clean:
	rm -f bin/*
