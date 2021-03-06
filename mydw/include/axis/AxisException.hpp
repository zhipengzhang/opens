/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 *
 */

/**
 * @file AxisException.hpp
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#ifndef __AXISEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISEXCEPTION_H_OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <string>
#include <exception>
#include <new>
#include <typeinfo>
#include <stdexcept>

using namespace std;

/*
 * The following enumeration is used to serve the Axis C++ codes for 
 * faults.
 */
#define CLIENT_FAULT_OFFSET      0x0
#define SERVER_FAULT_OFFSET      0x1000
#define SOAP_FAULT_OFFSET        0x2000
#define ENGINE_FAULT_OFFSET      0x3000
#define WSDD_FAULT_OFFSET        0x4000
#define TRANSPORT_FAULT_OFFSET   0x5000
#define CONFIG_FAULT_OFFSET      0x6000
#define AXISC_FAULT_OFFSET       0x7000

typedef enum 
{
    /*The notation used for naming these exceptions is as follows
     *CLIENT at the beginning means when this interpreted as a soap fault
     *    it's fault code is CLIENT
     *SERVER at the beginning means when this interpreted as a soap fault
     *    it's fault code is SERVER
     *SOAP that comes next to CLIENT/SERVER means this is a soap releated
     *    exception
     *ENGINE that comes next to CLIENT/SERVER means this is a axisc++ engine
     *    related exception
     *WSDD that comes next to CLIENT/SERVER means this is a wsdd releated
     *    exception
     *TRANSPORT that comes next to CLIENT/SERVER means this is a transport releated
     *    exception
     *CONFIG that comes next to CLIENT/SERVER means this is a axisc++ configuration
     *    related exception
     *AXISC ?
     */
    /* SOAP faults */
/*0*/    SOAP_VERSION_MISMATCH, /* VersionMismatch faults */
/*1*/    SOAP_MUST_UNDERSTAND,    /* MustUnderstand faults */

    /* Client faults */
/*2*/    CLIENT_SOAP_MESSAGE_INCOMPLETE,
/*3*/    CLIENT_SOAP_SOAP_ACTION_EMTPY,
/*4*/    CLIENT_SOAP_SOAP_CONTENT_ERROR,
/*5*/    CLIENT_SOAP_NO_SOAP_METHOD,
/*6*/    CLIENT_SOAP_CONTENT_NOT_SOAP,
/*7*/    CLIENT_WSDD_SERVICE_NOT_FOUND,
/*8*/    CLIENT_WSDD_METHOD_NOT_ALLOWED,
/*9*/    CLIENT_WSDD_PARA_TYPE_MISMATCH,
/*10*/   CLIENT_ENGINE_CLIENT_HANDLER_FAILED,
/*11*/   CLIENT_TRANSPORT_EXCEPTION,
/*12*/   CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED,
/*13*/   CLIENT_TRANSPORT_TYPE_MISMATCH,
/*14*/   CLIENT_TRANSPORT_HAS_NO_UNSECURE_TRANSPORT_LAYER,
/*15*/   CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER,
/*16*/   CLIENT_SSLCHANNEL_RECEPTION_EXCEPTION,
/*17*/   CLIENT_SSLCHANNEL_SENDING_EXCEPTION,
/*18*/   CLIENT_SSLCHANNEL_CHANNEL_INIT_ERROR,
/*19*/   CLIENT_SSLCHANNEL_SOCKET_CREATE_ERROR,
/*20*/   CLIENT_SSLCHANNEL_SOCKET_CONNECT_ERROR,
/*21*/   CLIENT_SSLCHANNEL_INVALID_SOCKET_ERROR,
/*22*/   CLIENT_SSLCHANNEL_CONTEXT_CREATE_ERROR,
/*23*/   CLIENT_SSLCHANNEL_ERROR,
/*24*/   CLIENT_MIME_CONTENT_ID_NOT_UNIQUE,

    /* Server faults */
/*25*/    SERVER_ENGINE_EXCEPTION,
/*26*/    SERVER_ENGINE_COULD_NOT_LOAD_SRV,
/*27*/    SERVER_ENGINE_COULD_NOT_LOAD_HDL,
/*28*/    SERVER_ENGINE_LOADING_TRANSPORT_FAILED,
/*29*/    SERVER_ENGINE_LOADING_PARSER_FAILED,
/*30*/    SERVER_ENGINE_HANDLER_FAILED,
/*31*/    SERVER_ENGINE_WEBSERVICE_FAILED,
/*32*/    SERVER_ENGINE_HANDLER_INIT_FAILED,
/*33*/    SERVER_ENGINE_HANDLER_CREATION_FAILED,
/*34*/    SERVER_ENGINE_LIBRARY_LOADING_FAILED,
/*35*/    SERVER_ENGINE_HANDLER_NOT_LOADED,
/*36*/    SERVER_ENGINE_HANDLER_BEING_USED,
/*37*/    SERVER_ENGINE_GET_HANDLER_FAILED,
/*38*/    SERVER_ENGINE_WRONG_HANDLER_TYPE,
/*39*/    SERVER_CONFIG_EXCEPTION,
/*40*/    SERVER_CONFIG_TRANSPORT_CONF_FAILED,
/*41*/    SERVER_CONFIG_LIBRARY_PATH_EMPTY,
/*42*/    SERVER_WSDD_FILE_NOT_FOUND,
/*43*/    SERVER_WSDD_EXCEPTION,
/*44*/    SERVER_WSDD_NO_HANDLERS_CONFIGURED,
/*45*/    SERVER_SOAP_EXCEPTION,
/*46*/    SERVER_TRANSPORT_EXCEPTION,
/*47*/    SERVER_TRANSPORT_RECEPTION_EXCEPTION,
/*48*/    SERVER_TRANSPORT_SENDING_EXCEPTION,
/*49*/    SERVER_TRANSPORT_PROCESS_EXCEPTION,
/*50*/    SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
/*51*/    SERVER_TRANSPORT_HTTP_EXCEPTION,
/*52*/    SERVER_TRANSPORT_UNEXPECTED_STRING,
/*53*/    SERVER_TRANSPORT_CHANNEL_INIT_ERROR,
/*54*/    SERVER_TRANSPORT_SOCKET_CREATE_ERROR,
/*55*/    SERVER_TRANSPORT_SOCKET_CONNECT_ERROR,
/*56*/    SERVER_TRANSPORT_INVALID_SOCKET,
/*57*/    SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR,
/*58*/    SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
/*59*/    SERVER_TRANSPORT_TIMEOUT_EXCEPTION,
/*60*/    SERVER_TRANSPORT_TIMEOUT_EXPIRED,
/*61*/    SERVER_TRANSPORT_LOADING_SSLCHANNEL_FAILED,
/*62*/    SERVER_TRANSPORT_LOADING_CHANNEL_FAILED,
/*63*/    SERVER_TRANSPORT_BUFFER_EMPTY,
/*64*/    SERVER_PARSE_BUFFER_EMPTY,
/*65*/    SERVER_PARSE_PARSER_FAILED, 
/*66*/    SERVER_PARSE_TRANSPORT_FAILED,
/*67*/    SERVER_TEST_EXCEPTION,
/*68*/    SERVER_UNKNOWN_ERROR,
/*69*/    SERVER_CLIENT_ENGINE_MISMATCH,

    /* AXIS C faults */
    /*Following exceptions are not releated to soap faults
     */
/*70*/    AXISC_SERVICE_THROWN_EXCEPTION,
/*71*/    AXISC_UNKNOWN_ELEMENT_EXCEPTION,
/*72*/    AXISC_NODE_VALUE_MISMATCH_EXCEPTION,
/*73*/    AXISC_READ_CONF_EXCEPTION,

    /* CONFIG faults */
    /*Following exceptions are releated to configuration faults
     */
/*74*/    CONFIG_DEFAULTS_ALREADY_SET,
    /*
     * This FAULT_LAST is not used as a fault code, but instead is used 
     * internaly in the code. Developers should not use this as a fault 
     * code.
     */
/*75*/    FAULT_LAST 
} AXISC_EXCEPTIONS;

