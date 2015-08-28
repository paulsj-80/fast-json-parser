#include <stdexcept>
#include <sstream>
#include <cstring>
#include "jp_wrapper.h"

namespace jpw {

    Listener::~Listener() {
    }

    Parser::Parser(Listener* listener, unsigned int stackLen)
        : listener(listener) {
        jc.stack = new int[stackLen];
        jc.depth = stackLen;
        reset_JSON_checker(&jc, Parser::tokenHandler,
                           (void*)this, 0);
    }

    Parser::Parser(Parser const& other) : listener(other.listener) {
        currBuff = other.currBuff;
        
        jc = other.jc;
        jc.stack = new int[jc.depth];
        memcpy(jc.stack, other.jc.stack, sizeof(int) * jc.depth);
    }

    Parser& Parser::operator=(const Parser& other) {
        listener = other.listener;
        currBuff = other.currBuff;
        
        delete [] jc.stack;
        jc = other.jc;
        jc.stack = new int[jc.depth];
        memcpy(jc.stack, other.jc.stack, sizeof(int) * jc.depth);
    }


    Parser::~Parser() {
        delete [] jc.stack;
    }

    void Parser::setListener(Listener* listener) {
        this->listener = listener;
    }


    void Parser::feed(char* buff, unsigned int len) {
        currBuff = buff;
        for (int i = 0; i < len; i++)
            if (!JSON_checker_char(&jc, (int)buff[i])) {
                std::ostringstream stringStream;
                stringStream << "Bad character at " << jc.curr_pos;
                throw std::runtime_error(stringStream.str());
            }
    }

    void Parser::feeding_done() {
        if (!JSON_checker_done(&jc)) {
            std::ostringstream stringStream;
            stringStream << "Stream cannot end here, at " <<
                jc.curr_pos;
            throw std::runtime_error(stringStream.str());
        }
    }

    void Parser::reset() {
        reset_JSON_checker(&jc, Parser::tokenHandler,
                           (void*)this, 0);
    }


    int Parser::tokenHandler(void* ctx, int type, int pos,
                             int size) {
        Parser* instance = (Parser*)ctx;

        switch (type) {
        case JSON_TOKEN_KEY:
            instance->listener->handleKey(instance->currBuff + pos,
                                         size);
            break;
        case JSON_TOKEN_VALUE:
            instance->listener->handleValue(instance->currBuff + pos,
                                           size);
            break;
        case JSON_TOKEN_OBJ_START:
            instance->listener->handleObjStart();
            break;
        case JSON_TOKEN_OBJ_END:
            instance->listener->handleObjEnd();
            break;
        case JSON_TOKEN_ARR_START:
            instance->listener->handleArrStart();
            break;
        case JSON_TOKEN_ARR_END:
            instance->listener->handleArrEnd();
            break;
        }
        return 0;
    }
    
}
