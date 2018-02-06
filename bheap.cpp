/*
 * bheap.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: Prachi Prakash Desai
 */
#include "bheap.h"

#include <iostream>
#include <algorithm>

int bheap::size(){
	return _heap.size();
}

int bheap::leftchild(int i){
	return 2*i+1;
}

int bheap::rightchild(int i){
	return 2*i+2;
}

int bheap::parent(int i){
	return (i-1)/2;
}

void bheap::percolateup(int i){

	int pr=parent(i);
	if(i<_heap.size() && pr>=0 && (*_heap[i]< *_heap[pr])){
		std::swap(_heap[pr],_heap[i]);
		percolateup(pr);
	}
}

void bheap::percolatedown(int i){

	int l=leftchild(i);
	int r=rightchild(i);
	int small=i;
	if(l<_heap.size() && (*(_heap[l])< *(_heap[small]))){
		small=l;
	}
	if(r<_heap.size() && (*(_heap[r]) < *(_heap[small]))){
		small=r;
	}

	if(small!=i){
		std::swap(_heap[i],_heap[small]);
		percolatedown(small);
	}

}

void bheap::insert(hnode const* ele){

	_heap.push_back(ele);
	percolateup(_heap.size()-1);
}

void bheap::delete_min(){
	int length=_heap.size()-1;
	if(length>=0){
		_heap[0]=_heap[length];
		_heap.pop_back();
		percolatedown(0);
	}
}

hnode const* bheap::get_min(){
	if(_heap.size()==0){
		return NULL;
	}

	return _heap[0];
}

void bheap::displayheap(){
	std::cout<<"Binary Heap [frequency: value]\n";
	for(hnode const* ele:_heap){
		std::cout<<"["<<ele->freq<<" : "<<ele->data<<"]\n";
	}
	std::cout<<std::endl;
}

bheap::bheap(std::vector<hnode const*> &hnodes){
	for(hnode const * huff_node:hnodes){
		insert(huff_node);
	}
}

bheap::~bheap(){
}




