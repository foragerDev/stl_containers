#include <iostream>
#include "hash/hash_map.hpp"

int main(){
    hash_map<char, int> map;
    map['C'] = 10;
    auto f = map.find('C');
    if(f){
        std::cout << f->first << " " << f->second << std::endl;
    }
    else{
        std::cout<< "Not found" << std::endl;
    }
    return 0;
}