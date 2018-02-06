/*
 * bheap.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Prachi Prakash Desai
 */
#ifndef BHEAP_H_
#define BHEAP_H_

#include "hnode.h"
#include <vector>

class bheap{

	std::vector<hnode const*> 			_heap;

	void 								percolateup(int i);
	void 								percolatedown(int i);
	int 								leftchild(int i);
	int 								rightchild(int i);
	int 								parent(int i);

public:

										bheap();
										~bheap();
										bheap(std::vector<hnode const *> &numbers);
	void 								insert(hnode const* ele);
	hnode const* 						get_min();
	void 								delete_min();
	int 								size();
	void								displayheap();

};

#endif /* BHEAP_H_ */
