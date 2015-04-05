#ifndef _BLP_BASE_STRING_UTIL_H
#define _BLP_BASE_STRING_UTIL_H

#include <sstream>
#include <string>

namespace blp{
class CStringUtil
{
public:
	/** 删除字符串尾部从指定字符开始的内容
      * @src: 需要处理的字符串
      * @c: 分隔字符
      * @example:  如果str为“/usr/local/test/bin/”，而c为“/”，
      *            则处理后str变成“/usr/local/test/bin”
      */
    static void remove_last(std::string& src, char c);

    /** 删除字符串尾部从指定字符串开始的内容
      * @src: 需要处理的字符串
      * @sep: 分隔字符串
      * @example: 如果str为“/usr/local/test/bin/tt”，而sep为“/bin/”，
      *           则处理后str变成“/usr/local/test
      */
    static void remove_last(std::string& src, const std::string& sep);

    /** 将字符串中的所有小写字符转换成大写 */
    static void to_upper(char* src);
    static void to_upper(std::string& src);

    /** 将字符串中的所有大写字符转换成小写 */
    static void to_lower(char* src);    
    static void to_lower(std::string& src);

    /** 判断指定字符是否为空格或TAB符(\t)或回车符(\r)或换行符(\n) */
    static bool is_space(char c);
    
    /** 删除字符串首尾空格或TAB符(\t)或回车符(\r)或换行符(\n) */
    static void trim(char* src);
    static void trim(std::string& src);

    /** 删除字符串首部空格或TAB符(\t)或回车符(\r)或换行符(\n) */
    static void trim_left(char* src);
    static void trim_left(std::string& src);

    /** 删除字符串尾部空格或TAB符(\t)或回车符(\r)或换行符(\n) */
    static void trim_right(char* src);        
    static void trim_right(std::string& src);


    /***
      * 求得一个字符在字符串中的位置
      * @return 如果c在字符串中，则返回非负整数值，否则返回-1
      */
    static int chr_index(const char* str, char c);
    static int chr_rindex(const char* str, char c);

    /***
      * 通过格式化生成一个字符串
      * 请注意字符串的长度不能超过10240字节，否则会被截断
      * @return 返回生成的字符串
      */
    static std::string format_string(const char* format, ...) __attribute__((format(printf, 1, 2)));

    template <typename Any>
    std::string any2string(Any any)
    {
        std::stringstream s;
        s << any;
        return s.str();
    }
};
}
#endif