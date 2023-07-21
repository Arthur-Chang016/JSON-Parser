#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <algorithm>
#include <unordered_map>
using namespace std;

#include "def.hpp"
#include "Util.hpp"

void Error(string s);

JSONObject MetaObject(string_view s, int start, int end, const vector<int> &nextClose) {
    if(s[start] != '[' && s[start] != '{') Error("MetaObject not start with [ { : " + to_string(start) + s[start]);
    
    
    
    return JSONObject();
}

JSONObject JSONParse(string_view s, int start, int end, const vector<int> &nextClose) {
    return MetaObject(s, start, end, nextClose);
}


int main(int args, char **argv) {
    // check args
    if(args < 2) {
        cerr << "No input file" << endl;
        return 1;
    }
    // file input and trim
    string file = ReadFile(argv[1]);
    TrimFile(file);
    
    if(file.empty()) {
        cerr << "Empty File" << endl;
        return 1;
    }
    
    cout << file << endl;
    // cout << file.substr(310, 10) << endl;
    
    // build corresponding char map
    vector<int> next = BuildNextClosure(file);
    if(next.empty()) {
        cerr << "Parse Error" << endl;
        return 1;
    }
    
    JSONObject json = JSONParse(file, 0, file.size(), next);
    
    // JSONList o;
    // JSONList b;
    // o.add(b);
    
    // for(int i = 0; i < (int)next.size(); ++i) {
    //     if(next[i] == -1) continue;
    //     int ne = next[i];
    //     cout << i << ' ' << file[i] << ", " << ne << ' ' << file[ne] << endl;
    // }
    
    
    
    
    return 0;
}
