CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CPPFLAGS = -I ./include -D -MP

SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp,./bin/%.o, $(SRCS))

# default target
all: ./bin/studio

# build studio
./bin/studio: $(OBJS)
	@echo "Building ..."
	$(CXX) $(OBJS) -o $@
	@echo "Finished building"

# build cpp files
./bin/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# clean build files
clean:
	@echo 'cleaning...'
	@rm -f ./bin/*
