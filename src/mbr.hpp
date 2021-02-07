#ifndef _MBR_HPP_
#define _MBR_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "dpt.hpp"

#define MBR_SIZE 512
#define PARTITION_BASE 446

using std::cout;
using std::endl;

class MBR {
    friend std::ostream & 
    printRow(std::ostream &, const MBR &, size_t, size_t);

    friend std::ostream & 
    printData(std::ostream &, const MBR &, size_t, size_t, size_t);

    friend std::ostream &
    operator<<(std::ostream &, const MBR &);

public:

    struct MData {
        uint8_t code[440];                 // Code area
        uint32_t diskSign;                 // Disk signature (optional)
        uint16_t nulls;                    // Usually nulls; 0x0000
        DPT pTable[4];                     // Partition table
        uint16_t mbrSign;                  // MBR signature
    } __attribute__((packed));

    MBR() = default;

    MBR(std::ifstream &infs) {
        infs.read((char *)(&data), sizeof(data));
    }

    std::string 
    getPartionsHexInfo(int index) const {
        std::stringstream ss;
        printRow(ss, *this, PARTITION_BASE + index * 16, 16) << endl;
        return ss.str();
    }

    std::string 
    getPartionsInfo(int index) const {
        std::stringstream ss;
        printRow(ss, *this, PARTITION_BASE + index * 16, 16) << endl;
        return ss.str();
    }

private:

    void printTableHead() {

    }

private:
    MData data;
};

std::ostream & 
printRow(std::ostream &os, const MBR &mbr, size_t pos = 0, size_t len = 16) {
    if (len == 0) return os;
    
    auto tData = (uint8_t *)(&(mbr.data));

    os << std::hex << std::setfill('0');                // set format
    os << std::setw(8) << pos << ":";
    size_t j = 0;
    for (; j < len / 2; j++) {
        os << " " 
        << std::setw(2) << static_cast<uint16_t>(tData[pos + j * 2]) 
        << std::setw(2) << static_cast<uint16_t>(tData[pos + j * 2 + 1]);
    }
    if (len % 2) os << std::setw(2) << static_cast<uint16_t>(tData[pos + j * 2]);
    os << std::setfill(' ') << std::dec;                // restore format

    return os;    
}

std::ostream & 
printData(std::ostream &os, const MBR &mbr, size_t pos = 0, size_t len = 512, size_t colNums = 16) {
    if (len > 512 || len <= 0) 
        throw std::invalid_argument("Length error");
    
    size_t row = len / colNums, endRow = len % colNums;
    for (size_t i = 0; i < row; i++) {
        printRow(os, mbr, i * colNums, colNums) << endl;
    }
    printRow(os, mbr, row * colNums, endRow);

    return os;
}

std::ostream &
operator<<(std::ostream &os, const MBR &mbr) {
    printData(os, mbr);
    return os;
}

#endif

