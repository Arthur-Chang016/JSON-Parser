
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