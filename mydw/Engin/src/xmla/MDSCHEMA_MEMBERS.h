// MDSCHEMA_MEMBERS.h: interface for the MDSCHEMA_MEMBERS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDSCHEMA_MEMBERS_H__E5F98505_60CB_45AB_AADF_CFE51539AF5D__INCLUDED_)
#define AFX_MDSCHEMA_MEMBERS_H__E5F98505_60CB_45AB_AADF_CFE51539AF5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rowset.h"
#include <DWSchemac/XSchemas.h>
#include <DWSchemac/XSchema.h>
#include <DWSchemac/Dimension.h>
#include <DWSchemac/XCube.h>
#include <DWSchemac/Hierarchy.h>
#include <DWSchemac/Level.h>
#include <DWSchemac/Measure.h>
#include <DWSchemac/Member.h>
#include <DWSchemac/calcMember.h>

using namespace dwschemac;

class MDSCHEMA_MEMBERS:public Rowset 
{
public:
	MDSCHEMA_MEMBERS(Properties properties);
	virtual ~MDSCHEMA_MEMBERS();

	void serialize(SoapSerializer * SoapSer);
	bool processValue(Restrictions restrictions,Properties properties);
	void processProperties(Properties properties);
	
private:
	vector<Member*> getRestrictMembers(Restrictions &restrictions);
//	Row getRowC(calcMember * calc,int ordinal);
	Row getRowM(Measure* measure,int ordinal);
	string getParentUName(Member *member);
	string getMemberUName(Member *member);
//	vector<Level*> getRestrictLevel(Restrictions &restrictions);
//	Row getRowM(MeasureList measureList);
	Row getRow(Member *member);

	void string_replace(string & strBig, const string & strsrc, const string &strdst) {
    string::size_type pos=0;
    string::size_type srclen=strsrc.size();
    string::size_type dstlen=strdst.size();
    while( (pos=strBig.find(strsrc, pos)) != string::npos){
          strBig.replace(pos, srclen, strdst);
          pos += dstlen;
    }
}
	//transform "[Promotion Media].[(All)]" to "(All)"
	void handleString(string &str)
	{
		if(str=="")
			return;

		int last=str.rfind('.');

		//can find the '.'
		if(last!=string::npos){
			str=str.substr(last+1,str.size()-last);
		}
	
		string_replace(str,"[","");
		string_replace(str,"]","");
	}

};

#endif // !defined(AFX_MDSCHEMA_MEMBERS_H__E5F98505_60CB_45AB_AADF_CFE51539AF5D__INCLUDED_)
