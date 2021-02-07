#include <iostream>
#include <string>
#include <vector>

#include "mbr.hpp"

std::vector<std::string> cmd;

int main(int args, char **argv) {
    
    if (args <= 1) {
        cout << "args error" << endl;
    }
    for (int i = 1; i < args; i++) {
        cmd.push_back(argv[i]);
    }
    std::ifstream fs(cmd[0], std::fstream::binary);
    if (fs.is_open()) {
        auto m = MBR(fs);
        cout << m << endl << endl << m.getPartionsInfo(0) << endl;       
    } else {
        cout << "ERROR: " << cmd[0] << endl;
    }
    fs.close();
    return 0;
}