#include <iostream>
#include "hash/hash_map.hpp"

int main(){
    hash_map<char, int> map;
    map['C'] = 10;
    auto f = map.find('C');
    map.erase('C');
    f = map.find('C');
    map.insert({'A', 20});
    f = map.find('A');
    hash_map<char, int> new_map= std::move(map);
    f = new_map.find('A');
    if(f){
        std::cout << f->first << " " << f->second << std::endl;
    }
    else{
        std::cout<< "Not found" << std::endl;
    }
    return 0;
}