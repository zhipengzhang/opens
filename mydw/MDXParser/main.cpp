#include "MdxParser/yacc1.h"

using namespace dwschemac;
using namespace std;

int main(int argc, char *argv[])
{		  
	// Set the input stream (either a file from the command line or stdin)
		  
	yyin = fopen("TestSample\\Ancestor.txt","rt");

//		 std::ofstream logFile("out.txt");
//		 std::streambuf *outbuf = std::cout.rdbuf(logFile.rdbuf());


	//yyin<<s;
	yyparse (); // call the parser 
   
	if(ErrorSummary ()>0) { system("pause"); return 0; } 

		   
//	st.show();
	tree->init();
//	tree->show();
		   
	//creat a schema and print it
	XSchemas* s = &(XSchemas::instance());
	
	s->createSchema("E:\\FoodMart.xml");
	XSchema *ok=s->getSchema("FoodMart 2000");

//	//ParsedMDX* p = tree->traverse(vecMemInfo, vecMem, vecTuple, vecSet, ok);			
	ParsedMDX* p = tree->getParsedMDX(ok);   
//	
	if(!p)
	{
		cout<<"error in the MDX query"<<endl;
		return 0;
	}		
	cout<<"\nAxes size is :"<<(p->getAxes()).size()<<endl;			
	p->showParsedMDX(); 
 
				 
// 	std::cout.rdbuf(outbuf);	     
//	system("pause");	    

	return 0;   
}