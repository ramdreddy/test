# Makefile for Team Roster Manager

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = roster_manager

SRCS = main.cpp Player.cpp Roster.cpp InputValidator.cpp FileHandler.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = Player.h Roster.h InputValidator.h FileHandler.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
