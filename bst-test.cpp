#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<int,string> bt;
	std::pair<int, std::string> item5(5, "five");
	std::pair<int, std::string> item3(3, "three");
	std::pair<int, std::string> item7(7, "seven");
	std::pair<int, std::string> item4(4, "four");
    std::pair<int, std::string> item6(6, "six");
    std::pair<int, std::string> item9(9, "nine");
    bt.insert(item5);
    bt.insert(item3);
    bt.insert(item7);
    bt.insert(item4);
    bt.insert(item6);
    bt.insert(item9);
    // bt.remove(5);
    // bt.remove(7);
    //bt.insert(std::make_pair('f',6));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<int,string>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');

    bt.print();

    //AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));
    at.insert(std::make_pair('b',2));
    at.insert(std::make_pair('c',3));
    at.insert(std::make_pair('d',4));
    at.insert(std::make_pair('e',5));
    at.insert(std::make_pair('f',6));
    at.insert(std::make_pair('g',7));
    at.insert(std::make_pair('h',8));
    at.insert(std::make_pair('i',9));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    //cout << "Erasing b" << endl;
    //at.remove('b');
    at.print();

    return 0;
}
