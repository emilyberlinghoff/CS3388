CXX = g++
CXXFLAGS = -std=c++11 -g

# Homebrew path on Apple Silicon (adjust if needed)
INCLUDES = -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lglfw -lGLEW -framework OpenGL

# Source files
SRCS = A6-Water.cpp LoadShaders.cpp textureLoader.cpp TextureMesh.cpp
OBJS = $(SRCS:.cpp=.o)

# Output executable
EXEC = water

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDES) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

clean:
	rm -f *.o $(EXEC)
