//
//  count_uniq.cpp
//
//
//  Created by Shyam Ramamoorthy on 15/02/16.
//
//  This implementation accounts for collisions.

#include <iostream>
#include <vector>
#include <map>
#include "mfile.hpp"

#define A 54059 /* a prime */
#define B 76963 /* another prime */
unsigned Hasher(const std::string& s)
{
    unsigned int h = 31 ;
    
    for(std::size_t i = 0; i < s.length(); i++)
    {
        h = (h * A) ^ (s[i] * B);
    }
    return h;
}


int main(){
    std::map <int, vector<int> > store;
    int uniq = 0;
    int index = 0;
    
    std::string inp_file;
    std::cin >> inp_file;
    
    int n;
    std::cin >> n;
    
    MFile file;
    file.init(inp_file, n);
    
    std::string line = file.readNext();
    
    while (!line.empty()){
        int line_hash = Hasher(line);
        
        std::vector<int> cur_line;
        cur_line.push_back(index);
        
        if(store.insert(pair<int, vector<int> > (line_hash, cur_line)).second) uniq += 1;
        //When the current hash doesn't match with any of the previous ones.
        
        else{
            //When the current hash already exists in the map.
            std::vector<int> line_nums = (store.find(line_hash))->second;
            
            std::vector<string> prev_lines = file.readLines (line_nums);
            bool isUnique = true;
            
            for (std::vector<string>::iterator it = prev_lines.begin() ; it != prev_lines.end(); ++it){
                if(*it == line) {
                    isUnique = false;
                    break;
                }
            }
            
            if (isUnique){
                uniq += 1;
                (store.find(line_hash)->second).push_back(index);
            }
            

        }
        index += 1;
        line = file.readNext();
    }
    file.close();
    std::cout << uniq << endl;
}
