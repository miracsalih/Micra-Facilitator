#ifndef MICRA_FACILITATOR_H
#define MICRA_FACILITATOR_H

#ifdef __c
#error "C desteği bulunmamaktadır."
#endif

#include <iostream>
#include <SDL2/SDL.h>

typedef struct Key {
    bool n0, n1, n2, n3, n4, n5, n6, n7, n8, n9;
    bool a, b, c, d, e, f, g, h, i, j, k, l, m;
    bool n, o, p, q, r, s, t, u, v, w, x, y, z;
    bool up, down, left, right;
    bool space, shift, ctrl, alt;
    bool f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;
    bool escape, enter, tab, backspace;
    bool capslock, numlock, lctrl, rctrl, lshift, rshift, lalt, ralt;
    bool quit;
} Key;

typedef struct Mouse {
    int x, y;
    int dx, dy;
    bool left_button, right_button, middle_button;
    bool left_click, right_click, middle_click;
    int wheel_x;
    int wheel_y;
} Mouse;

typedef struct Button {
    int x, y;
    int w, h;
} Button;

typedef struct Screen {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Screen;

inline bool start_sdl2(const Uint32 flags) {
    if (SDL_Init(flags) != 0) {
        std::cerr << "Micra-Facilitator: SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline void destroy_screen(const Screen screen, const bool window = true, const bool renderer = true) {
    if (renderer) SDL_DestroyRenderer(screen.renderer);
    if (window) SDL_DestroyWindow(screen.window);
}

inline void quit_sdl2(const Screen screen) {
    if (screen.renderer) SDL_DestroyRenderer(screen.renderer);
    if (screen.window) SDL_DestroyWindow(screen.window);
    SDL_Quit();
}

[[nodiscard]] inline bool quit_press(const SDL_Event& e) {
    if (e.type == SDL_QUIT) {
        std::cerr << "Micra-Facilitator: Quit pressed." << std::endl;
        return true;
    }
    return false;
}

inline void delay(const Uint32 ms) { SDL_Delay(ms); }

inline bool create_window(Screen& screen, const char* title, int x, int y, int w, int h, Uint32 flags) {
    SDL_Window* win = SDL_CreateWindow(title, x, y, w, h, flags);

    if (!win) {
        std::cerr << "Micra-Facilitator: SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        screen.window = nullptr;
        return false;
    }

    screen.window = win;
    return true;
}

inline bool create_renderer(Screen& screen, const Uint32 flags, const int index = -1) {
    if (!screen.window) {
        std::cerr << "Micra-Facilitator: There are no windows at all!" << std::endl;
        return false;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(screen.window, index, flags);

    if (!renderer) {
        std::cerr << "Micra-Facilitator: SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        screen.renderer = nullptr;
        return false;
    }

    screen.renderer = renderer;
    return true;
}

inline void clear_renderer(const Screen screen, const SDL_Color color = {.r = 0, .g = 0, .b = 0, .a = 255}) {
    SDL_SetRenderDrawColor(screen.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(screen.renderer);
}

inline void set_render_color(const Screen screen, const SDL_Color color = {.r = 255, .g = 255, .b = 255, .a = 255}) {
    SDL_SetRenderDrawColor(screen.renderer, color.r, color.g, color.b, color.a);
}

inline Key scan_keyboard() {
    const uint8_t* state = SDL_GetKeyboardState(nullptr);
    Key key = {};

    key.n0 = state[SDL_SCANCODE_0];
    key.n1 = state[SDL_SCANCODE_1];
    key.n2 = state[SDL_SCANCODE_2];
    key.n3 = state[SDL_SCANCODE_3];
    key.n4 = state[SDL_SCANCODE_4];
    key.n5 = state[SDL_SCANCODE_5];
    key.n6 = state[SDL_SCANCODE_6];
    key.n7 = state[SDL_SCANCODE_7];
    key.n8 = state[SDL_SCANCODE_8];
    key.n9 = state[SDL_SCANCODE_9];

    key.a = state[SDL_SCANCODE_A];
    key.b = state[SDL_SCANCODE_B];
    key.c = state[SDL_SCANCODE_C];
    key.d = state[SDL_SCANCODE_D];
    key.e = state[SDL_SCANCODE_E];
    key.f = state[SDL_SCANCODE_F];
    key.g = state[SDL_SCANCODE_G];
    key.h = state[SDL_SCANCODE_H];
    key.i = state[SDL_SCANCODE_I];
    key.j = state[SDL_SCANCODE_J];
    key.k = state[SDL_SCANCODE_K];
    key.l = state[SDL_SCANCODE_L];
    key.m = state[SDL_SCANCODE_M];
    key.n = state[SDL_SCANCODE_N];
    key.o = state[SDL_SCANCODE_O];
    key.p = state[SDL_SCANCODE_P];
    key.q = state[SDL_SCANCODE_Q];
    key.r = state[SDL_SCANCODE_R];
    key.s = state[SDL_SCANCODE_S];
    key.t = state[SDL_SCANCODE_T];
    key.u = state[SDL_SCANCODE_U];
    key.v = state[SDL_SCANCODE_V];
    key.w = state[SDL_SCANCODE_W];
    key.x = state[SDL_SCANCODE_X];
    key.y = state[SDL_SCANCODE_Y];
    key.z = state[SDL_SCANCODE_Z];

    key.up = state[SDL_SCANCODE_UP];
    key.down = state[SDL_SCANCODE_DOWN];
    key.left = state[SDL_SCANCODE_LEFT];
    key.right = state[SDL_SCANCODE_RIGHT];

    key.space = state[SDL_SCANCODE_SPACE];

    key.lshift = state[SDL_SCANCODE_LSHIFT];
    key.rshift = state[SDL_SCANCODE_RSHIFT];
    key.shift = key.lshift || key.rshift;

    key.lctrl = state[SDL_SCANCODE_LCTRL];
    key.rctrl = state[SDL_SCANCODE_RCTRL];
    key.ctrl = key.lctrl || key.rctrl;

    key.lalt = state[SDL_SCANCODE_LALT];
    key.ralt = state[SDL_SCANCODE_RALT];
    key.alt = key.lalt || key.ralt;

    key.f1 = state[SDL_SCANCODE_F1];
    key.f2 = state[SDL_SCANCODE_F2];
    key.f3 = state[SDL_SCANCODE_F3];
    key.f4 = state[SDL_SCANCODE_F4];
    key.f5 = state[SDL_SCANCODE_F5];
    key.f6 = state[SDL_SCANCODE_F6];
    key.f7 = state[SDL_SCANCODE_F7];
    key.f8 = state[SDL_SCANCODE_F8];
    key.f9 = state[SDL_SCANCODE_F9];
    key.f10 = state[SDL_SCANCODE_F10];
    key.f11 = state[SDL_SCANCODE_F11];
    key.f12 = state[SDL_SCANCODE_F12];

    key.escape = state[SDL_SCANCODE_ESCAPE];
    key.enter = state[SDL_SCANCODE_KP_ENTER] || state[SDL_SCANCODE_RETURN];
    key.tab = state[SDL_SCANCODE_TAB];
    key.backspace = state[SDL_SCANCODE_BACKSPACE];
    key.capslock = state[SDL_SCANCODE_CAPSLOCK];
    key.numlock = state[SDL_SCANCODE_NUMLOCKCLEAR];

    return key;
}

inline Mouse scan_mouse(const SDL_Event& e) {
    int x, y;
    const Uint32 state = SDL_GetMouseState(&x, &y);

    Mouse mouse = {};
    mouse.x = x;
    mouse.y = y;

    mouse.left_button = (state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    mouse.right_button = (state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
    mouse.middle_button = (state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;

    static bool prev_left = false, prev_right = false, prev_middle = false;
    mouse.left_click = mouse.left_button && !prev_left;
    mouse.right_click = mouse.right_button && !prev_right;
    mouse.middle_click = mouse.middle_button && !prev_middle;
    prev_left = mouse.left_button;
    prev_right = mouse.right_button;
    prev_middle = mouse.middle_button;

    static int prev_x = 0, prev_y = 0;
    mouse.dx = x - prev_x;
    mouse.dy = y - prev_y;
    prev_x = x;
    prev_y = y;

    static int wheel_x = 0, wheel_y = 0;

    if (e.type == SDL_MOUSEWHEEL) {
        wheel_x = e.wheel.x;
        wheel_y = e.wheel.y;
    }

    mouse.wheel_x = wheel_x;
    mouse.wheel_y = wheel_y;

    return mouse;
}

inline Button create_button(const int x, const int y, const int w, const int h) {
    Button button = {.x = x, .y = y, .w = w, .h = h};
    return button;
}

inline bool button_in_button(const Button* a, const Button* b) {
    return (a->x < b->x + b->w && a->x + a->w > b->x &&
            a->y < b->y + b->h && a->y + a->h > b->y);
}

inline bool point_in_button(const Button* btn, const int x, const int y) {
    return (x >= btn->x && x <= btn->x + btn->w &&
            y >= btn->y && y <= btn->y + btn->h);
}

inline bool rect_in_button(const Button* a, const int x, const int y, const int w, const int h) {
    return (a->x < x + w && a->x + a->w > x &&
            a->y < y + h && a->y + a->h > y);
}

inline bool is_button_lclicked(const Button* btn, const Mouse* mouse) {
    return (mouse->left_click &&
            point_in_button(btn, mouse->x, mouse->y));
}

inline bool is_button_rclicked(const Button* btn, const Mouse* mouse) {
    return (mouse->right_click &&
            point_in_button(btn, mouse->x, mouse->y));
}

inline void present(const Screen screen) {
    SDL_RenderPresent(screen.renderer);
}

inline bool draw_pixelc(const Screen screen, const int x, const int y, const Uint32 c) {
    SDL_SetRenderDrawColor(screen.renderer,
        (c >> 24) & 0xFF,
        (c >> 16) & 0xFF,
        (c >> 8) & 0xFF,
        c & 0xFF);

    if (const int error = SDL_RenderDrawPoint(screen.renderer, x, y); error != 0) {
        std::cerr << "Micra-Facilitator: SDL_RenderDrawPoint Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline bool draw_pixel(const Screen screen, const int x, const int y) {
    if (const int error = SDL_RenderDrawPoint(screen.renderer, x, y); error != 0) {
        std::cerr << "Micra-Facilitator: SDL_RenderDrawPoint Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline bool draw_linec(const Screen screen, const int x1, const int y1, const int x2, const int y2, const Uint32 c) {
    SDL_SetRenderDrawColor(screen.renderer,
        (c >> 24) & 0xFF,
        (c >> 16) & 0xFF,
        (c >> 8) & 0xFF,
        c & 0xFF);

    if (const int error = SDL_RenderDrawLine(screen.renderer, x1, y1, x2, y2); error != 0) {
        std::cerr << "Micra-Facilitator: SDL_RenderDrawLine Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline bool draw_line(const Screen screen, const int x1, const int y1, const int x2, const int y2) {
    if (const int error = SDL_RenderDrawLine(screen.renderer, x1, y1, x2, y2); error != 0) {
        std::cerr << "Micra-Facilitator: SDL_RenderDrawLine Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline bool draw_rectc(const Screen screen, const SDL_Rect rect, const Uint32 c) {
    SDL_SetRenderDrawColor(screen.renderer,
        (c >> 24) & 0xFF,
        (c >> 16) & 0xFF,
        (c >> 8) & 0xFF,
        c & 0xFF);

    if (const int error = SDL_RenderDrawRect(screen.renderer, &rect); error != 0) {
        std::cerr << "Micra-Facilitator: SDL_RenderDrawRect Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline bool draw_rect(const Screen screen, SDL_Rect rect) {
    if (const int error = SDL_RenderDrawRect(screen.renderer, &rect); error != 0) {
        std::cerr << "Micra-Facilitator: SDL_RenderDrawRect Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline void draw_texture(const Screen screen, SDL_Texture* tex, const int x, const int y) {
    int w, h;
    SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(screen.renderer, tex, nullptr, &dest);
}

inline SDL_Texture* load_texture(const Screen screen, const char* path) {
    SDL_Surface* surf = SDL_LoadBMP(path);
    if (!surf) {
        std::cerr << "Micra-Facilitator: Load_Texture Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(screen.renderer, surf);
    SDL_FreeSurface(surf);
    return tex;
}

inline SDL_Surface* load_surface(const char* path) {
    SDL_Surface* surf = SDL_LoadBMP(path);
    if (surf == nullptr) {
        std::cerr << "Micra-Facilitator: Load_Surface Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return surf;
}

inline SDL_Texture* convert_texture(const Screen screen, SDL_Surface* surf) {
    SDL_Texture* tex = SDL_CreateTextureFromSurface(screen.renderer, surf);
    SDL_FreeSurface(surf);
    return tex;
}

inline float get_delta_time() {
    static Uint32 last = SDL_GetTicks();
    const Uint32 now = SDL_GetTicks();
    const float dt = (static_cast<float>(now) - static_cast<float>(last)) / 1000.0f;
    last = now;
    return dt;
}

inline int get_fps() {
    static int fps = 0;
    static Uint32 last = SDL_GetTicks();
    static int count = 0;
    count++;
    if (SDL_GetTicks() - last >= 1000) {
        fps = count;
        count = 0;
        last = SDL_GetTicks();
    }
    return fps;
}

#endif