OBJS = jp_wrapper.o
DEPS = jp_wrapper.h
OUTLIB = jp_wrapper.a
INCLUDE = ../../src

all: $(OUTLIB)

clean:
	rm -rf $(OBJS) $(OUTLIB)

$(OUTLIB): $(OBJS)
	ar rcs $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) -g -c -I$(INCLUDE) $< -o $@

.PHONY: all clean
