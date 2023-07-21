void Error(string s);

class JSONObject {
    
};

class JSONString: public JSONObject, string {
public:
    string str;
    
    JSONString(string s): str(move(s)) {}
    JSONString(string_view s): str(string(s)) {}
};

class JSONNumber: public JSONObject {
public:
    long val;
    
    JSONNumber(long v): val(v) {}
};

class JSONBoolean: public JSONObject {
public:
    bool val;
    
    JSONBoolean(bool v): val(v) {}
};

class JSONDict: public JSONObject {
public:
    unordered_map<string, JSONObject> objDict;
    
    JSONDict() {}
    
    JSONDict(unordered_map<string, JSONObject> od): objDict(move(od)) {}
    
    void add(string s, JSONObject obj) {
        if(objDict.count(s)) Error("duplicate dict name: " + s);
        objDict.emplace(move(s), move(obj));
    }
};

class JSONList: public JSONObject {
public:
    vector<JSONObject> objList;
    
    JSONList() {}
    
    JSONList(vector<JSONObject> ol): objList(move(ol)) {}
    
    void add(JSONObject obj) {
        objList.emplace_back(move(obj));
    }
};