//nocopyable.h
#ifndef BLP_BASE_NOCOPYABLE_H
#define BLP_BASE_NOCOPYABLE_H

namespace blp
{
class CNoCopyable
{
protected:
	CNoCopyable(){}
	~CNoCopyable(){}

	/* 阻止拷贝 */
private:
	CNoCopyable(const CNoCopyable&);
	const CNoCopyable& operator=(const CNoCopyable&);
};
}
#endif