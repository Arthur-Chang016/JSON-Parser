
string ReadFile(const char *fileName) {
    std::ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file." << std::endl;
        exit(1);
    }
    file.seekg(0, std::ios::end);
    streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    string fileContents;
    fileContents.resize(fileSize);

    file.read(&fileContents[0], fileSize);
    file.close();
    return fileContents;
}

void TrimFile(string &s) {
    s.erase(remove_if(begin(s), end(s), [](char c) {
        return c == ' ' || c == '\t' || c == '\n';
    }), end(s));
}

void Error(string s) {
    cout << "Parse error: " << s << endl;
    exit(1);
}

vector<int> BuildNextClosure(const string &s) {
    vector<int> ret(s.size(), -1);
    vector<pair<int, char>> st;
    
    auto correspond = [](char a, char b)->bool {
        return (a == '\"' && b == '\"') || (a == '[' && b == ']') || (a == '{' && b == '}');
    };
    
    for(int i = 0; i < (int)ret.size(); ++i) {
        char cur = s[i];
        if(cur == '\"') {
            if(st.empty() || st.back().second != '\"') st.emplace_back(i, cur);
            else {
                auto [prev, c] = st.back();  st.pop_back();
                ret[prev] = i;
            } 
        }
        if(cur == '[' || cur == '{') {
            st.emplace_back(i, cur);
        } else if(cur == ']' || cur == '}') {
            if(st.empty()) Error("no left correspondence: index " + to_string(i));
            auto [prev, c] = st.back();  st.pop_back();
            if(correspond(c, cur) == false) Error(string("not correspond: ") + to_string(prev) + c + ", " + to_string(i) + cur);
            ret[prev] = i;
        }
    }
    if(!st.empty()) Error("left thing in the stack. something not closed");
    return ret;
}