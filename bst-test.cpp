#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    AVLTree<int, std::string> b, c, d;
	std::pair<int, std::string> item5(5, "five");
	std::pair<int, std::string> item3(3, "three");
	std::pair<int, std::string> item7(7, "seven");
	std::pair<int, std::string> item4(4, "four");
	std::pair<int, std::string> item6(6, "six");
	std::pair<int, std::string> item9(9, "nine");
	std::pair<int, std::string> item10(10, "ten");
	std::pair<int, std::string> item2(2, "two");
	std::pair<int, std::string> item8(8, "eight");
	std::pair<int, std::string> item13(13, "thirteen");
	std::pair<int, std::string> item11(11, "eleven");
	std::pair<int, std::string> item12(12, "twelve");
	std::pair<int, std::string> item15(15, "fifteen");
	std::pair<int, std::string> item14(14, "fourteen");
	std::pair<int, std::string> item16(16, "sixteen");
	std::pair<int, std::string> item17(17, "seventeen");

    b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	b.insert(item9);
	b.insert(item10);
	b.insert(item2);
	b.insert(item8);
    b.insert(item13);
    b.insert(item12);
    b.insert(item11);

    b.remove(13);
    b.remove(12);
    b.remove(10);

    b.print();
    
    
    // AVLTree<int,int> testTree; 
    // testTree.insert(std::make_pair(0,0));
    // testTree.insert(std::make_pair(1,1));
    // testTree.insert(std::make_pair(2,2));

    // testTree.print();

    // testTree.insert(std::make_pair(2, 8));
	// testTree.insert(std::make_pair(1, -50));
	// testTree.insert(std::make_pair(3, 0));
	// testTree.insert(std::make_pair(10, 0));
	// testTree.insert(std::make_pair(15, 0));
    // // testTree.print();
    // testTree.remove(-1);
    // // testTree.print();
    // testTree.remove(2);
    // testTree.remove(10);
    // testTree.print();
    // Binary Search Tree tests
    // 	BinarySearchTree<int, double> bst;
	// bst.insert(std::make_pair(2, 1.0));
	// bst.insert(std::make_pair(1, 1.0));
	// bst.insert(std::make_pair(3, 1.0));

	// bst.remove(2);
    // BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('b',2));
    
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');

    // // AVL Tree Tests
    // AVLTree<char,int> at;
    // at.insert(std::make_pair('a',1));
    // at.insert(std::make_pair('b',2));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    // return 0;
}
