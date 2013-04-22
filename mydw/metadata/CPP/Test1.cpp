
#include <iostream>
#include <string>
#include "Dimension.h"
#include "Hierarchy.h"
#include "XSchemas.h"

using namespace dwschemac;
using namespace std;

void main()
{
	XSchemas s;
  	s.createSchema("d:\\smq.xml");
    XSchema *ok=s.getSchema("FoodMart");
    Dimension *d=ok->getShareDimension("Time");
	Hierarchy *h=d->getHierarchy("Time");
    
	if(h)
	{
		h->LoadMembers();
		h->printMembers();
	}
    s.Dispose();
	system("pause");
/*
	Level *L= h->getLevel("Store Name");

	h->writeXML("D:\\test3.xml");
	L->writeXML("D:\\test4.xml");
	d->writeXML("D:\\test5.xml");	
	ok->writeXML("D:\\test.xml");
	while(1)
	{
		string op1;
		cout<<"=================test===============\n"<<endl;
		cout<<"please intput op"<<endl;
        cout<<"1. add a schema with xml file"<<endl;
        cout<<"2. get a schema obj "<<endl;
		cout<<"0. exit test"<<endl;
		cout<<"please chose:";
		cin>>op1;
		if(op1=="1")
		{
			cout<<"file path:";
			string fp;
			cin>>fp;
			if(s.createSchema(fp))
			{
				cout<<"success!"<<endl;
			}
		}
		else if(op1=="2")
		{
			while(1)
			{
				cout<<"\n OP3\n";
				cout<<" you want obj"<<endl;
				cout<<" 1. schema"<<endl;
				cout<<" 0. cancel op"<<endl;
				string op31;
				cout<<" please chose:";
				cin>>op31;
				if(op31=="0")
				{
					cout<<"cancel OP3\n"<<endl;
					break;
				}
				if(op31=="1")
				{
					string scn;
					cout<<"input name:";
					cin>>scn;
					XSchema *ok=s.getSchema(scn);
					if(ok!=NULL)
					{
						while(1)
						{
							cout<<"\n\n chose OP:\n";
							cout<<" 1. write me into xml file"<<endl;
							cout<<" 2. print me "<<endl;
							cout<<" 3. get shared dimension "<<endl;
							cout<<" 4. get cube "<<endl;
							cout<<" 0. cancel op"<<endl;
							string op;
							cout<<" please chose:";
							cin>>op;
							if(op=="0")
							{
								cout<<"exit schema op"<<endl;
								break;
							}
							if(op=="1")
							{
								cout<<"oup file:";
								string fp;
								cin>>fp;
                                if(!ok->writeXML(fp))
								{
									cout<<"error"<<endl;
								}
								else
								{
									cout<<"success!"<<endl;
								}
							}
							if(op=="2")
							{
								cout<<"print Schema:"<<endl;
								ok->print();
							}
							if(op=="3")
							{
								string scn;
								cout<<"input name:";
								cin>>scn;
								Dimension *ok1=ok->getShareDimension(scn);
								if(ok1!=NULL)
								{
									while(1)
									{
										cout<<"\n\n chose OP:\n";
										cout<<" 1. write me into xml file"<<endl;
										cout<<" 2. print me "<<endl;
										cout<<" 3. get hierarchy "<<endl;
										cout<<" 0. cancel op"<<endl;
										string op;
										cout<<" please chose:";
										cin>>op;
										if(op=="0")
										{
											cout<<"exit share dimension op"<<endl;
											break;
										}
										if(op=="1")
										{
											cout<<"oup file:";
											string fp;
											cin>>fp;
											if(!ok1->writeXML(fp))
											{
												cout<<"error"<<endl;
											}
											else
											{
												cout<<"success!"<<endl;
											}
										}
										if(op=="2")
										{
											cout<<"print shared dimension:"<<endl;
											ok1->print();
										}
										if(op=="3")
										{
											string scn;
											cout<<"input name:";
											cin>>scn;
											Hierarchy * h=ok1->getHierarchy(scn);
											if(h==NULL)
											{
												cout<<"error!"<<endl;
											}
											else
											{
												h->print();
											}
										}							
									}						
								}
								 else
								{
									cout<<"\nno exists "<<"Dimension "<<scn<<endl; 
								}
						}
						if(op=="4")
						{
							string scn;
							cout<<"input name:";
							cin>>scn;
							XCube *ok2=ok->getCub(scn);
							if(ok!=NULL)
							{
							while(1)
							{
							cout<<"\n\n chose OP:\n";
							cout<<" 1. write me into xml file"<<endl;
							cout<<" 2. print me "<<endl;						
							cout<<" 3. get Measure "<<endl;
							cout<<" 4. get dimension "<<endl;
							cout<<" 0. cancel op"<<endl;
							string op;
							cout<<" please chose:";
							cin>>op;
							if(op=="0")
							{
								cout<<"exit cube op"<<endl;
								break;
							}
							if(op=="1")
							{
								cout<<"oup file:";
								string fp;
								cin>>fp;
                                if(!ok2->writeXML(fp))
								{
									cout<<"error"<<endl;
								}
								else
								{
									cout<<"success!"<<endl;
								}
							}
							if(op=="2")
							{
								cout<<"print Cube:"<<endl;
								ok2->print();
							}
							if(op=="3")
							{
								string scn;
								cout<<"input name:";
								cin>>scn;
								Measure * h=ok2->getMeasure(scn);
								if(h==NULL)
								{
												cout<<"error!"<<endl;
								}
								 else
								 {
									 string scn ;
									 cout<<"1. print"<<endl;
									 cout<<"2. write to file"<<endl;									 
									 cout<<"chose op:";
									 cin>>scn;
									 if(scn=="1")
									 {
												h->print();
									 }
									 if(scn=="2")
									 {
										 	cout<<"oup file:";
											string fp;
											cin>>fp;
											if(h->writeXML(fp))
											{
												cout<<"success"<<endl;
											}
									 }
								 }
							}
						}						
					}
					else
					{
						cout<<"\nno exists"<<" Cube "<<scn<<endl; 
					}
							}
						}						
					}
					else
					{
						cout<<"\nno exists"<<" schema "<<scn<<endl; 
					}
				}
			}

		}
		else if(op1=="0")
		{
			cout<<"  exit test"<<endl;
			break;
		}
	    cout<<"================end=output============\n\n" ;	
	}*/
}