/**
 *   @class AxisException
 *   @brief Base class for Axis C++ exception hierarchy.
 *
 *   This will act as the base class for Axis C++ exception hierarchy. 
 *   This is class is derived from the std c++ exception class. Derived
 *   from this class are AxisConfigExceptin, AxisSoapExceptin, AxisWsddException,
 *   AxisEngineException, AxisTransportException and AxisParseException.
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 */
class STORAGE_CLASS_INFO AxisException :public exception
{
public:
    /** No parameter constructor*/
    AxisException():m_iExceptionCode(0), m_sMessage(NULL){};

    /** This can be used to throw an exception with exception code which is
      * is defined in the AxisException.h file, under AXISC_EXCEPTIONS type.
      * An additional description of the exception could be appended.
      *
      * @param Exception code which is defined in the AxisException.h file,
      *  under AXISC_EXCEPTIONS type.
      * @param A char pointer that will point to an exception message.
      *
      * @example throw AxisException(AXISC_NODE_VALUE_MISMATCH_EXCEPTION, 
            "Some additional exception info");
      */
    AxisException(const int iExceptionCode, const char* pcMessage = NULL):m_iExceptionCode(iExceptionCode), m_sMessage(NULL)
    {
        setMessage(pcMessage);    
    }

    /** This can be used to throw an exception with another exception as a
      * parameter. One situation in which this can be used is when we catch
      * a standard exception like std::bad_alloc
      *
      * @param An exception class derived from std::exception
      *
      * @example throw AxisException(std::bad_alloc);
      */
    AxisException(const AxisException& e):m_iExceptionCode(e.m_iExceptionCode), m_sMessage(NULL)
    {
        setMessage(e.m_sMessage);
    };
    
