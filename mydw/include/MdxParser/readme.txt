int main(int argc, char *argv[])
{
  // Set the input stream (either a file from the command line or stdin)
   yyin = fopen("D:\\mdx_compiler20070903\\Debug\\big4.txt","rt");
   
     std::ofstream logFile("out.txt");
     std::streambuf *outbuf = std::cout.rdbuf(logFile.rdbuf());
   
  //yyin<<s;
   yyparse (); // call the parser 
   
   ErrorSummary ();

//   st.show();
//   tree->show();
   
   //creat a schema and print it
   XSchemas s;
	s.createSchema("D:\\smq.xml");
	XSchema *ok=s.getSchema("FoodMart");
	
 	//ParsedMDX* p = tree->traverse(vecMemInfo, vecMem, vecTuple, vecSet, ok);
	ParsedMDX* p = tree->getParsedMDX(ok);
 	p->showParsedMDX();
   
    std::cout.rdbuf(outbuf);

	system("pause");
	s.Dispose();
	return 0;   
}