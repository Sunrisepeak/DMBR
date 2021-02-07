#ifndef _TABLE_HPP
#define _TABLE_HPP

#include <iostream>

class SimpleTable {

    friend std::ostream &
    operator<<(std::ostream &, const SimpleTable &);

public:

    struct Pos {
        unsigned int row, col;
        Pos(int r, int c) : row { r }, col { c } {}
    };
    
    SimpleTable(unsigned int r = 0, unsigned int c = 0) : tableSize(r, c), len{ 4 } {

    }
    
private:


private:
    Pos tableSize;
    unsigned int len;
};

std::ostream &
operator<<(std::ostream &os, const SimpleTable &st) {

}

#endif