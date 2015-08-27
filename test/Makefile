INCLUDE = ../dist/include
LIB_DIR = ../dist/lib
LIBS = -ljp_wrapper -lJSON_checker 
OBJS = test.o
TESTBIN = test
DEPS = $(INCLUDE)/JSON_checker.h $(INCLUDE)/jp_wrapper.h $(LIB_DIR)/libJSON_checker.a $(LIB_DIR)/libjp_wrapper.a


all: test-report.txt

clean:
	rm -f $(TESTBIN) $(OBJS)

test-report.txt: $(TESTBIN)
	./$^ 2>&1 | tee test-report.txt

$(TESTBIN): $(OBJS) 
	$(CXX) -Wall -g -L$(LIB_DIR) -o $@ $^ $(LIBS) 

%.o: %.cpp $(DEPS)
	$(CXX) -g -c -I$(INCLUDE) $< -o $@

$(DEPS):
	$(error Missing one of the following: $(DEPS))

.PHONY: all clean






