//Lexical_cast.h
#ifndef _BLP_BASE_LEXICAL_CAST_H
#define _BLP_BASE_LEXICAL_CAST_H

#include <sstream>
#include <exception>
#include <typeinfo>

namespace blp
{
	/**
	 * @class lexical_cast类型转换异常
	 * @brief lexical_cast类型转换异常, 源类型无法转换成目标类型
	 */
	class bad_lexical_cast: public std::bad_cast
	{
	public:
		bad_lexical_cast() : source(&typeid(void)), target(&typeid(void))
		{
		}

		bad_lexical_cast(
				const std::type_info &source_type_arg,
				const std::type_info &target_type_arg) :
			source(&source_type_arg), target(&target_type_arg)
		{
		}

		const std::type_info &source_type() const
		{
			return *source;
		}
		const std::type_info &target_type() const
		{
			return *target;
		}

		virtual const char *what() const throw()
		{
			return "bad lexical cast: "
							"source type value could not be interpreted as target";
		}
		virtual ~bad_lexical_cast() throw()
		{
		}
		private:
			const std::type_info *source;
			const std::type_info *target;
	};

	/**
	* @fn lexical_cast
	* @brief 完成源类型和目标类型之间的转换
	*
	* @param arg 源类型值
	* @param bThrow 类型转换失败时是否抛出异常
	*
	* @return 目标类型值
	*/ 
	template<typename Target, typename Source>
	Target lexical_cast(Source arg, bool bThrow = false)
	{
		std::stringstream interpreter;
		Target result;

		if(!(interpreter << arg && interpreter >> result) && bThrow)
		{
			throw bad_lexical_cast(typeid(Source), typeid(Target));
		}

		return result;
	}

	/**
	* @fn lexical_cast
	* @brief 完成源类型和目标类型之间的转换
	*
	* @param s 源类型值
	* @param t 目标类型值
	*
	* @return 类型转换结果 0:成功 -1:失败
	*/ 
	template<typename Target, typename Source>
	int lexical_cast(Source s, Target& t)
	{
		std::stringstream interpreter;

		if(!(interpreter << s && interpreter >> t))
		return -1;

		return 0;
	}
}


#endif
