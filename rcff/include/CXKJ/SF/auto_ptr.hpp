
//******************************************************************************
// RCF - Remote Call Framework
//
// Copyright (c) 2005 - 2019, Delta V Software. All rights reserved.
// http://www.deltavsoft.com
//
// RCF is distributed under dual licenses - closed source or GPL.
// Consult your particular license for conditions of use.
//
// If you have not purchased a commercial license, you are using RCF 
// under GPL terms.
//
// Version: 3.1
// Contact: support <at> deltavsoft.com 
//
//******************************************************************************

#ifndef INCLUDE_SF_AUTO_PTR_HPP
#define INCLUDE_SF_AUTO_PTR_HPP

#include <memory>

#include <SF/SerializeSmartPtr.hpp>

namespace SF {

    // serialize std::auto_ptr
    SF_SERIALIZE_SIMPLE_SMARTPTR( std::auto_ptr );

} // namespace SF

#endif // ! INCLUDE_SF_AUTO_PTR_HPP
