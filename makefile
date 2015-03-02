SRC = utf8.cc
HDR = utf8.h
TEST = test.cc

OBJ := $(SRC:.cc=.o)
LIB = libutf8.o

LIBS= utf8/libutf8.o
CXXFLAGS+=-g

.PHONY: all clean test

all: $(LIB)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $?

$(LIBS):
	$(foreach var,$@, $(MAKE) $(MAKEFLAGS) -C $(dir $(var));)

$(LIB): $(OBJ) $(LIBS)
	$(LD) -o $@ -r $^

clean:
	$(RM) $(LIB) $(OBJ) $(TEST:.cc=.o)
	$(foreach var,$(LIBS), $(MAKE) $(MAKEFLAGS) -C $(dir $(var)) clean;)

# run tests
test: $(LIB)
	$(CXX) $(CXXFLAGS) -o "test.o" -c $(TEST)
	$(CXX) $(CXXFLAGS) -o "test" "test.o" $^
	./test
