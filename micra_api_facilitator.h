#ifndef MICRA_API_FACILITATOR_H
#define MICRA_API_FACILITATOR_H

#ifdef __c
#error "C desteği bulunmamaktadır."
#endif

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <iostream>

struct MicraSHM {
    int fd;
    void* ptr;
    size_t size;
};

inline bool micra_shm_create(MicraSHM* shm, const char* name, size_t size) {
    shm->fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm->fd < 0) {
        std::cerr << "shm_open hatası: " << strerror(errno) << std::endl;
        return false;
    }

    if (ftruncate(shm->fd, size) < 0) {
        std::cerr << "ftruncate hatası: " << strerror(errno) << std::endl;
        close(shm->fd);
        return false;
    }

    shm->ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm->fd, 0);
    if (shm->ptr == MAP_FAILED) {
        std::cerr << "mmap hatası: " << strerror(errno) << std::endl;
        close(shm->fd);
        return false;
    }

    shm->size = size;
    return true;
}

inline void micra_shm_close(MicraSHM* shm) {
    if (shm->ptr) {
        munmap(shm->ptr, shm->size);
        shm->ptr = nullptr;
    }
    if (shm->fd > 0) {
        close(shm->fd);
        shm->fd = -1;
    }
}

inline void micra_shm_unlink(const char* name) {
    shm_unlink(name);
}

inline bool micra_shm_write(MicraSHM* shm, const void* data, size_t len) {
    if (!shm->ptr || len > shm->size) return false;
    memcpy(shm->ptr, data, len);
    return true;
}

inline bool micra_shm_read(MicraSHM* shm, void* buffer, size_t len) {
    if (!shm->ptr || len > shm->size) return false;
    memcpy(buffer, shm->ptr, len);
    return true;
}

inline bool micra_shm_write_string(MicraSHM* shm, const char* str) {
    return micra_shm_write(shm, str, strlen(str) + 1);
}

inline char* micra_shm_read_string(MicraSHM* shm) {
    if (!shm->ptr) return nullptr;
    return (char*)shm->ptr;
}

inline void* micra_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        std::cerr << "malloc hatası: " << strerror(errno) << std::endl;
    }
    return ptr;
}

inline void micra_free(void* ptr) {
    if (ptr) free(ptr);
}

#endif