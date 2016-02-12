#include "mfile.hpp"
#include <algorithm>
#include <vector>
using namespace std;
int MFile::init(string fname, int line_size) {
    m_line_size = line_size;
    m_fs.open(fname);
    if (m_fs.is_open()) {
        buf = new char[line_size+1];
        return 0;
    }
    return -1;
}

string MFile::readNext() {
    m_fs.read(buf, m_line_size);
    
    buf[m_fs.gcount()] = 0;
    string s(buf);
    return s;
}

vector<string> MFile::readLines(vector<int> line_nums) {
    sort(line_nums.begin(), line_nums.end());
    streampos cur_pos = m_fs.tellg();
    vector<string> lines;
    for (auto line_num : line_nums) {
        m_fs.seekg(line_num * m_line_size, m_fs.beg);
        lines.push_back(readNext());
    }
    m_fs.seekg(cur_pos, m_fs.beg);
    return lines;
}

int MFile::close() {
    return 0;
}