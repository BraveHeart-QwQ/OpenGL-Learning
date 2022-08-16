#include <iostream>
#include <string>

// NOTE 选用不同文件夹的代码时，这个也要改
#include "Practice/LearnOpengl/1_HelloTriangle_1/Practice.hpp"

using namespace std;

int main(int argc, const char* argv[])
{
	learngl_practice::DrawMoreTriangle foobar;
	foobar.RealMain(argc, argv);
}
