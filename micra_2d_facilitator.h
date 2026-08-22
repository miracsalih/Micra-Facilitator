#ifndef MICRA_2D_FACILITATOR_H
#define MICRA_2D_FACILITATOR_H

#ifdef __c
#error "C desteği bulunmamaktadır."
#endif

#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

inline double convertMilad(double angle) { return angle * M_PI / 400.0; }

inline double cosMilad(double angle) {
    double radyan = convertMilad(angle);
    return cos(radyan);
}

inline double sinMilad(double angle) {
    double radyan = convertMilad(angle);
    return sin(radyan);
}

typedef struct Pixel_2d {
    int x, y;
    unsigned int color;
} Pixel_2d;

inline Pixel_2d create_pixel(const int x, const int y, const unsigned int color) { return {.x = x, .y = y, .color = color}; }

inline std::vector<Pixel_2d> create_pixel(const int x, const int y, const int w, const int h, const unsigned int color = 0x000000FF) {
    std::vector<Pixel_2d> pixel;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            pixel.push_back({.x = j + x, .y = i + y, .color = color});
        }
    }

    return pixel;
}

// Döndürme işlemi:

inline void rotate_pixel(Pixel_2d& pixel, const int cx, const int cy, const int mesafe, const int angle) {
    pixel.x = static_cast<int>(cx + mesafe * cosMilad(angle));
    pixel.y = static_cast<int>(cy + mesafe * sinMilad(angle));
}

inline void rotate_pixel(int& x, int& y, const int cx, const int cy, const int mesafe, const int angle) {
    x = static_cast<int>(cx + mesafe * cosMilad(angle));
    y = static_cast<int>(cy + mesafe * sinMilad(angle));
}

// Gelişmiş - Mesafe özel X ve Y ayarlı:

inline void rotate_pixel(Pixel_2d& pixel, const int cx, const int cy, const int mesafe_x, const int mesafe_y, const int angle) {
    pixel.x = static_cast<int>(cx + mesafe_x * cosMilad(angle));
    pixel.y = static_cast<int>(cy + mesafe_y * sinMilad(angle));
}

inline void rotate_pixel(int& x, int& y, const int cx, const int cy, const int mesafe_x, const int mesafe_y, const int angle) {
    x = static_cast<int>(cx + mesafe_x * cosMilad(angle));
    y = static_cast<int>(cy + mesafe_y * sinMilad(angle));
}

// Yansıma Açısı:

inline double ray_trace(const double angle) {
    return (1.0 * angle);
}

inline std::vector<double> ray_traces(const std::vector<double>& angle) {
    std::vector<double> rays;
    for (size_t i = 0; i < angle.size(); i++) {
        rays.push_back((1.0 * angle[i]));
    }
    return rays;
}

#endif
