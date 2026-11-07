#include "micra_facilitator.hpp"
#include <SDL2/SDL_events.h>

int main() {
    start_sdl2(SDL_INIT_VIDEO);
    Screen screen;
    screen.create_window("Test 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    screen.create_renderer(SDL_RENDERER_SOFTWARE);

    unsigned int color;
    bool reverse = false;

    Event e;

    const int kalinlik = 20;

    while(true) {
        SDL_PollEvent(&e.e);
        if (e.quit_press()) break;

        screen.set_render_color(0);

        if (!reverse) color += 0x00010100; 
        else color -= 0x00010100;

        if ((color & 0xFFFFFF00) == 0xFFFFFF00) reverse = true;
        else if ((color & 0xFFFFFF00) == 0x00000000) reverse = false;

        screen.clear_renderer();
        screen.set_render_color(color);

        for (int size = kalinlik; size != 0; size--) {
            screen.draw_line(200+size, 200+size, 600+size, 200+size);
            screen.draw_line(600+size, 200+size, 600+size, 600+size);
            screen.draw_line(600+size, 600+size, 200+size, 600+size);
            screen.draw_line(200+size, 600+size, 200+size, 200+size);
        }
        screen.present();

        delay(10);
    }

    screen.quit_sdl2();
    return 0;
}
