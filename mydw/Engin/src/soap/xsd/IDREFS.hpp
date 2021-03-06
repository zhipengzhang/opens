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

#if !defined(_IDREFS_HPP____OF_AXIS_INCLUDED_)

#define _IDREFS_HPP____OF_AXIS_INCLUDED_

#include "IDREF.hpp"

using namespace std;

class IDREFS : public IDREF {

public:
	/**
	 * Constructor
	 */
	IDREFS();
    /**
     * Constructor providing a value for later serialization
     * @param value The value to be serialized
     */
    IDREFS(const xsd__IDREFS value);
    /**
     * Get the xsd type of this simple type.
     * @return the xsd type of this simple type
     */
    XSDTYPE getType();
    /**
     * Get the deserialized value.
     * @return Deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__IDREFS getIDREFS();
    /**
     * Get the deserialized value
     * @return the deserialized value. Note: it is the responsibility of the calling code to delete this value!
     */
    void* getValue();

protected:
    /**
     * Deserialized IDREFS value from it's on-the-wire string form.
     * @param valueAsChar Serialized form of IDREFS value.
     * @return Deserialized IDREFS value. Note: it is the responsibility of the calling code to delete this value!
     */
    xsd__IDREFS deserializeIDREFS(const AxisChar* valueAsChar) throw (AxisSoapException);

};


#endif

