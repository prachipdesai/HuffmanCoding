/*
 * decoder.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: Prachi Prakash Desai
 */
#include "decoder.h"

#include <iostream>
#include <string>

using namespace std;

void Decode::addLeafAt(int value, string binaryString) {
    Node *current;
    current = root;
    for (int i = 0; i < binaryString.length(); i++) {
        if (binaryString.at(i) == '0') {
            if (current->left == NULL) {
                Node* newNode = new (struct Node);
                current->left = newNode;
            }
            current = current->left;
        }
        else if (binaryString.at(i) == '1') {
            if (current->right == NULL) {
                Node* newNode = new (struct Node);
                current->right = newNode;
            }
            current = current->right;
        }
    }
    current->value = value;
    current->isLeaf = true;
}

int Decode::getAt(string binaryString) {
    Node *current;
    current = root;

    for (int i = 0; i < binaryString.length(); i++) {
        if (current == NULL) {
            return -1;
        }
        else if (binaryString.at(i) == '0') {
            current = current->left;
        }
        else if (binaryString.at(i) == '1') {
            current = current->right;
        }
    }
    if (current->isLeaf == true) {
        return current->value;
    }
    else {
        return -1;
    }
}

Node* Decode::getRoot() {
    return root;
}




