#include <iostream>
#include <string>

// CRITICAL 选用不同文件夹的代码时，这个也要改
//#include "Template/BasicVBO.hpp"
//#include "Template/BasicIBO.hpp"
//#include "Practice/LearnOpengl/Chapter1/DrawMoreTriangle.hpp"
//#include "Practice/LearnOpengl/Chapter1/DrawTwoTriangleInDiffVAOVBO.hpp"
//#include "Practice/LearnOpengl/Chapter1/DuoShaderProgram.hpp"
#include "OpenglLearning/Chapter2/FragmentInterpolation.hpp"


using namespace std;

int main(int argc, const char* argv[])
{
	learngl_ch2::FragmentInterpolation foobar;

	foobar.RealMain(argc, argv);
}
