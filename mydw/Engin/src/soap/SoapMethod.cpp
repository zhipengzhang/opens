#include "SoapMethod.h"

#include "Attribute.h"

#include <axis/GDefine.hpp>


int defSerMeth(void* rs, SoapSerializer *serializer, bool bArray){
	serializer->serialize(">\r\n",NULL);

	return AXIS_SUCCESS;
}


SoapMethod::SoapMethod()
{
	setReturn(true);
	return;
}

SoapMethod::~SoapMethod()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "~SoapMethod", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    /*for (list<Attribute*>::iterator it = m_attributes.begin();
         it != m_attributes.end(); it++)
    {
        delete (*it);
    }*/
	list<Attribute*>::iterator it;
	for (it = m_attributes.begin();
    it != m_attributes.end(); it++)
    {
		if(*it)
			delete (*it);
    }
    clearOutParams();
	m_attributes.clear();
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "~SoapMethod", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

void SoapMethod::setPrefix(const AxisChar* prefix)
{
    m_strPrefix = prefix;
	
		return;
}

void SoapMethod::setLocalName(const AxisChar* localname)
{
    m_strLocalname = localname;
		return;
}

void SoapMethod::setURI(const AxisChar* uri)
{
    m_strUri = uri;
	
	return;
}

void SoapMethod::addOutputParam(Param param)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "addOutputParam", this, 1,
					TRACETYPE_POINTER, sizeof(Param), ((void*)&param));	  /* AUTOINSERTED TRACE */
	#endif

//   if (param)
//    {
		//set the default pDZFunct if pDZFunct is null
		if(param.m_Type==USER_TYPE&&!param.m_Value.pCplxObj->pSZFunct)
			param.m_Value.pCplxObj->pSZFunct=(AXIS_SERIALIZE_FUNCT)(void *)defSerMeth;
			
		m_OutputParams.push_back(param);
//    }
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "addOutputParam", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

int SoapMethod::serialize(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "serialize", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif
    
    int iStatus= AXIS_SUCCESS;
    do
    {
        if(isSerializable())
        {
                    
            pSZ.serialize("<", m_strPrefix.c_str(), ":", m_strLocalname.c_str(),
                " xmlns:", m_strPrefix.c_str(),
                "=\"", m_strUri.c_str(), "\"", NULL);
			list<AxisChar*> lstTmpNameSpaceStack;
            iStatus= serializeAttributes(pSZ, lstTmpNameSpaceStack);
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
            
            pSZ.serialize(">\r\n", NULL);
            // push the current NS to the NS stack
            pSZ.getNamespacePrefix(m_strUri.c_str());
			
			/*llh 07-05-23*/
			if(isReturn()){
				pSZ.serialize("<",m_strPrefix.c_str(),":return xmlns:xsi=\"http:\//www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http:\//www.w3.org/2001/XMLSchema\">\r\n",NULL);
			}
			/*llh 07-05-23*/
			if(!m_OutputParams.empty())
				iStatus= serializeOutputParam(pSZ);

			/*llh 07-05-23*/
			if(isReturn()){
				pSZ.serialize("</",m_strPrefix.c_str(),":return>\r\n",NULL);
			}
			/*llh 07-05-23*/

            // remove the current NS from the NS stack
            pSZ.removeNamespacePrefix(m_strUri.c_str());
            if(iStatus==AXIS_FAIL)
            {
                break;
            }
            
            pSZ.serialize("</", NULL);
            if(m_strPrefix.length() != 0)
            {                    
                pSZ.serialize(m_strPrefix.c_str(), ":", NULL);
            }
            
            pSZ.serialize(m_strLocalname.c_str(), ">\r\n", NULL);
			// Removing the namespace list of this SOAPMethod from the stack.
			list<AxisChar*>::iterator itCurrentNamespace = 
				lstTmpNameSpaceStack.begin();
			while (itCurrentNamespace != lstTmpNameSpaceStack.end())
			{
				pSZ.removeNamespacePrefix(*itCurrentNamespace);
				itCurrentNamespace++;
			}
            iStatus= AXIS_SUCCESS;
        }
        else
        {
            iStatus= AXIS_FAIL;
        }
    } while(0);
            
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (iStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "serialize", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return iStatus;
		#endif
	}
}

int SoapMethod::serializeOutputParam(SoapSerializer& pSZ)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "serializeOutputParam", this, 1,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ));	  /* AUTOINSERTED TRACE */
	#endif
    
    int nStatus;
    for (list<Param>::iterator it = m_OutputParams.begin();
    it != m_OutputParams.end(); it++)
    {
        if (AXIS_SUCCESS != (nStatus = (*it).serialize(pSZ)))
        {
            	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (nStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "serializeOutputParam", this, 1,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return nStatus;
		#endif
	}

        }
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "serializeOutputParam", this, 2,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
}

const AxisChar* SoapMethod::getMethodName()
{
	
			return m_strLocalname.c_str();
	

}

bool SoapMethod::isSerializable()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "isSerializable", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    bool bStatus= true;    
    // checking whether namespace qualified, if not return AXIS_FAIL 
    do
    {
        if(m_strPrefix.length() == 0)
        {            
            bStatus= false;        
            break;
        }
        else if(m_strUri.length() == 0)
        {
            bStatus= false;
            break;
        }
    } while(0);
    	{
		#ifdef ENABLE_AXISTRACE
			bool traceRet = (bStatus);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "isSerializable", this, 0,
					TRACETYPE_BOOL, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return bStatus;
		#endif
	}

}

int SoapMethod::addAttribute(Attribute *pAttribute)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "addAttribute", this, 1,
					TRACETYPE_POINTER, sizeof(Attribute), ((void*)&pAttribute));	  /* AUTOINSERTED TRACE */
	#endif

    m_attributes.push_back(pAttribute);
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "addAttribute", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}

}

int SoapMethod::serializeAttributes(SoapSerializer& pSZ, 
        list<AxisChar*>& lstTmpNameSpaceStack)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "serializeAttributes", this, 2,
					TRACETYPE_DATA, sizeof(SoapSerializer&), ((void*)&pSZ),
					TRACETYPE_DATA, sizeof(list<AxisChar* >&), ((void*)&lstTmpNameSpaceStack));	  /* AUTOINSERTED TRACE */
	#endif

    list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();
    while(itCurrAttribute != m_attributes.end())
    {        
        (*itCurrAttribute)->serialize(pSZ, lstTmpNameSpaceStack);
        itCurrAttribute++;        
    }    
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "serializeAttributes", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
	}
    
}

int SoapMethod::reset()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "reset", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    m_strUri = "";
    m_strLocalname = "";
    m_strPrefix = "";
    m_OutputParams.clear();
    m_attributes.clear();
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (AXIS_SUCCESS);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "reset", this, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return AXIS_SUCCESS;
		#endif
		}
}

void SoapMethod::clearOutParams()
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry("SoapMethod", "clearOutParams", this, 0);	  /* AUTOINSERTED TRACE */
	#endif

    if ( m_OutputParams.empty() )
        	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "clearOutParams", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
/*
    list<Param>::iterator itParam;
    for (itParam = m_OutputParams.begin(); 
         itParam != m_OutputParams.end(); itParam++)
  
    {
  		if(*itParam)
  			delete (*itParam);
      }*/
  
    m_OutputParams.clear();
	{
		#ifdef ENABLE_AXISTRACE
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit("SoapMethod", "clearOutParams", this, 0);	  /* AUTOINSERTED TRACE */
		#endif
		return;
	}
}

list<Param> SoapMethod::getParams(){
	
	return this->m_OutputParams;
}