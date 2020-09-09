#include "bst.hpp"
#include <iostream>

int main(){
    bst<int> b;
    b.add(5);
    b.add(2);
    b.add(22);
    b.add(1);
    b.add(3);
    b.add(18);
    b.add(31);
    b.add(29);
    b.add(35);
    b.add(27);
    //b.remove(22);
    b.add(20);
    b.add(19);
    b.add(21);
    b.print_tree();
    return 0;
}