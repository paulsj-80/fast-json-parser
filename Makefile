all: prepare build-src prepare-dist 

test: all
	cd test && $(MAKE)


build-src:
	cd src && $(MAKE)
	cd bindings/c++ && $(MAKE)

prepare:
	mkdir -p dist/lib
	mkdir -p dist/include

clean:
	cd src && $(MAKE) clean
	cd bindings/c++ && $(MAKE) clean
	rm -rf dist

prepare-dist:
	cp src/libJSON_checker.a dist/lib
	cp src/JSON_checker.h dist/include
	cp bindings/c++/libjp_wrapper.a dist/lib
	cp bindings/c++/jp_wrapper.h dist/include

.PHONY: all clean prepare build-src prepare-dist test


