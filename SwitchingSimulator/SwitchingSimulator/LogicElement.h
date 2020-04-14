#pragma once
class LogicElement
{
public:
	LogicElement();
	~LogicElement();
	void setElementAttributes(char* type_p, int* inputs_p, int output_p);
	int nnn;
	void getElementAttributes(char*& type_p, int*& inputs_p, int& output_p);
};

