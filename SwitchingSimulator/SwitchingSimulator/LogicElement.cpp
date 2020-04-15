#include "stdafx.h"
#include "LogicElement.h"


#include <string>

struct elementStruct{
	char* type;
	int* inputs;
	int output;
};

elementStruct element;

LogicElement::LogicElement()
{
	esw = 0;
}


LogicElement::~LogicElement()
{
}

void LogicElement::setElementAttributes(char * type_p, int * inputs_p, int output_p)
{
	element.type = type_p;
	element.inputs = inputs_p;
	element.output = output_p;
}

void LogicElement::getElementAttributes(char*& type_p, int*& inputs_p, int& output_p) {
	type_p = element.type;
	inputs_p = element.inputs;
	output_p = element.output;
}