#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif
/* -*- C++ -*- */

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
 * @author  Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#include "AxisSoapException.h"

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_SOAP_EXCEPTION is assumed.
*/


AxisSoapException::AxisSoapException(const int iExceptionCode, const char* pcMessage):AxisException(iExceptionCode)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisSoapException", "AxisSoapException", this, 2,
					TRACETYPE_INT, 0, ((void*)&iExceptionCode),
					TRACETYPE_STRING, 0, ((void*)&pcMessage));	  /* AUTOINSERTED TRACE */
	#endif

   std::string sMessage = "";
	if (pcMessage) 
	{
		sMessage = string(pcMessage);
		getMessageForExceptionCode(iExceptionCode);
		m_sMessageForExceptionCode = getMessageForExceptionCode(iExceptionCode) + " " + sMessage;
		setMessage(m_sMessageForExceptionCode.c_str());
	}
	else
		setMessage(getMessageForExceptionCode(iExceptionCode).c_str());
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisSoapException", "AxisSoapException", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

AxisSoapException::AxisSoapException (const AxisSoapException& e):AxisException (e)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisSoapException", "AxisSoapException", this, 1,
					TRACETYPE_AXISEXCEPTION, sizeof(AxisSoapException&), ((void*)&e));	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisSoapException", "AxisSoapException", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

AxisSoapException::~AxisSoapException() throw ()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisSoapException", "~AxisSoapException", this, 0);	  /* AUTOINSERTED TRACE */
	#endif
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisSoapException", "~AxisSoapException", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

string AxisSoapException::getMessageForExceptionCode (const int iExceptionCode)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("AxisSoapException", "getMessageForExceptionCode", this, 1,
					TRACETYPE_INT, 0, ((void*)&iExceptionCode));	  /* AUTOINSERTED TRACE */
	#endif

    
	switch(iExceptionCode)
    {
        case SOAP_VERSION_MISMATCH :
            m_sMessageForExceptionCode = "AxisSoapException:Soap Version mismatch fault occurred";
            break;
        case SOAP_MUST_UNDERSTAND:
			m_sMessageForExceptionCode = "AxisSoapException:Soap Must understand fault occurred";
            break;
        case CLIENT_SOAP_MESSAGE_INCOMPLETE:
			m_sMessageForExceptionCode = "AxisSoapException:Received message is incomplete";
            break;
        case CLIENT_SOAP_SOAP_ACTION_EMTPY:
			m_sMessageForExceptionCode = "AxisSoapException:Soap action is empty";
            break;
        case CLIENT_SOAP_SOAP_CONTENT_ERROR:
			m_sMessageForExceptionCode = "AxisSoapException:Received content is faulty";
            break;
        case CLIENT_SOAP_NO_SOAP_METHOD:
			m_sMessageForExceptionCode = "AxisSoapException:Request method is not a soap method";
            break;
        case CLIENT_SOAP_CONTENT_NOT_SOAP:
			m_sMessageForExceptionCode = "AxisSoapException:Content is not a valid soap message";
            break;
        case CLIENT_MIME_CONTENT_ID_NOT_UNIQUE:
			m_sMessageForExceptionCode = "AxisSoapException:Content is not unique within the MIME message";
            break;
        default:
			m_sMessageForExceptionCode = "AxisSoapException:Unknown Soap Exception";
    }
    	{
		#ifdef ENABLE_AXISTRACE
			string traceRet = (m_sMessageForExceptionCode);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("AxisSoapException", "getMessageForExceptionCode", this, 0,
					TRACETYPE_STLSTRING, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return m_sMessageForExceptionCode;
		#endif
	}

}


