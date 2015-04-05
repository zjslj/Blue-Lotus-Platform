//Exception.h

#ifndef BLP_BASE_EXCEPTION_H
#define BLP_BASE_EXCEPTION_H
#include <string>
#include <exception>
#include <iostream>

namespace blp{
class CException:public::std::exception
{
public:
	explicit CException(int errCode, const char* szErrMsg, const char* szFile=NULL, const int iLine= 0) throw();
	
	explicit CException(int errCode, const std::string& strErrMsg, const char* szFile=NULL, const int iLine= 0) throw();

	virtual ~CException() throw();

	inline int error() const throw()
	{
		return _errCode;
	}

	virtual const char* what() const throw();

	inline int line() const throw()
	{
		return _line;
	}
	inline std::string file() const throw()
	{
		return _file;
	}

private:
	int _errCode;
	std::string _errMsg;
	std::string _file;
	int _line;
};
}

#endif 