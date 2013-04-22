/*
 * Copyright 2001,2004 The Apache Software Foundation.
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
 * $Id: XercesElementWildcard.hpp,v 1.1 2007/05/22 02:40:03 linkun Exp $
 */


#if !defined(XERCESELEMENTWILDCARD_HPP)
#define XERCESELEMENTWILDCARD_HPP

#include <xercesc/util/QName.hpp>
#include <xercesc/validators/common/ContentSpecNode.hpp>
#include <xercesc/validators/schema/SubstitutionGroupComparator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward declarations
// ---------------------------------------------------------------------------
class SchemaGrammar;


class VALIDATORS_EXPORT XercesElementWildcard
{

public :

    // -----------------------------------------------------------------------
    //  Class static methods
    // -----------------------------------------------------------------------
    /*
     * check whether two elements are in conflict
     */
    static bool conflict(SchemaGrammar* const         pGrammar,
                         ContentSpecNode::NodeTypes   type1,
                         QName*                       q1,
                         ContentSpecNode::NodeTypes   type2,
                         QName*                       q2,
                         SubstitutionGroupComparator* comparator);

private:

    // -----------------------------------------------------------------------
    //  private helper methods
    // -----------------------------------------------------------------------
    static bool uriInWildcard(SchemaGrammar* const         pGrammar,
                              QName*                       qname,
                              unsigned int                 wildcard,
                              ContentSpecNode::NodeTypes   wtype,
                              SubstitutionGroupComparator* comparator);

    static bool wildcardIntersect(ContentSpecNode::NodeTypes t1,
                                  unsigned int               w1,
                                  ContentSpecNode::NodeTypes t2,
                                  unsigned int               w2);

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XercesElementWildcard();
    ~XercesElementWildcard();
};

XERCES_CPP_NAMESPACE_END

#endif // XERCESELEMENTWILDCARD_HPP

