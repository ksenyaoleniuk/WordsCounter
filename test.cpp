//
// Created by oksana on 28.05.17.
//

#include "test.h"
//string line;
//vector<string> lines;
//size_t line_index = 0;
//
//while(getline(file, line) && line_index < block_size)
//{
//++line_index;
//lines.push_back(line);
//}



vector<vector<string>> read_file(string filename, int threads){
    ifstream in1(filename);
    string s;
    vector<string> words;
    vector<vector<string>> listOfWords;
    for (int i = 0; i < threads; ++i) listOfWords.push_back(words);
    int i = threads;
    while (in1 >> s) {
        --i;
        listOfWords[i].push_back(s);
        if (i==0) i = threads;
    }
    in1.close();
    return listOfWords;
}

void read_file(int &flag,size_t block_size,string nameOFfile,deque<vector<string>> &que_with_work,mutex &m) {
    vector<string> words;
    ifstream myfile(nameOFfile);
    string line;
    size_t line_index = 0;
    while (getline(myfile, line)) {
        ++line_index;
        words.push_back(line);
        if (line_index == block_size) {
            m.lock();
            que_with_work.push_back(words);
            m.unlock();
            line_index = 0;
            words.clear();
        }
    }
    if (line_index > 0)
    {
        m.lock();
        que_with_work.push_back(words);
        m.unlock();
    }
    flag = 1;
}

map<string, string> read_config(string filename) {
    string line, delimiter;
    ifstream myfile(filename);
    map<string, string> mp;

    delimiter = "=";


    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            int pos = line.find(delimiter);
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            mp[key] = value;
        }

        myfile.close();
    } else {
        cout << "Error with opening the file!" << endl;
    }
    return mp;

};
