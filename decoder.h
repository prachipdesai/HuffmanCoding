/*
 * decoder.h
 *
 *  Created on: Apr 4, 2017
 *      Author: Prachi Prakash Desai
 */
#include <iostream>
#include <string>
using namespace std;

/*
 *  Node Struct Prototype
 */

struct Node {
    struct Node *right = NULL;
    struct Node *left = NULL;
    int value;
    bool isLeaf = false;
};

/*
 *  Decode Class Prototype
 */


class Decode {
private:
    Node* root;
public:
    Node* getRoot();
    void addLeafAt(int value, string binaryString);
    int getAt(string binaryString);

    Decode() {
        root = new (struct Node);
    }
};



