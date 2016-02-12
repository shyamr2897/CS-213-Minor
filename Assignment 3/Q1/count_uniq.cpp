#include <iostream>
#include <string>
#include <set>
#include "mfile.hpp"

#define A 54059
#define B 76963 
#define C 86969 

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
    std::string inp_file;
    std::cin >> inp_file;
    
    int n;
    std::cin >> n;
    
    MFile file;
    file.init(inp_file,n);
    
    std::string current = file.readNext();
    std::set<int> store;
    int uniq=0;
    
    
    while(current.length() > 0) {
        int cur_hash = Hasher(current);
        if(store.insert(cur_hash).second) uniq += 1;
        current = file.readNext();
    }
    
   std::cout << uniq;
    
}
