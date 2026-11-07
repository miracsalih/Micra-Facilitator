/*
 * Micra-Facilitator/micra_facilitator.hpp
 * Copyright (C) 2026  Miraç Salih İşler
 *
 * Bu kütüphane özgür yazılımdır: GNU Kısıtlı Genel Kamu Lisansı'nın 
 * (GNU Lesser General Public License) Free Software Foundation tarafından 
 * yayımlanan koşulları altında (Lisansın 3. sürümü veya (isteğinize göre)
 * daha sonraki bir sürümü) yeniden dağıtabilir ve/veya değiştirebilirsiniz.
 *
 * Bu kütüphane, işe yarayacağı umuduyla dağıtılmaktadır, ancak HİÇBİR GARANTİ
 * VERİLMEZ; hatta TİCARİ ELVERİŞLİLİK veya BELİRLİ BİR AMACA UYGUNLUK
 * garantisi bile verilmez. Daha fazla ayrıntı için GNU Kısıtlı Genel Kamu
 * Lisansı'na bakın.
 *
 * Bu kütüphaneyle birlikte GNU Kısıtlı Genel Kamu Lisansı'nın bir kopyasını 
 * almış olmalısınız. Eğer almamışsanız, <https://www.gnu.org/licenses/> 
 * adresine bakın.
 */

#pragma once
#include <iostream>
#include <SDL2/SDL.h>

// ===== Key =====
struct Key {
    bool n0,n1,n2,n3,n4,n5,n6,n7,n8,n9;
    bool a,b,c,d,e,f,g,h,i,j,k,l,m;
    bool n,o,p,q,r,s,t,u,v,w,x,y,z;
    bool up,down,left,right;
    bool space,shift,ctrl,alt;
    bool f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12;
    bool escape,enter,tab,backspace;
    bool capslock,numlock,lctrl,rctrl,lshift,rshift,lalt,ralt;
    bool quit;

    inline void scan_keyboard() {
        const Uint8* s = SDL_GetKeyboardState(nullptr);
        this->n0=s[SDL_SCANCODE_0];             this->n1=s[SDL_SCANCODE_1];             this->n2=s[SDL_SCANCODE_2];
        this->n3=s[SDL_SCANCODE_3];             this->n4=s[SDL_SCANCODE_4];             this->n5=s[SDL_SCANCODE_5];
        this->n6=s[SDL_SCANCODE_6];             this->n7=s[SDL_SCANCODE_7];             this->n8=s[SDL_SCANCODE_8];
        this->n9=s[SDL_SCANCODE_9];             this->a=s[SDL_SCANCODE_A];              this->b=s[SDL_SCANCODE_B];
        this->c=s[SDL_SCANCODE_C];              this->d=s[SDL_SCANCODE_D];              this->e=s[SDL_SCANCODE_E];
        this->f=s[SDL_SCANCODE_F];              this->g=s[SDL_SCANCODE_G];              this->h=s[SDL_SCANCODE_H];
        this->i=s[SDL_SCANCODE_I];              this->j=s[SDL_SCANCODE_J];              this->k=s[SDL_SCANCODE_K];
        this->l=s[SDL_SCANCODE_L];              this->m=s[SDL_SCANCODE_M];              this->n=s[SDL_SCANCODE_N];
        this->o=s[SDL_SCANCODE_O];              this->p=s[SDL_SCANCODE_P];              this->q=s[SDL_SCANCODE_Q];
        this->r=s[SDL_SCANCODE_R];              this->s=s[SDL_SCANCODE_S];              this->t=s[SDL_SCANCODE_T];
        this->u=s[SDL_SCANCODE_U];              this->v=s[SDL_SCANCODE_V];              this->w=s[SDL_SCANCODE_W];
        this->x=s[SDL_SCANCODE_X];              this->y=s[SDL_SCANCODE_Y];              this->z=s[SDL_SCANCODE_Z];
        this->up=s[SDL_SCANCODE_UP];            this->down=s[SDL_SCANCODE_DOWN];        this->left=s[SDL_SCANCODE_LEFT];
        this->right=s[SDL_SCANCODE_RIGHT];      this->space=s[SDL_SCANCODE_SPACE];      this->lshift=s[SDL_SCANCODE_LSHIFT];
        this->rshift=s[SDL_SCANCODE_RSHIFT];    this->shift=this->lshift||this->rshift; this->lctrl=s[SDL_SCANCODE_LCTRL];
        this->rctrl=s[SDL_SCANCODE_RCTRL];      this->ctrl=this->lctrl||this->rctrl;    this->lalt=s[SDL_SCANCODE_LALT];
        this->ralt=s[SDL_SCANCODE_RALT];        this->alt=this->lalt||this->ralt;       this->f1=s[SDL_SCANCODE_F1];
        this->f2=s[SDL_SCANCODE_F2];            this->f3=s[SDL_SCANCODE_F3];            this->f4=s[SDL_SCANCODE_F4];
        this->f5=s[SDL_SCANCODE_F5];            this->f6=s[SDL_SCANCODE_F6];            this->f7=s[SDL_SCANCODE_F7];
        this->f8=s[SDL_SCANCODE_F8];            this->f9=s[SDL_SCANCODE_F9];            this->f10=s[SDL_SCANCODE_F10];
        this->f11=s[SDL_SCANCODE_F11];          this->f12=s[SDL_SCANCODE_F12];
        
        this->escape=s[SDL_SCANCODE_ESCAPE];
        this->enter=s[SDL_SCANCODE_KP_ENTER]||s[SDL_SCANCODE_RETURN];
        this->tab=s[SDL_SCANCODE_TAB];
        this->backspace=s[SDL_SCANCODE_BACKSPACE];
        this->capslock=s[SDL_SCANCODE_CAPSLOCK];
        this->numlock=s[SDL_SCANCODE_NUMLOCKCLEAR];
    }
};

