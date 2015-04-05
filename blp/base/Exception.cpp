//Exception.cpp
#include "Exception.h"

using namespace blp;

CException::CException(int errCode, const char* szErrMsg, const char* szFile, const int iLine) throw()
					:_errCode(errCode), _errMsg(szErrMsg), _file(szFile ? szFile : ""), _line(iLine)
{

}

CException::CException(int errCode, const std::string& strErrMsg, const char* szFile, const int iLine) throw()
					:_errCode(errCode), _errMsg(strErrMsg), _file(szFile ? szFile : ""), _line(iLine)
{

}

CException::~CException() throw()
{

}

const char* CException::what() const throw()
{
	return _errMsg.c_str();
}