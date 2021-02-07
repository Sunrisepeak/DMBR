#ifndef _DPT_HPP
#define _DPT_HPP

#include <iostream>

struct DPT {
        uint8_t pStatus;        // Partitions status(boot)

        uint8_t bHead;          // Begin
        uint8_t bSector : 6;    // Sector 0-5bit 
        uint8_t bCylHight : 2;    // Bits 9–8 of cylinder are in bits 7–6 
        uint8_t bCylLow;       // Bits 7–0 of cylinder
        
        uint8_t pType;          // Partitions Type
        
        uint8_t eHead;          // End
        uint8_t eSector : 6;    // Sector 0-5bit 
        uint8_t eCylLow : 2;    // Bits 9–8 of cylinder are in bits 7–6 
        uint8_t eCylHigh;       // Bits 7–0 of cylinder
        
        uint32_t usedSector;    
        uint32_t allSector;

        bool isActive() {
            return pStatus == 0x80;
        }

        size_t getStartSector() {
            return 0;
        }

} __attribute__((packed));

#endif