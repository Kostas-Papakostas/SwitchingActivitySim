#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>

#include "LogicElement.h"

#include <string>

using namespace std;

LogicElement* elementTable;
int signals[6] = { 0, 0, 0, 0, 0, 0 };
ifstream myfile;

int t_s[4][6] = {   {0,1,0,0,0,0},
					{1,1,0,0,0,0},
					{1,0,0,0,0,0},
					{0,0,1,0,0,0} };//first 3 colls are the input signals last 3 ones are the output of the first 3


/*HELPER FUNCTIONS*/
int spAND(int* in_p,int row_p) {
	int res=t_s[row_p][in_p[0]-1];
	//cout << "resin   " << res << endl;
	for (int i = 1; i < (sizeof(in_p) / sizeof(*in_p)); i++) {
		res = res&t_s[row_p][in_p[i]-1];
	}
	return res;
}

int spOR(int* in_p, int row_p) {
	int res = t_s[row_p][in_p[0] - 1];
	for (int i = 1; i < (sizeof(in_p) / sizeof(*in_p)); i++) {
		res = res | t_s[row_p][in_p[i] - 1];
	}
	return res;
}

int spXOR(int* in_p, int row_p) {
	int res = t_s[row_p][in_p[0] - 1];
	for (int i = 1; i < (sizeof(in_p) / sizeof(*in_p)); i++) {
		res = res ^ t_s[row_p][in_p[i] - 1];
	}
	return res;
}

int spNOT(int* in_p, int row_p) {
	int res = !t_s[row_p][in_p[0] - 1];
	/*if (t_s[in_p[0] - 1] == 0) {
		res = 1;
		return res;
	}*/
	return res;
}

int spNOR(int* in_p, int row_p) {
	int res = !spOR(in_p,row_p);
	return res;
}

int spNAND(int* in_p, int row_p) {
	int res = !spAND(in_p,row_p);
	return res;
}

int spXNOR(int* in_p, int row_p) {
	int res = !spXOR(in_p,row_p);
	return res;
}


int process(LogicElement el_p, int row_p) {
	char* type = "";
	int out = 0;
	int* inp = nullptr;
	el_p.getElementAttributes(type, inp, out);

	if (std::string(type).compare("AND") == 0) {
		t_s[row_p][out-1] = spAND(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
		if (row_p > 0 && (t_s[row_p-1][out - 1]!= t_s[row_p][out - 1])) {//checks previous and given output for changes
			return 1;
		}
	}
	else if (std::string(type).compare("OR") == 0) {
		t_s[row_p][out-1] = spOR(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
		if (row_p > 0 && (t_s[row_p - 1][out - 1] != t_s[row_p][out - 1])) {//checks previous and given output for changes
			return 1;
		}
	}
	else if (std::string(type).compare("XOR") == 0) {
		t_s[row_p][out-1] = spXOR(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
		if (row_p > 0 && (t_s[row_p - 1][out - 1] != t_s[row_p][out - 1])) {//checks previous and given output for changes
			return 1;
		}
	}
	else if (std::string(type).compare("NOT") == 0) {
		t_s[row_p][out-1] = spNOT(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
		if (row_p > 0 && (t_s[row_p - 1][out - 1] != t_s[row_p][out - 1])) {
			return 1;
		}
	}
	else if (std::string(type).compare("NAND") == 0) {
		t_s[row_p][out - 1] = spNAND(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
		if (row_p > 0 && (t_s[row_p - 1][out - 1] != t_s[row_p][out - 1])) {//checks previous and given output for changes
			return 1;
		}
	}
	else if (std::string(type).compare("NOR") == 0) {
		t_s[row_p][out - 1] = spNOR(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
		if (row_p > 0 && (t_s[row_p - 1][out - 1] != t_s[row_p][out - 1])) {//checks previous and given output for changes
			return 1;
		}
	}
	else if (std::string(type).compare("XNOR") == 0) {
		t_s[row_p][out - 1] = spXNOR(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
		if (row_p > 0 && (t_s[row_p - 1][out - 1] != t_s[row_p][out - 1])) {//checks previous and given output for changes
			return 1;
		}
	}
	else
	{
		cout << "Not supported logic" << endl;
	}
	return 0;

	//std::cout << "result of element    " << type <<"   "<< t_s[row_p][out-1] << endl;
}

int lineCounter(char* filename_p) {
	string line;
	int lines = 0;
	if (!myfile.is_open()) {
		myfile.open(filename_p);
	}
	while (getline(myfile, line))
	{
		lines++;
	}
	myfile.close();
	return lines;
}

void fileParser(char* filename_p, char*& logicElement_p, int*& inputs_p, int& output_p) {
	string line;
	if (!myfile.is_open()) {
		myfile.open(filename_p);
	}
	
	getline(myfile, line);

	string temp;
	//find the logic name
	int i;
	for (i = 0; i < line.length(); i++) {
		if (line[i] == ' ') {
			temp.append(line.substr(0, i));
			logicElement_p = new char[(int)temp.length()];
			for (int k = 0; k < (int)temp.length(); k++) {
				logicElement_p[k] = temp.at(k);
			}
			logicElement_p[(int)temp.length()] = '\0';
			break;
		}
	}

	//get the output value
	i++;
	output_p = line.at(i)-48;
	i++;

	//get the inputs
	string tempInput;
	tempInput.append(line.substr(i, line.length()));
	tempInput.erase(std::remove_if(tempInput.begin(), tempInput.end(), ::isspace), tempInput.end());
	
	int size = (int)tempInput.length();
	int* tempInp;
	tempInp = new int(size);
	inputs_p = new int(size);
	for (int j=0; j < (int)tempInput.length(); j++) {
		tempInp[j]= tempInput.at(j) - 48;
		inputs_p[j]= tempInput.at(j) - 48;
	}

	if (myfile.eof()) {
		myfile.close();
	}

}

int main()
{
	int lines = lineCounter("method2.txt");//lines counter which computes the number of elements
	int* inputRef=nullptr;
	int outRef=0;
	char* nameRef="";

	elementTable = new LogicElement[lines];
	int input1[2] = { 1,2 };
	int input2[1] = { 3 };
	int input3[2] = { 5,6 };
	int eswEl1=0,eswEl2=0,eswEl3=0;
	
	for (int i = 0; i < 4; i++) {
		for (int l = 0; l < lines; l++) {

			fileParser("method2.txt", nameRef, inputRef, outRef);
			//cout << "length:" << sizeof(inputRef) / sizeof(int) << "   outputPin:" << outRef << "    name:" << nameRef << endl;
			elementTable[l].setElementAttributes(nameRef, inputRef, outRef);
			elementTable[l].esw += process(elementTable[l], i);
		}
		system("PAUSE");
	}
	for (int i = 0; i < lines; i++) {
		cout << "element " << i+1 << " switching activity    " << elementTable[i].esw << "/" << 3 << endl;
	}

	system("PAUSE");
    return 0;
}

