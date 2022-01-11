CC = g++
CXXFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
ll: src/ll.cpp  ; $(CC) $(CXXFLAGS) -o ll src/ll.cpp src/Lander.cpp src/olcPixelGameEngine.cpp

clean:  ; -rm $(objects) ll error.txt

debug:  ; $(CC) $(CXXFLAGS) -o ll -g src/ll.cpp src/Lander.cpp src/olcPixelGameEngine.cpp

log:  ; $(CC) $(CXXFLAGS) 2> error.txt -o ll src/ll.cpp src/Lander.cpp src/olcPixelGameEngine.cpp
