# Choose your compiler (depending on your environment clang/gcc)
CC=gcc

# Add flags to the compilation
CC_FLAGS=-Wpedantic -Wall -g

# These variables hold the name of all source files/headers/object files
# SRCS=$(wildcard src/*.c)
SRCS=$(wildcard src/vm.c)
HEADERS=$(wildcard src/*.h)
OBJECTS=$(patsubst src/%.c,bin/%.o,$(SRCS))

# To display one of the above variable, uncomment the next line
$(info SRCS    is $(SRCS))
$(info HEADERS is $(HEADERS))
$(info OBJECTS is $(OBJECTS))

# This rule produces the executable by compiling and linking all objects
# $< are the names of all prerequisites (the object files)
# $@ is the name of the target (bin/womc in this case)
bin/vm: $(OBJECTS)
	$(CC) $^ $(CC_FLAGS) -o $@ 
# must start with TAB character

# This rule produces all object files
# -c option tells gcc to only compile one source file at a tile
#  $< is the name of the first prerequisite (the c file in this case)
bin/%.o: src/%.c $(HEADERS)
	$(CC) $< $(CC_FLAGS) -c -o $@ 
# must start with TAB character


.PHONY: clean

clean:
	rm -f $(OBJECTS) womc

documentation:
	doxygen src/doxygen_config_assembleur
	doxygen src/doxygen_config_vm