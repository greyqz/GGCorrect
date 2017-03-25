/* GGCorrect
 * Au: GG
 * ====================================
 * Thanks to http://bbs.csdn.net/topics/80416661
 * Thanks to http://blog.csdn.net/crazyer2010/article/details/9063847
 */

#define GGFILE_DIR_CODE "F:\\GGCorrect\\*.txt"

#include <stdio.h>
#include <io.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;


void string_replace(string &s1, const string &s2) // ,const string& s3
{
	string::size_type pos = 0;
	string::size_type a = s2.size();
	// string::size_type b = s3.size();
	while ((pos = s1.find(s2, pos)) != string::npos)
	{
		s1.erase(pos, a);
		// s1.insert(pos,s3);
		// pos += b;
	}
}

void ggFile(const char* path)
{
	ifstream in(path); // 打开txt
	stringstream ss;
	ss << in.rdbuf(); // 将文件整个buffer放到stringstream中
	string s;
	s = ss.str(); // 把ss整个作为一个string放入s，文件所有内容就在s中

	// ... 操作s
	string replace_char = "\n";
	string_replace(s, replace_char);
	replace_char = "\r";
	string_replace(s, replace_char);

	// 把s重新写回文件
	ofstream out(path);
	out << s;
	out.close();
	// 不需要out.close()，scope结束out析构会自动close()
}

int main (void)
{
	printf("GGCorrect: scanning...\n-------------------------\n\n");

	_finddata_t fileDir;
	char* dir = GGFILE_DIR_CODE;
	long lfDir;

	if ((lfDir = _findfirst(dir, &fileDir)) == -1l)
		printf("No file is found.\n");
	else {
		printf("File list:\n");
		do {
			printf("%s", fileDir.name);

			// Open file and replace
			ggFile(fileDir.name);
			printf("\t(fixed)\n");
			// fix

		} while ( _findnext( lfDir, &fileDir ) == 0 );
	}
	_findclose(lfDir);

	printf("\n-------------------------\n");
	system("pause");

	return 0;
}
