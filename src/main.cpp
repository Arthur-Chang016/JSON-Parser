#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "def.hpp"

int main(int args, char **argv) {
    hi();
    
    // check args
    if(args < 2) {
        cerr << "No input file" << endl;
        return 1;
    }
    // string inputFile = 
    
    cout << "hi" << endl;
    
    return 0;
}