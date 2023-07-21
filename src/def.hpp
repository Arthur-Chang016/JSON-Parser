
class JSONObject {
    
};

class JSONString: public JSONObject, string {
    
};

class JSONNumber: public JSONObject {
public:
    long val;
    
    JSONNumber(long v): val(v) {}
};

class JSONDict: public JSONObject {
public:
    unordered_map<string, JSONObject> objDict;
    
    // JSONDict(string s, JSONObject obj) {
    //     objDict.emplace(move(s), move(obj));
    // }
    
    void add(string s, JSONObject obj) {
        objDict.emplace(move(s), move(obj));
    }
};

class JSONList: public JSONObject {
public:
    vector<JSONObject> objList;
    
    // JSONList(JSONObject obj) {
    //     objList.emplace_back(move(obj));
    // }
    
    void add(JSONObject obj) {
        objList.emplace_back(move(obj));
    }
};