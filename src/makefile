CXX = g++
RM = rm -f
ECHO = echo

CXXFLAGS = -Wall -Werror -ggdb
LDFLAGS = -lncurses

SRCS = main.cpp io.cpp perlin.cpp
OBJS = main.o io.o perlin.o
EXEC = poke_ascii

all: $(EXEC)

# Rule to compile source files into object files
%.o: %.cpp
	$(ECHO) Compiling
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	@$(ECHO) Removing all generated files
	@$(RM) $(OBJS) $(EXEC)