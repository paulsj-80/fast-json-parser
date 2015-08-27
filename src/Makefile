CC = gcc
OBJS = JSON_checker.o
DEPS = JSON_checker.h
OUTLIB = libJSON_checker.a

all: $(OUTLIB)

clean:
	rm -rf $(OBJS) $(OUTLIB)

$(OUTLIB): $(OBJS)
	ar rcs $@ $^

%.o: %.c $(DEPS)
	$(CC) -g -c $< -o $@

.PHONY: all clean


