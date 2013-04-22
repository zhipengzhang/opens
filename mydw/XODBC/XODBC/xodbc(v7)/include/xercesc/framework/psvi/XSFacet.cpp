/*
 * Copyright 2003,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Id: XSFacet.cpp,v 1.1 2007/05/22 02:39:13 linkun Exp $
 */

#include <xercesc/framework/psvi/XSFacet.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  XSFacet: Constructors and Destructor
// ---------------------------------------------------------------------------
XSFacet::XSFacet(XSSimpleTypeDefinition::FACET facetKind,
                 const XMLCh* const            lexicalValue,
                 bool                          isFixed,
                 XSAnnotation* const           annot,
                 XSModel* const                xsModel,
                 MemoryManager* const          manager)
    : XSObject(XSConstants::FACET, xsModel, manager)
    , fFacetKind(facetKind)
    , fIsFixed(isFixed)
    , fLexicalValue(lexicalValue)
    , fAnnotation(annot)
{
}

XSFacet::~XSFacet()
{
}

XERCES_CPP_NAMESPACE_END


