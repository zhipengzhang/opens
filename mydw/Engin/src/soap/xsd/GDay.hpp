#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../../common/AxisTrace.h"
#endif
/* -*- C++ -*- */

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
 * @author Adrian Dick (adrian.dick@uk.ibm.com)
 *
 */

#if !defined(_GDAY_HPP____OF_AXIS_INCLUDED_)

#define _GDAY_HPP____OF_AXIS_INCLUDED_

#include "IAnySimpleType.hpp"

#include "constraints/MinInclusive.hpp"

#include "constraints/MinExclusive.hpp"

#include "constraints/MaxInclusive.hpp"

#include "constraints/MaxExclusive.hpp"

#include <ctime>

using namespace std;

class GDay : public IAnySimpleType {

public:
    /**
     * Constructor
     */
    GDay();
    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    GDay(const xsd__gDay* value);
    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();
    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__gDay* getGDay();
    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();

protected:
    /**
     * Deserialized GDay value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of GDay value.
     * @return Deserialized GDay value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__gDay* deserializeGDay(const AxisChar* valueAsChar) throw (AxisSoapException);
    /**
     * Serialize GDay value to it's on-the-wire string form.
     * @param value The GDay value to be serialized.
     * @return Serialized form of GDay value.
     */
    AxisChar* serialize(const xsd__gDay* value) throw (AxisSoapException);
    /**
     * Creates a MinInclusive object.  For the GDay type this is undefined, 
     * so an unset MinInclusive object is created.
     * @return MinInclusive object
     */
    MinInclusive* getMinInclusive();
    /**
     * Creates a MinExclusive object.  For the GDay type this is undefined, 
     * so an unset MinExclusive object is created.
     * @return MinExclusive object
     */
    MinExclusive* getMinExclusive();    
    /**
     * Creates a MaxInclusive object.  For the GDay type this is undefined, 
     * so an unset MaxInclusive object is created.
     * @return MaxInclusive object
     */
    MaxInclusive* getMaxInclusive();
    /**
     * Creates a MaxExclusive object.  For the GDay type this is undefined, 
     * so an unset MaxExclusive object is created.
     * @return MaxExclusive object
     */
    MaxExclusive* getMaxExclusive();    
    /**
     * Creates a WhiteSpace object to collapse whitespace
     * @return WhiteSpace object set to collapse whitespace
     */
    WhiteSpace* getWhiteSpace();

};


#endif

