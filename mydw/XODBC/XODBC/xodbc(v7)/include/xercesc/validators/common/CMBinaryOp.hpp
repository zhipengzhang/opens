/*
 * Copyright 1999-2001,2004 The Apache Software Foundation.
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
 * $Id: CMBinaryOp.hpp,v 1.1 2007/05/22 02:39:55 linkun Exp $
 */

#if !defined(CMBINARYOP_HPP)
#define CMBINARYOP_HPP

#include <xercesc/validators/common/CMNode.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class CMStateSet;

class CMBinaryOp : public CMNode
{
public :
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    CMBinaryOp
    (
        const ContentSpecNode::NodeTypes type
        ,     CMNode* const              leftToAdopt
        ,     CMNode* const              rightToAdopt
        ,     MemoryManager* const       manager = XMLPlatformUtils::fgMemoryManager
    );
    ~CMBinaryOp();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const CMNode* getLeft() const;
    CMNode* getLeft();
    const CMNode* getRight() const;
    CMNode* getRight();


    // -----------------------------------------------------------------------
    //  Implementation of the public CMNode virtual interface
    // -----------------------------------------------------------------------
    bool isNullable() const;


protected :
    // -----------------------------------------------------------------------
    //  Implementation of the protected CMNode virtual interface
    // -----------------------------------------------------------------------
    void calcFirstPos(CMStateSet& toSet) const;
    void calcLastPos(CMStateSet& toSet) const;


private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLeftChild
    //  fRightChild
    //      These are the references to the two nodes that are on either side
    //      of this binary operation. We own them both.
    // -----------------------------------------------------------------------
    CMNode* fLeftChild;
    CMNode* fRightChild;

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CMBinaryOp(const CMBinaryOp&);
    CMBinaryOp& operator=(const CMBinaryOp&);
};

XERCES_CPP_NAMESPACE_END

#endif
