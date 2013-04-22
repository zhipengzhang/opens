#include "Attribute.h"
#include "SoapBody.h"
#include "Soapenvelope.h"
#include "SoapFault.h"
#include "SoapHeader.h"
#include "SoapMethod.h"
#include "SoapSerializer.h"
#include <LIST>
using namespace std;

/*
已经完成的类：SoapHeader、ComplexElement、CharacterElement、HeaderBlock、Attribute、Namespace、SoapBody、
SoapEnvelope、SoapMethod
未完成：SoapSerializer、SoapFaoult、Param、SOAPTransport、关于数组方面、Attachment

*/
extern SoapEnvVersionsStruct gs_SoapEnvVersionsStruct[VERSION_LAST];

/*
int main(){
	
	SoapSerializer serializer;
	SOAPTransport *soaptransport;
	serializer.init();

	serializer.addNamespaceToNamespaceList("urn:schemas-microsoft-com:xml-analysis","m");
	serializer.addNamespaceToNamespaceList("http://www.w3.org/2001/XMLSchema-instance","xsi");
	serializer.addNamespaceToNamespaceList("http://www.w3.org/2001/XMLSchema","xsd");
	serializer.addNamespaceToNamespaceList("urn:schemas-microsoft-com:xml-analysis:mddataset","n");
	serializer.addNamespaceToNamespaceList("EX","urn:schemas-microsoft-com:xml-analysis:exception");

	//SoapMethod
	serializer.createSoapMethod("ExecuteResponse","urn:schemas-microsoft-com:xml-analysis",true);
	
	MDDataSet mddatset(1,2,3,"ddd");
	serializer.addOutputCmplxParam(&mddatset,(void *)execute,NULL,"root","urn:schemas-microsoft-com:xml-analysis:mddataset");

	serializer.setOutputStream(soaptransport);
	return 0;
}*/

