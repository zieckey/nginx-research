
#include "../libnginx/test_common.h"

int main(int argc, char** argv) {
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}


namespace
{
#ifdef WIN32
    struct OnAppExit
    {
        ~OnAppExit()
        {
            system("pause");
        }
    } __s_onexit_pause;
#endif
}
