#include "PreComputation/PreComputation.h"

using namespace PreCmpt;

void main()
{	
	string schemaName = "FoodMart 2000";
	string cubeName = "Sales";

    PreComputation p;
    string ret = p.preCompute(schemaName, cubeName);
}