    /** Destructor */
    virtual ~AxisException() throw()
    {
        if (m_sMessage)
            delete [] m_sMessage;
    };

    /** This method is defined in std::exception. AxisException and derived
      * classes will override this to print exception messages
      */
    virtual const char* what() const throw() { return m_sMessage; };

    /** This can be called to get the exception code. */
    virtual const int getExceptionCode() const { return m_iExceptionCode; }

    /** This can be called to set the exception code */
    void setExceptionCode(int exceptionCode) { m_iExceptionCode = exceptionCode;}

    /** Get error message text - deprecated, use what() */
    const char* getMessage() const { return what(); }
    
    /**
      * The method setMessage(std::string psMessage) uses to set the private data member m_sMessage
      * This method should be used to set the m_sMessage variable in derived classes.
      */
    void setMessage(const char* psMessage)
    {
        if (m_sMessage)
        {
            delete [] m_sMessage;
            m_sMessage = NULL;
        }

        if (psMessage)
        {
            m_sMessage = new char[strlen(psMessage) + 1];
            strcpy(m_sMessage,psMessage);
        }        
    }
    
    /** The method will set exception data from another exception */
    void setExceptionFromException(const AxisException& e)
    {
        m_iExceptionCode = e.m_iExceptionCode;
        setMessage(e.m_sMessage);
    }

    /**
      * The method will reset exception object as if no parameters
      * where passed to constructor
      */
    void resetException()
    {
        m_iExceptionCode = 0;
        setMessage((const char *)NULL);
    }

protected:
    /**
      * This data member is common to all the inherited classes of this base class.
      * The integer variable m_iExceptionCode stores the Exception code
      */
    int m_iExceptionCode;

    /**
      * This data member is common to all the inherited classes of this base class.
      * The char* variable m_sMessage is used to store the Exception message
      * Whenever you want to set this variable use method setMessage(std::string psMessage)
      */
    char* m_sMessage;
};

#endif

