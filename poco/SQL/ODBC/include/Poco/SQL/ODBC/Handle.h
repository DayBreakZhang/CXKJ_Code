//
// Handle.h
//
// Library: Data/ODBC
// Package: ODBC
// Module:  Handle
//
// Definition of Handle.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SQL_ODBC_Handle_INCLUDED
#define SQL_ODBC_Handle_INCLUDED


#include "Poco/SQL/ODBC/ODBC.h"
#include "Poco/SQL/ODBC/EnvironmentHandle.h"
#include "Poco/SQL/ODBC/ConnectionHandle.h"
#include "Poco/SQL/ODBC/ODBCException.h"
#include "Poco/SQL/ODBC/Utility.h"
#ifdef POCO_OS_FAMILY_WINDOWS
#include <windows.h>
#endif
#include <sqltypes.h>


namespace Poco {
namespace SQL {
namespace ODBC {


template <typename H, SQLSMALLINT handleType>
class Handle
/// ODBC handle class template
{
public:
	Handle(const ConnectionHandle& rConnection):
		_rConnection(rConnection),
		_handle(0)
			/// Creates the Handle.
	{
		if (Utility::isError(SQLAllocHandle(handleType,
			_rConnection,
			&_handle)))
		{
			throw ODBCException("Could not allocate statement handle.");
		}
	}

	~Handle()
		/// Destroys the Handle.
	{
		try
		{
#if defined(_DEBUG)
			SQLRETURN rc =
#endif
			SQLFreeHandle(handleType, _handle);
			// N.B. Destructors should not throw, but neither do we want to
			// leak resources. So, we throw here in debug mode if things go bad.
			poco_assert_dbg (!Utility::isError(rc));
		}
		catch (...)
		{
			poco_unexpected();
		}
	}

	operator const H& () const
		/// Const conversion operator into reference to native type.
	{
		return handle();
	}

	const H& handle() const
		/// Returns const reference to native type.
	{
		return _handle;
	}

private:
	Handle(const Handle&);
	const Handle& operator=(const Handle&);

	operator H& ()
		/// Conversion operator into reference to native type.
	{
		return handle();
	}

	H& handle()
		/// Returns reference to native type.
	{
		return _handle;
	}

	const ConnectionHandle& _rConnection;
	H _handle;

	friend class ODBCStatementImpl;
};


typedef Handle<SQLHSTMT, SQL_HANDLE_STMT> StatementHandle;
typedef Handle<SQLHDESC, SQL_HANDLE_DESC> DescriptorHandle;


} } } // namespace Poco::SQL::ODBC


#endif
