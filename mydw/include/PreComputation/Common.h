/**
 * @file Common.h
 *
 * 通用类文件
 *
 * @author DBNCLab
 * Copyright(c) 2007 by School Of Computer Science & Engineering, South China University of Technology, Guangzhou, Guangdong, P.R.C. 
 *
 */

#ifndef _COMMON_H_INCLUDE__
#define _COMMON_H_INCLUDE__

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#pragma warning(disable: 4503)
#endif

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>	
#include <list>

#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include <assert.h>

using namespace std;

namespace PreCmpt{

static clock_t tstart = 0; 
static double count = 0;
inline void Settime()
{
	tstart = clock();
}

inline double Gettime()
{
	return (double)((double)clock() - (double)tstart)/
		(double)CLOCKS_PER_SEC;
}

inline string ftos( double f )
{
	ostringstream o;
	o << f;
	return o.str();
}

inline double stof( const string& s )
{
	double result;
	istringstream(s) >> result;
	return result;
}	

/* convert a string to an integer */
inline int stoi( const string& s )
{
	int result;
	istringstream(s) >> result;
	return result;
}

/* convert an integer to a string */
inline string itos(int n)
{
	ostringstream o;
	o << n;
	return o.str();
}

inline string toLower(string rhs)
{
	const size_t size = rhs.size();
	
	std::string result = rhs;
	for(int i=0;i<size;i++)
	{
		if(rhs[i]>='A'&&rhs[i]<='Z')
		{
			result[i]='a'+rhs[i]-'A';
		}
	}
	
	return result;
}

inline vector<string> splitString( const std::string& str, const char* separator )
{
	vector<string> result;
	string::size_type prev_pos = 0;
	string::size_type pos = 0;
	while ( (pos = str.find_first_of(separator,prev_pos)) != string::npos )
	{
		if ( prev_pos < pos )
		{
			result.push_back(str.substr(prev_pos,pos-prev_pos));
		}
		prev_pos = pos + 1;
	}

	if ( prev_pos < str.size() )
	{
		result.push_back(str.substr(prev_pos));
	}

	return result;
}


};
#endif