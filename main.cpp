#include <application.h>

// Need argc and argv for windows compatibility
int main(int argc, char *argv[])
{
    // Gets rid of useless warnings
    (void)argc;
    (void)argv;

    constexpr int WIDTH = 1920 * 0.5;
    constexpr int HEIGHT = 1080 * 0.5;

    // Type determines the quality of the audio float < double
    auto &app = APPLICATION<float>::instance(WIDTH, HEIGHT);
    app.run();
    return 0;
}