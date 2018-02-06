/*
 * encoder.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: Prachi Prakash Desai
 */
#include "bheap.h"
#include "fheap.h"
#include "pheap.h"
#include "hnode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <ctime>
#include <stack>
#include <string>
#include <queue>

void FillFreqMap(
	std::ifstream &infile,
	std::unordered_map<int,unsigned int> &freq_map){

	int number;
	while(infile >> number){
		auto it_f=freq_map.find(number);
		if(it_f!=freq_map.end()){
			it_f->second++;
		} else {
			freq_map[number]=1;
		}
	}
}

void CreateHnodeVec(
	std::unordered_map<int,unsigned int> const &freq_map,
	std::vector<hnode const*> &hnode_vec){

	for(auto it:freq_map){
		hnode* huff_node=new hnode(it.first,it.second,NULL,NULL);
		hnode_vec.push_back(huff_node);
	}
}

hnode const* BuildTreeFheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVec(freq_map,hnode_vec);

	fheap fheap_obj(hnode_vec);

	unsigned int freq;

	while (fheap_obj.size() > 4)
	{

		hnode const *left =fheap_obj.get_min();
		fheap_obj.delete_min();


		hnode const *right = fheap_obj.get_min();
		fheap_obj.delete_min();


		freq=left->freq + right->freq;

		hnode const* parent = new hnode(-1,freq, left, right );
		fheap_obj.insert(parent);

	}
	return fheap_obj.get_min();
}

hnode const* BuildTreeBheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVec(freq_map,hnode_vec);

	bheap bheap_obj(hnode_vec);

	bheap_obj.displayheap();
	unsigned int freq;

	int count=0;
	while ((bheap_obj.size() > 1))
	{	count++;

		hnode const *left =bheap_obj.get_min();
		bheap_obj.delete_min();


		hnode const *right = bheap_obj.get_min();
		bheap_obj.delete_min();


		freq=left->freq + right->freq;

		hnode const* parent = new hnode(-1,freq, left, right );
		bheap_obj.insert(parent);

	}
	return bheap_obj.get_min();
}


hnode const* BuildTreePheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVec(freq_map,hnode_vec);

	pheap pheap_obj(hnode_vec);

	pheap_obj.displayheap();
	unsigned int freq;

	while ((pheap_obj.size() > 1))
	{
		hnode const *left =pheap_obj.find_Min();
		pheap_obj.delete_Min();
		hnode const *right = pheap_obj.find_Min();
		pheap_obj.delete_Min();

		freq=left->freq + right->freq;

		hnode const* parent = new hnode(-1,freq, left, right );
		pheap_obj.Insert(parent);
	}
	return pheap_obj.find_Min();
}


void printCodes(
		hnode const *root,
		std::string str,
		std::unordered_map<int,std::string> &code_table_map
		)
{

    if (!root)
        return;

    if (root->data != -1){

    	code_table_map[root->data]=str;
    }

    printCodes(root->left, str + "0",code_table_map);
    printCodes(root->right, str + "1",code_table_map);
}


char setBit(char num, int i){
	return num|(1<<i);
}

void compress(std::string &value,std::vector<char> &result){

	char res=0;
	char str;
	for(long i=0;i<value.size();){
		res=0;
		for(int j=7;j>=0;j--){
			if(value[i]=='1')
				res=setBit(res,j);
			i++;
		}
		result.push_back(res);
	}
}

void binfilecreate(
		std::unordered_map<int,std::string> &code_table_map,
		char *filename,
		char const *out
		){

	std::ifstream infile (filename);
	std::ofstream onfile (out,std::ios::out | std::ios::binary);

	int number;
	std::string value;
	while(infile >> number){
		auto it_f=code_table_map.find(number);
		if(it_f!=code_table_map.end()){
			value+=it_f->second;

		} else {
			std::cout<<"Can't Happen: "<<(it_f->first)<<std::endl;
		}
	}
	std::cout<<"Reached File writing"<<std::endl;
	std::vector<char> result;
	compress(value,result);
	std::cout<<"Size of the result is:"<<result.size()<<", Size of the string is:"<<value.size()<<std::endl;
	char *res=&result[0];
	onfile.write(res,result.size());
	onfile.close();
	infile.close();

}

struct compare
{
    bool operator()(hnode* l, hnode* r)
    {
        return (l->freq > r->freq);
    }
};


int main(int argc, char *argv[]){

	if ( argc != 2 ){
		std::cout<<"Usage:./"<<argv[0]<<" <input_file_name>\n";
		return 0;
	}

	std::ifstream infile (argv[1]);
	if ( !infile.is_open() ){
	  std::cout<<"Could not open file\n";
	  return 0;
	}

	std::unordered_map<int,unsigned int> freq_map;
	FillFreqMap(infile,freq_map);

	infile.close();
	clock_t start_time;

//	std::cout<<"Huffman binary heap:"<<std::endl;
//	start_time=clock();
//	hnode const* rootb=BuildTreeBheap(freq_map);
//	std::unordered_map<int,std::string> code_table_map1;
//	printCodes(rootb,"",code_table_map1);
//	std::cout << "Time using binary heap (microsecond):  " << (clock() - start_time)/10 << std::endl;

	std::string of;
	std::cout<<"Huffman 4way heap:"<<std::endl;
	start_time=clock();
	hnode const* rootf=BuildTreeFheap(freq_map);
	std::unordered_map<int,std::string> code_table_map2;
	printCodes(rootf,"",code_table_map2);
	of="encoded.bin";
	char const *o2=of.c_str();
	binfilecreate(code_table_map2,argv[1],o2);
	std::cout << "Time using 4-way heap (microsecond):  " << (clock() - start_time)/10 << std::endl;

//	hnode* failsafe_root=failsafe(freq_map);
//	std::unordered_map<int,std::string> code_table_map4;
//	printCodes(failsafe_root,"",code_table_map4);
//	of="failsafe.bin";
//	char const *o4=of.c_str();
//	binfilecreate(code_table_map4,argv[1],o4);

//	std::cout<<"Encode table:"<<std::endl;
//	for(auto it:freq_map){
//		std::cout<<it.first<<":"<<it.second<<std::endl;
//	}

	std::cout<<"Encode table:"<<std::endl;
	std::string code_table_file_name="code_table.txt";
	std::ofstream onfile (code_table_file_name,std::ios::out);
	for(auto it:code_table_map2){
		onfile<<it.first<<" "<<it.second<<"\n";
	}

	onfile.close();
//	std::cout<<"Huffman pairing heap:"<<std::endl;
//	start_time=clock();
//	hnode const* rootp=BuildTreePheap(freq_map);
//	std::unordered_map<int,std::string> code_table_map3;
//	printCodes(rootp,"",code_table_map3);
//	std::cout << "Time using pairing heap (microsecond):  " << (clock() - start_time)/10 << std::endl;

	return 0;
}


