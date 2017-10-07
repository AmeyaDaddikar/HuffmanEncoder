#ifndef TREE_H
#define TREE_H

#include <queue>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>

class node_comparator;
class tree;

class node {
	private:
		signed char ch;
		int freq;
		node *left;
		node *right;
		friend class node_comparator;
		friend class tree;
		
	public:
		node(char ch,int freq, node*left=NULL,node*right=NULL)
		{
			this->ch = ch;
			this->freq = freq;
			this->left=left;
			this->right=right;
		}
		
		std::string getCode(char);
		
};	

class node_comparator{
	private:	
	public:
		bool operator () (const node* lhs, const node* rhs) const {
			return (lhs->freq > rhs->freq);
		}
};




struct tree{
	private:
		node* root;
		
	public:
		 tree();
		~tree();
		
		std::priority_queue<node*,std::vector<node*>,node_comparator> node_queue;
		
		int* freq_count;
		std::string output;
		
		void writeToFile(std::string filename);
		void makeTree(std::string inp);
		bool disableSeparator;
		
		
};

#include "tree.cpp"

#endif
