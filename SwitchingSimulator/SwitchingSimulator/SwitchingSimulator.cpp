#include "stdafx.h"
#include <iostream>

#include "LogicElement.h"

#include <string>

using namespace std;

LogicElement* elementTable;
int signals[6] = { 0, 0, 0, 0, 0, 0 };

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
	}
	else if (std::string(type).compare("XOR") == 0) {
		t_s[row_p][out-1] = spXOR(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
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
	}
	else if (std::string(type).compare("NOR") == 0) {
		t_s[row_p][out - 1] = spNOR(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
	}
	else if (std::string(type).compare("XNOR") == 0) {
		t_s[row_p][out - 1] = spXNOR(inp, row_p);
		std::cout << "result of element    " << type << "   " << t_s[row_p][out - 1] << endl;
	}
	else
	{
		cout << "Not supported logic" << endl;
	}
	return 0;

	//std::cout << "result of element    " << type <<"   "<< t_s[row_p][out-1] << endl;
}

int main()
{
	elementTable = new LogicElement[3];
	int input1[2] = { 1,2 };
	int input2[1] = { 3 };
	int input3[2] = { 5,6 };
	int eswEl1=0,eswEl2=0,eswEl3=0;
	
	for (int i = 0; i < 4; i++) {
		elementTable[0].setElementAttributes("AND", input1, 5);
		eswEl1 =eswEl1 + process(elementTable[0],i);

		elementTable[1].setElementAttributes("NOT", input2, 6);
		//process(elementTable[1],i);
		eswEl2 = eswEl2 + process(elementTable[1], i);

		elementTable[2].setElementAttributes("AND", input3, 4);
		//process(elementTable[2],i);
		eswEl3 = eswEl3 + process(elementTable[2], i);
		cout << endl;
		system("pause");
	}
	cout << "element 1 switching activity    " << eswEl1 << "/" << 3 << endl;
	cout << "element 2 switching activity   " << eswEl2 << "/" << 3 << endl;
	cout << "element 3 switching activity   " << eswEl3 << "/" << 3 << endl;
	
	/*
	elementTable[0].setElementAttributes("XNOR", input1, 5);
	process(elementTable[0]);
	elementTable[1].setElementAttributes("NOT", input2, 6);
	process(elementTable[1]);
	elementTable[2].setElementAttributes("AND", input3, 4);
	process(elementTable[2]);
	*/
	system("PAUSE");
    return 0;
}