// ===== Mouse =====
struct Mouse {
    int x = 0, y = 0;
    int dx = 0, dy = 0;
    bool left_button = false, right_button = false, middle_button = false;
    bool left_click = false, right_click = false, middle_click = false;
    int wheel_x = 0;
    int wheel_y = 0;

    inline void scan_mouse(const SDL_Event& e) {
        Uint32 state = SDL_GetMouseState(&this->x, &this->y);
        this->left_button   = (state & SDL_BUTTON(SDL_BUTTON_LEFT))   != 0;
        this->right_button  = (state & SDL_BUTTON(SDL_BUTTON_RIGHT))  != 0;
        this->middle_button = (state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;

        static bool pl=false, pr=false, pm=false;
        this->left_click   = this->left_button   && !pl;
        this->right_click  = this->right_button  && !pr;
        this->middle_click = this->middle_button && !pm;
        pl = this->left_button; pr = this->right_button; pm = this->middle_button;

        static int px=0, py=0;
        this->dx = x - px; this->dy = y - py;
        px = x; py = y;

        static int wx=0, wy=0;
        if (e.type == SDL_MOUSEWHEEL) { wx = e.wheel.x; wy = e.wheel.y; }
        this->wheel_x = wx; this->wheel_y = wy;
    }
};

// ===== Screen =====
struct Screen {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    Screen() = default;
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

    ~Screen() {
        if (renderer) { SDL_DestroyRenderer(renderer); renderer = nullptr; }
        if (window)   { SDL_DestroyWindow(window);     window = nullptr; }
    }

    inline bool create_window(const char* title, int x, int y, int w, int h, Uint32 flags) {
        if (this->window) {
            SDL_DestroyWindow(this->window);
            this->window = nullptr;
        }
        this->window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (!this->window) {
            std::cerr << "Micra: SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    }

    inline bool create_renderer(Uint32 flags, int index = -1) {
        if (!this->window) {
            std::cerr << "Micra: Pencere yok!" << std::endl;
            return false;
        }
        if (this->renderer) {
            SDL_DestroyRenderer(this->renderer);
            this->renderer = nullptr;
        }
        this->renderer = SDL_CreateRenderer(this->window, index, flags);
        if (!this->renderer) {
            std::cerr << "Micra: SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    }

    inline void quit_sdl2() {
        if (this->renderer) {
            SDL_DestroyRenderer(this->renderer);
            this->renderer = nullptr;
        }
        if (this->window) {
            SDL_DestroyWindow(this->window);
            this->window = nullptr;
        }
        SDL_Quit();
    }



    inline void clear_renderer() {
        if (!this->renderer) return;
        SDL_RenderClear(this->renderer);
    }

    inline void set_render_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        if (!this->renderer) return;
        SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
    }

    inline void set_render_color(unsigned int color) {
        Uint8 r = (color >> 16) & 0xFF;
        Uint8 g = (color >> 8) & 0xFF;
        Uint8 b = color & 0xFF;
        Uint8 a = (color >> 24) & 0xFF;
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }

    inline void present() {
        if (this->renderer) SDL_RenderPresent(this->renderer);
    }

    inline bool draw_pixel(int x, int y) {
        if (!this->renderer) return false;
        return SDL_RenderDrawPoint(this->renderer, x, y) == 0;
    }

    inline bool draw_line(int x1, int y1, int x2, int y2) {
        if (!this->renderer) return false;
        return SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2) == 0;
    }

    inline bool draw_rect(const SDL_Rect* rect) {
        if (!this->renderer) return false;
        return SDL_RenderDrawRect(this->renderer, rect) == 0;
    }

};

// ===== Event =====
struct Event {
    SDL_Event e;

    inline bool quit_press() {
        return this->e.type == SDL_QUIT;
    }
};

// ===== Button =====
struct Button {
    int x = 0, y = 0, w = 0, h = 0;

    Button() = default;
    Button(int xx, int yy, int ww, int hh) : x(xx), y(yy), w(ww), h(hh) {}
    ~Button() = default;

    inline bool in_button(const Button& button) {
        return (this->x < button.x + button.w && this->x + this->w > button.x &&
                this->y < button.y + button.h && this->y + this->h > button.y);
    }

    inline bool in_point(int x, int y) {
        return (x >= this->x && x <= this->x + this->w &&
                y >= this->y && y <= this->y + this->h);
    }

    inline bool in_rect(SDL_Rect& rect) {
        return (this->x < rect.x + rect.w && this->x + this->w > rect.x &&
                this->y < rect.y + rect.h && this->y + this->h > rect.y);
    }

    inline bool is_lclicked(const Mouse& mouse) {
        return mouse.left_click && in_point(mouse.x, mouse.y);
    }

    inline bool is_rclicked(const Mouse& mouse) {
        return mouse.right_click && in_point(mouse.x, mouse.y);
    }
};



inline bool start_sdl2(Uint32 flags) {
    if (SDL_Init(flags) != 0) {
        std::cerr << "Micra-Facilitator: SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

inline void delay(Uint32 ms) { SDL_Delay(ms); }
