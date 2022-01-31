#include <Application.h>

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int WINDOW_SCALE = 3;
int main(int argc, char *argv[])
{
    if (Application::Singleton().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_SCALE))
    {
        Application::Singleton().Run();
    }
    return 0;
}
