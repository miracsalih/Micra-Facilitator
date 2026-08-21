#include "micra_facilitator.h"

int main() {
    start_sdl2(SDL_INIT_VIDEO);
    Screen screen;
    create_window(screen, "Test 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    create_renderer(screen, SDL_RENDERER_SOFTWARE);

    SDL_Event e;

    int angle = 0;
    int x, y;

    clear_renderer(screen);
    set_render_color(screen, {.r = 255, .g = 255, .b = 255, .a = 0});

    while(true) {
        SDL_PollEvent(&e);
        if (quit_press(e)) break;

        std::cout << get_delta_time() << std::endl;
    }

    quit_sdl2(screen);
    return 0;
}