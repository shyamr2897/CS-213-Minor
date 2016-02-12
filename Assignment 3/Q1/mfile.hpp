#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

class MFile {
private:
    ifstream m_fs;
    int m_line_size;
    char* buf;
public:
    /**
     * Returns 0 on success.
     */
    int init(string fname, int line_size);
    
    /**
     * Returns a non empty string on success.
     */
    string readNext();
    
    /**
     * Returns a non empty string on success.
     */
    vector<string> readLines(vector<int> line_num);
    
    /**
     * Returns 0 on success.
     */
    int close();
};