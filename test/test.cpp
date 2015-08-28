#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include "jp_wrapper.h"

using namespace std;


class WrapperListener : public jpw::Listener {
private:
    ostream& out;
public:
    WrapperListener(ostream& out) : out(out) {
    }
    virtual ~WrapperListener() {
    }
    virtual void handleKey(char* str, unsigned int len) {
        out << ";K";
        for (int i = 0; i < len; i++)
            out << str[i];
        out << ":";
    }
    virtual void handleValue(char* str, unsigned int len) {
        out << ";V";
        for (int i = 0; i < len; i++)
            out << str[i];
    }
    virtual void handleObjStart() {
        out << "{";
    }
    virtual void handleObjEnd() {
        out << "}";
    }
    virtual void handleArrStart() {
        out << "[";
    }
    virtual void handleArrEnd() {
        out << "]";
    }
};

/*
  simply trying if a small JSON file is parsed correctly
 */
void test_jp_wrapper() {
    ifstream s1;
    s1.open("samples/sample1.json");
    char data[1024];
    s1.read(data, 1024);
    unsigned int bytesRead = s1.gcount();
    s1.close();

    stringstream ss;
    WrapperListener wl(ss);

    jpw::Parser p(&wl, 10);
    p.feed(data, bytesRead);
    p.feeding_done();

    std::ifstream r1("samples/sample1.result");
    std::stringstream buff;
    buff << r1.rdbuf();

    assert(buff.str().compare(ss.str()) == 0);
}

int main(int argc, char* argv[]) {
    cerr << "********************************" << endl;
    cerr << "Starting tests" << endl;

    test_jp_wrapper();

    cerr << "Tests finished succesfuly" << endl;
}
