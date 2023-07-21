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

JSONObject DataOjbect(const string_view s, const int start, const int end, const vector<int> &nextClose);
JSONObject MetaObject(const string_view s, const int start, const int end, const vector<int> &nextClose);

pair<string, JSONObject> DictObject(const string_view s, const int start, const int end, const vector<int> &nextClose) {
    return {"", JSONObject()};
}

JSONObject MetaObject(const string_view s, const int start, const int end, const vector<int> &nextClose) {
    if(s[start] != '[' && s[start] != '{') Error("MetaObject not start with [ { : " + to_string(start) + s[start]);
    if(s[start] == '[') {
        // create list
        JSONList ret;
        // split by,
        int last = start;
        for(int i = start; i <= end; ++i) {
            if(i == end || s[i] == ',') {
                JSONObject obj = DataOjbect(s, last, i, nextClose);
                ret.add(obj);
                // update
                last = i + 1;
            }
        }
        return ret;
    } else {  // s[start] == '{'
        // create dict
        JSONDict ret;
        // split by,
        int last = start;
        for(int i = start; i <= end; ++i) {
            if(i == end || s[i] == ',') {
                auto [str, obj] = DictObject(s, last, i, nextClose);
                ret.add(str, obj);
                // update
                last = i + 1;
            }
        }
        return ret;
    }
}

/**
 * objects can be in list or value of dict
*/
JSONObject DataOjbect(const string_view s, const int start, const int end, const vector<int> &nextClose) {
    int len = end - start;
    if(len <= 0) Error("length error: " + to_string(len));
    char fir = s[start], last = s[end];
    if((len == 5 && s.substr(start, len) == "false") || (len == 4 && s.substr(start, len) == "true")) {
        return len == 5 ? JSONBoolean(false) : JSONBoolean(true);
    } else if(fir == '\"' && last == '\"') {  // string
        return JSONString(s.substr(start + 1, len - 2));
    } else if(fir == '[' || fir == '{') {
        return MetaObject(s, start, end, nextClose);
    }
    
    
    return JSONObject();
}

JSONObject JSONParse(const string_view s, const int start, const int end, const vector<int> &nextClose) {
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
