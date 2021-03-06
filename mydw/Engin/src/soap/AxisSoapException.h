#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
 
#ifndef __AXISSOAPEXCEPTION_H_OF_AXIS_INCLUDED_

#define __AXISSOAPEXCEPTION_H_OF_AXIS_INCLUDED_

#include <string>

#include <axis/AxisException.hpp>


using namespace std;

class STORAGE_CLASS_INFO AxisSoapException :public AxisException
{

public:
    AxisSoapException(const int iExceptionCode,const char* pcMessage = NULL);
    AxisSoapException(const AxisSoapException& e);
    virtual ~AxisSoapException() throw();
    
private:
    string getMessageForExceptionCode(const int iExceptionCode);
	std::string m_sMessageForExceptionCode;

};


#endif

