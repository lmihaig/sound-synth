#include <application.h>

#define WIDTH 1920 * 0.5
#define HEIGHT 1080 * 0.5

// need argc and argv for windows compatibility
int main(int argc, char *argv[])
{

    APPLICATION app(WIDTH, HEIGHT);
    app.run();
    return 0;
}