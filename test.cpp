#include "hash_map/hash_map.hpp"
#include <iostream>
#include <string>

int main(){
    hash_map<std::string, int> map;
    map["Mohsan"] = 10;
    auto f = map.find("Mohsan");
    if(f){
        std::cout << f->first << " " << f->second << std::endl;
    }
    return 0;
}