#include "inc.h"
#include <string>
#include <iostream>

using namespace blp;
using namespace std;

void stringUtilTest()
{
	string src = "abcdefghijklmno|pqrstuvwxyz";
	//remove_last
	cout << "src:" << src << endl;
	CStringUtil::remove_last(src, '|');
	cout << "remove_last:" << src << endl;
	cout << "==================" << endl;

	cout << "src:" << src << endl;
	CStringUtil::remove_last(src, "ef");
	cout << "remove_last:" << src << endl;
	cout << "==================" << endl;

	src = "abcdefghijklmnopqrstuvwsyz";
	cout << "src:" << src << endl;
	CStringUtil::to_upper(src);
	cout << "to_upper:" << src << endl;
	cout << "==================" << endl;

	cout << "src:" << src << endl;
	CStringUtil::to_lower(src);
	cout << "to_lower:" << src << endl;
	cout << "==================" << endl;

	src = "    " + src + "    " ;
	cout << "src:" << src << endl;
	CStringUtil::trim_left(src);
	cout << "trim_left:" << src << endl;
	cout << "==================" << endl;

	cout << "src:" << src << endl;
	CStringUtil::trim_right(src);
	cout << "trim_right:" << src << endl;
	cout << "==================" << endl;

	src = "    " + src + "    " ;
	cout << "src:" << src << endl;
	CStringUtil::trim(src);
	cout << "trim:" << src << endl;
	cout << "==================" << endl;

	cout << "src:" << src << endl;
	cout << "chr_index:" << CStringUtil::chr_index(src.c_str(), 'f') << endl;	
	cout << "==================" << endl;
	cout << "format_string:" << CStringUtil::format_string("src:%s", src.c_str()) << endl;

}