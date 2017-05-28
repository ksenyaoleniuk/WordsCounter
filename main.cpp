#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <atomic>

#include <queue>
#include <sstream>

#include <cmath>

using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
void read_file(size_t block_size, string filename, deque<vector<string>> &que,mutex &m)
{

    string line;
    vector<string> lines;
    size_t line_index = 0;
    ifstream myfile(filename);

    while(getline(myfile, line) && line_index < block_size) {
        ++line_index;
        lines.push_back(line);
        if (line_index == block_size) {
            m.lock();
            que.push_back(lines);
            m.unlock();
            lines.clear();
            line_index = 0;
        }
    }
    if (line_index >0 )
    {
        m.lock();
        que.push_back(lines);
        m.unlock();
    }

};

map<string, string> parsing_config(string filename){
    string line, delimiter;
    ifstream myfile(filename);
    map<string, string> mp;
    delimiter = "=";
    if (myfile.is_open()) {
        while(getline(myfile, line)) {
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
