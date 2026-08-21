# Micra-Facilitator

Micra-Facilitator, Micra platformu için geliştirilmiş bir yardımcı kütüphane koleksiyonudur. SDL2 tabanlı grafik işlemleri, soket üzerinden ağ iletişimi ve paylaşımlı bellek (shared memory) yönetimi için C++ başlık dosyaları içerir.

## 📦 İçerik

| Dosya | Açıklama |
|-------|----------|
| **`micra_facilitator.h`** | SDL2 ile grafik, klavye/fare girişi, buton ve texture yönetimi için temel facilitator |
| **`micra_2d_facilitator.h`** | 2D koordinat işlemleri, döndürme (rotation), açı hesaplamaları ve piksel manipülasyonu |
| **`micra-api.h++`** | Paylaşımlı bellek (POSIX shm) yönetimi - okuma/yazma, oluşturma ve bellek yönetimi |
| **`micra-socket.h++`** | TCP soket ile istemci/sunucu iletişimi, çoklu bağlantı yönetimi ve IP tabanlı mesajlaşma |

## 🚀 Kullanım

### 1. SDL2 Grafik ve Giriş İşlemleri

```cpp
#include "micra_facilitator.h"

Screen screen;
start_sdl2(SDL_INIT_VIDEO);
create_window(screen, "Pencere", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
create_renderer(screen, SDL_RENDERER_ACCELERATED);

SDL_Event e;
while (!quit_press(e)) {
    while (SDL_PollEvent(&e)) {
        Mouse mouse = scan_mouse(e);
        Key key = scan_keyboard();
        
        clear_renderer(screen);
        draw_pixel(screen, mouse.x, mouse.y);
        present(screen);
        
        if (key.escape) break;
    }
}

quit_sdl2(screen);
```

### 2. 2D İşlemler (Döndürme, Piksel)

```cpp
#include "micra_2d_facilitator.h"

// Piksel oluştur ve döndür
Pixel_2d px = create_pixel(100, 100, 0xFFFF00FF);
rotate_pixel(px, 400, 300, 150, 45);  // (cx, cy, mesafe, açı)

// Dikdörtgen piksel dizisi oluştur
std::vector<Pixel_2d> pixels = create_pixel(50, 50, 100, 100, 0x00FF00FF);
```

### 3. Soket İletişimi (İstemci/Sunucu)

```cpp
#include "micra-socket.h++"

// Sunucu olarak başlat
start_server(8080);
write("Merhaba istemci!");

char buffer[1024];
read(buffer, sizeof(buffer));

// İstemci olarak bağlan
connect("127.0.0.1", 8080);
write("Sunucuya mesaj");

// Çoklu istemci yönetimi
accept_clients(server_fd);
send_to_all("Herkese mesaj");
send_to_ip("192.168.1.100", "Belirli IP'ye mesaj");
list_clients();

quit();  // Bağlantıyı kapat
```

### 4. Paylaşımlı Bellek (Shared Memory)

```cpp
#include "micra-api.h++"

MicraSHM shm;
micra_shm_create(&shm, "/micra_shm", 1024);

// Yazma
micra_shm_write_string(&shm, "Merhaba Dünya!");

// Okuma
char buffer[256];
micra_shm_read(&shm, buffer, sizeof(buffer));
std::cout << "Okunan: " << buffer << std::endl;

// Kapat ve temizle
micra_shm_close(&shm);
micra_shm_unlink("/micra_shm");
```

## 🔧 Derleme

### SDL2 Bağımlılığı

Linux'ta SDL2'yi yükleyin:

```bash
sudo apt-get install libsdl2-dev
```

### Örnek Derleme

```bash
g++ -std=c++17 -o program main.cpp -lSDL2
```

Soket kullanımı için ekstra kütüphane gerekmez (POSIX standart).

## 📝 Notlar

- **`micra_facilitator.h`** ve **`micra_2d_facilitator.h`** C desteği içermez (`#error "C desteği bulunmamaktadır."`).
- **`micra-socket.h++`** ve **`micra-api.h++`** Linux/Unix sistemler için POSIX çağrıları kullanır (Windows desteği yoktur).
- Tüm fonksiyonlar `inline` olarak tanımlandığı için başlık dosyalarını doğrudan projene dahil edebilirsin.

## 📄 Lisans

Bu proje [LICENSE](LICENSE) dosyasında belirtilen lisans koşulları altında dağıtılmaktadır.

## 🤝 Katkıda Bulunma

Katkılarınızı bekliyoruz! Lütfen bir issue açın veya pull request gönderin.

---

**Not:** Depodaki dosyalar `micra_facilitator.h`, `micra_2d_facilitator.h` (C++), `micra-api.h++` ve `micra-socket.h++` olarak düzenlenmiştir. Tüm fonksiyonlar header-only olarak tasarlanmıştır.
