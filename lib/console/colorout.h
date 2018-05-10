#ifndef COLOROUT_H_
#define COLOROUT_H_

#include <stdio.h>

using namespace std;

namespace Formatter{
    enum Color{
        GREEN   = 32,
        BLUE    = 34,
        BLACK   = 30,
        WHITE   = 37,
        RED     = 31,
        MAGENTA = 35,
        CYAN    = 36,
        BRIGHT_GREEN   = 92,
        BRIGHT_BLUE    = 94,
        BRIGHT_BLACK   = 90,
        BRIGHT_WHITE   = 97,
        BRIGHT_RED     = 91,
        BRIGHT_MAGNETA = 95,
        BRIGHT_CYAN    = 96
    };
    enum Style{
        DEFAULT             = 0, 
        BOLD_BRIGHT         = 1, 
        UNDERLINE           = 4,
        INVERSE             = 7,
        BOLD_BRIGHT_OFF     = 21,
        UNDERLINE_OFF       = 24,
        INVERSE_OFF         = 27
    };

    inline void cout(string data, Color fgColor, Color bgColor, Style fontStyle){
        std::cout << "\033[" << fontStyle << ";" << bgColor + 10 << ";" << fgColor << "m" << data << "\033[0m";
    }

    inline void cout(string data, Color fgColor, Style fontStyle){
        std::cout << "\033[" << fontStyle << ";" << fgColor << "m" << data << "\033[0m";
    }

    inline void cout(string data, Color fgColor){
        std::cout << "\033["  << fgColor << "m" << data << "\033[0m";
    }

    inline void endl(){
        std::cout << std::endl;
    }
}

#endif