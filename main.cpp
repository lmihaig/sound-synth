#include <application.h>

// need argc and argv for windows compatibility
int main(int argc, char *argv[])
{
    constexpr int WIDTH = 1920 * 0.5;
    constexpr int HEIGHT = 1080 * 0.5;

    APPLICATION app(WIDTH, HEIGHT);
    app.run();
    return 0;
}