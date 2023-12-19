#include <iostream>
#include <fstream>
#include <cstdio>

int main(){
    std::ofstream fout("b.txt"); //文件输出流对象
	std::streambuf* pOld = std::cout.rdbuf(fout.rdbuf());

	std::cout<<"我是sb"<< std::endl;
}