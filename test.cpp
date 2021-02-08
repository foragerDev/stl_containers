#include <iostream>
#include "my_array/my_array.hpp"
#include <array>
int main(){
    my_array<int, 10> my_arr;
//    my_array<int, 10> my_arr2 = my_arr;
    my_arr.fill(10);
    my_arr[5] = 11;
    my_array<int, 10> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    arr = std::move(my_arr);
    for (int i = 0; i < 10; i++)
    {
        std::cout << my_arr[i] << std::endl;
    }
    std::cout << "Second Array" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}