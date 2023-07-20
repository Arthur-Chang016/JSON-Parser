#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

#include "def.hpp"
#include "Util.hpp"

int main(int args, char **argv) {
    // check args
    if(args < 2) {
        cerr << "No input file" << endl;
        return 1;
    }
    
    // build corresponding char map
    
    vector<int> next;
    
    string file = ReadFile(argv[1]);
    
    TrimFile(file);
    
    cout << file << endl;
    
    
    // string inputFile = 
    
    // string_view sv;
    
    // cout << "hi" << endl;
    
    return 0;
}
