#include <iostream>
#include <string>
#include "tree.h"

using namespace std;

int main()
{
	tree huffman_tree;
	int option;
	//string input = "Hello my name is Ameya and this is the huffmann code. I got bored so I am writing this text, to see if I can type with a speed of 50wpm but that doesn't seem the case.";
	cout << "WANT TO SET SEPARATORS BETWEEN EACH CCOMPRESSED CHARACTER? 0 = false" << endl;
	cin >> option;
	
	if(option == 0)
		huffman_tree.disableSeparator = false;
	else
		huffman_tree.disableSeparator = true;
	
	cout << "ENTER YOUR INPUT TEXT" << endl;
	string input;	
	cin.ignore();
	getline(cin,input);
	
	huffman_tree.makeTree(input);
	huffman_tree.makeTree(input);

	cout << huffman_tree.output << endl;
	cout << "ORIGINAL   SIZE = "  << input.size()*8 << " BITS" << endl;
	cout << "COMPRESSED SIZE = "  << huffman_tree.output.size()<< " BITS" << endl;
	
	cout << "PERCNTAGE DATA SIZE REDUCTION W.R.T. ORIGINAL SIZE = " << ((input.size()*8 - (float)huffman_tree.output.size())/(input.size()*8)) * 100 << "%" << endl;
	
	cout << "COMPRESSING AND SAVING TEXT TO FILE" << endl;
	huffman_tree.writeToFile("customCompressedFile.huffman");
	
	return 0;
}
