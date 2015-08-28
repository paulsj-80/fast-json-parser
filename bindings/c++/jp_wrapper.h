#ifndef JP_WRAPPER_H
#define JP_WRAPPER_H

extern "C" {
#include "JSON_checker.h"
}

namespace jpw {

    class Listener {
    public:
        virtual ~Listener();
        virtual void handleKey(char* str, unsigned int len) = 0;
        virtual void handleValue(char* str, unsigned int len) = 0;
        virtual void handleObjStart() = 0;
        virtual void handleObjEnd() = 0;
        virtual void handleArrStart() = 0;
        virtual void handleArrEnd() = 0;
    };

    class Parser {
    private:
        Listener& listener;        
        JSON_checker_struct jc;
        char* currBuff;

        static int tokenHandler(void* ctx, int type, int pos, int size);
    public:
        Parser(Listener& listener, unsigned int stackLen);
        Parser(Parser const& other);
        Parser& operator=(const Parser& other);
        virtual ~Parser();

        // allows to reuse instance for multiple JSON "files"
        void reset();

        /*
          Side, which passes buffer, should take care of not freeing
          it prematurely; associated Listener may (and, most likely,
          will) get data which references it; this is until
          feeding_done() is called.
         */
        void feed(char* buff, unsigned int len);
        void feeding_done();
    };

}

#endif
