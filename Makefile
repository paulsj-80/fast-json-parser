all: prepare build-src prepare-dist 

build-src:
	cd src && $(MAKE)
	cd bindings/c++ && $(MAKE)

prepare:
	mkdir -p dist/lib
	mkdir -p dist/include

clean:
	cd src && $(MAKE) clean
	cd bindings/c++ && $(MAKE) clean

prepare-dist:
	cp src/JSON_checker.a dist/lib
	cp src/JSON_checker.h dist/include
	cp bindings/c++/jp_wrapper.a dist/lib
	cp bindings/c++/jp_wrapper.h dist/include

.PHONY: all clean prepare build-src prepare-dist


