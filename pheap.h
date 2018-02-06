/*
 * pheap.h
 *
 *  Created on: Apr 1, 2017
 *      Author: Prachi Prakash Desai
 */
#ifndef PHEAP_H_
#define PHEAP_H_

#include <vector>
#include <cstddef>
#include "hnode.h"
class pnode
{
    public:
        hnode const *huff_node;
        pnode *leftChild;
        pnode *nextSibling;
        pnode *prev;
        pnode(hnode const* huff_node):
		huff_node(huff_node),
		leftChild(NULL),
		nextSibling(NULL),
		prev(NULL)
		{ }
};

class pheap
{
    private:
		long _heapsize;
        pnode *root;
        std::vector<pnode*> pnode_list;
        void reclaimMemory(pnode *t);
        void compareAndLink(pnode * &first, pnode *second);
        pnode *combineSiblings(pnode *firstSibling);

    public:
        pheap();
        pheap(std::vector<hnode const*> & numbers);
        ~pheap();
        bool isEmpty();
        bool isFull();
        pnode *Insert(hnode const* x);
        hnode const *find_Min();
        void delete_Min();
        void makeEmpty();
        void displayheap();
        long size();

};



#endif /* PHEAP_H_ */


