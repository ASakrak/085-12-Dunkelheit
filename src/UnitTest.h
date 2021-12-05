//Test

#pragma once

#ifndef UNITTEST_H
#define UNITTEST_H

#endif
#define IS_TRUE(x)                                                                    \
    {                                                                                 \
        if (!(x))                                                                     \
            std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; \
    }
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class UnitTest
{
public:
    UnitTest();
    //UnitTest(const char *str);
    //UnitTest(const UnitTest &other);
};

bool function1(int x)
{
    //using namespace std::placeholders; // for the _1, _2 placeholders
    //glutKeyboardFunc(std::bind(&Controller::OnKeyPress, &GLInput, _1, _2, _3));
}

void test_function1()
{

    IS_TRUE(!function1(1));
}

/*int main(void)
{

    test_function1();
}*/
