#include <iostream>		// TEMPORARILY INCLUDED TO PUT LOGS FOR DEBUGGING
////TREE DEFINITIONS
tree :: tree()
{
	root = NULL;
	output = "";
	disableSeparator = false;
	
	freq_count = new int [123];
	memset(freq_count,0,sizeof(freq_count));
	
	node_queue = std::priority_queue<node*,std::vector<node*>,node_comparator>(node_comparator());
}

tree :: ~tree()
{
	delete freq_count;
}

void tree:: makeTree(std::string inp)
{
	memset(freq_count,0,sizeof(freq_count));
	
	int len = inp.length();
	int i;
	
	for(i=0; i<len; i++)
		freq_count[inp[i]]++;
		
	for(i=0;i<123;i++)
		if(freq_count[i] > 0)
			node_queue.push(new node((char) i,freq_count[inp[i]]));
	
	while(node_queue.size() > 1)
	{
		node *child1 = node_queue.top();
		node_queue.pop();
		
		node *child2 = node_queue.top();
		node_queue.pop();
		
		node_queue.push(new node(-1,child1->freq+child2->freq,child1,child2));		
	}	
	
	if(!node_queue.empty())
		root = node_queue.top();

	//SETS NULL TERMINATING CHARACTER ON THE LEFT OF THE WHOLE HEAP
	node *temp_node = root;
	while(temp_node->left != NULL)
		temp_node = temp_node->left;
	
	temp_node->left = new node(0,0);
	
	node_queue.pop();
	
	
	output = "";
	 
	for(i=0; i<len; i++){
		std::string curr_char = root->getCode(inp[i]);
		
		if(!disableSeparator)
			curr_char.pop_back();
		
		output += curr_char;
	}

	
}

void tree :: writeToFile(std::string filename)
{
		const char *file = filename.c_str();
		bool outputWritten = false;
		int index = 0;
		int output_len = output.length();
		unsigned char write_char= 0;
		
		if(output_len % 8 != 0)
			output_len = (output_len/8 + 1)*8;
		
		//std::cout << "OUTPUT LENGTH : " << output_len << std::endl;
		std::fstream outFile;
		outFile.open(file,std::ios::out|std::ios::binary);
		
		while(index <= output_len)
		{
			if(index % 8 == 0 && index)
			{
				outFile << write_char ;
				//std::cout << "OUTPUT WORD : " << write_char << std::endl;
				write_char = 0;
			}
			write_char = (write_char << 1);

			if(index < output.length())
				write_char += (unsigned)(output[index]-'0');
			else
				write_char += 0;
			
			++index;
		}
		outFile.close();
		std::cout << "FILE SUCCESSFULLY SAVED" << std::endl;
}

////NODE DEFINITIONS
std::string node :: getCode(char inp_char)
{
	//sstring curr = "";
	
	if(this->ch < 0)	
	{
		
		std::string left_str  = this->left->getCode(inp_char);
		
		std::string right_str = this->right->getCode(inp_char);
		
		if(left_str.back() != 'x')
		{
			std::string left_child_str = "0" + left_str ;
			return left_child_str;
		}
		else// if(right_str.back() != 'x')
		{
			std::string right_child_str = "1" + right_str;
			return right_child_str;
		}
	}
	else
	{
		if(ch == inp_char)
			return std::string("|");
		else
			return std::string("x");
	}
	
}
