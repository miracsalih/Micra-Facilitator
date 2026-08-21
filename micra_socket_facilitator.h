#ifndef MICRA_SOCKET_FACILITATOR_H
#define MICRA_SOCKET_FACILITATOR_H

#ifdef __c
#error "C desteği bulunmamaktadır."
#endif

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <string>

#define PORT 8080
#define BUFFER_SIZE 1024

static int sockfd = -1;
static struct sockaddr_in addr;
static bool is_server = false;
static std::vector<std::string> connected_ips;

inline int start_client(const char* hedef_ip, int port = PORT) {
    if (sockfd != -1) {
        std::cerr << "[!] Zaten bağlantı var. Önce quit() çağırın." << std::endl;
        return -1;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "[!] Soket oluşturulamadı!" << std::endl;
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, hedef_ip, &addr.sin_addr) <= 0) {
        std::cerr << "[!] Geçersiz IP adresi!" << std::endl;
        close(sockfd);
        sockfd = -1;
        return -1;
    }

    if (connect(sockfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        std::cerr << "[!] Bağlantı başarısız! IP/Port kontrol edin." << std::endl;
        close(sockfd);
        sockfd = -1;
        return -1;
    }

    is_server = false;
    std::cout << "[+] İstemci başlatıldı ve " << hedef_ip << ":" << port << " adresine bağlandı." << std::endl;
    return 0;
}

inline int start_server(int port = PORT) {
    if (sockfd != -1) {
        std::cerr << "[!] Zaten bağlantı var. Önce quit() çağırın." << std::endl;
        return -1;
    }

    int server_fd;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "[!] Soket oluşturulamadı!" << std::endl;
        return -1;
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
        std::cerr << "[!] Bind başarısız!" << std::endl;
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "[!] Dinleme başarısız!" << std::endl;
        close(server_fd);
        return -1;
    }

    std::cout << "[+] Sunucu başlatıldı. Port: " << port << " - Bağlantı bekleniyor..." << std::endl;

    if ((sockfd = accept(server_fd, reinterpret_cast<struct sockaddr*>(&address), reinterpret_cast<socklen_t*>(&addrlen))) < 0) {
        std::cerr << "[!] Accept başarısız!" << std::endl;
        close(server_fd);
        sockfd = -1;
        return -1;
    }

    close(server_fd);
    is_server = true;
    std::cout << "[+] Bağlantı alındı!" << std::endl;
    return 0;
}

inline int connect(const char* hedef_ip, int port = PORT) {
    return start_client(hedef_ip, port);
}

inline int reconnect(const char* hedef_ip, int port = PORT) {
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }
    std::cout << "[*] Yeniden bağlanılıyor..." << std::endl;
    return start_client(hedef_ip, port);
}

inline int read(char* buffer, int buffer_size) {
    if (sockfd == -1) {
        std::cerr << "[!] Bağlantı yok! Önce start_server/start_client çağırın." << std::endl;
        return -1;
    }

    int bytes_read = recv(sockfd, buffer, buffer_size, 0);
    if (bytes_read < 0) {
        std::cerr << "[!] Okuma hatası!" << std::endl;
        return -1;
    } else if (bytes_read == 0) {
        std::cout << "[*] Bağlantı kapandı (karşı taraf kapattı)." << std::endl;
        close(sockfd);
        sockfd = -1;
        return 0;
    }

    buffer[bytes_read] = '\0';
    return bytes_read;
}

inline int write(const char* mesaj) {
    if (sockfd == -1) {
        std::cerr << "[!] Bağlantı yok! Önce start_server/start_client çağırın." << std::endl;
        return -1;
    }

    int bytes_sent = send(sockfd, mesaj, strlen(mesaj), 0);
    if (bytes_sent < 0) {
        std::cerr << "[!] Yazma hatası!" << std::endl;
        return -1;
    }

    return bytes_sent;
}

inline std::string get_client_ip() {
    if (sockfd == -1) return "0.0.0.0";

    socklen_t len = sizeof(addr);
    getpeername(sockfd, reinterpret_cast<struct sockaddr*>(&addr), &len);
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, ip, INET_ADDRSTRLEN);
    return std::string(ip);
}

inline void send_message_by_ip(const std::string& ip, const std::string& message) {
    std::string client_ip = get_client_ip();
    if (client_ip == ip) {
        write(message.c_str());
    }
}

inline void add_connection_ip(const std::string& ip) {
    connected_ips.push_back(ip);
}

inline void remove_connection_ip(const std::string& ip) {
    for (auto it = connected_ips.begin(); it != connected_ips.end(); ++it) {
        if (*it == ip) {
            connected_ips.erase(it);
            break;
        }
    }
}

inline void list_connected_ips() {
    std::cout << "[+] Bağlı IP'ler (" << connected_ips.size() << " adet):" << std::endl;
    for (size_t i = 0; i < connected_ips.size(); ++i) {
        std::cout << "    " << i+1 << ". " << connected_ips[i] << std::endl;
    }
}

static std::vector<int> client_sockets;
static std::vector<std::string> client_ips;

inline void accept_clients(int server_fd) {
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    while (true) {
        int new_socket = accept(server_fd, reinterpret_cast<struct sockaddr*>(&address), reinterpret_cast<socklen_t*>(&addrlen));
        if (new_socket < 0) break;

        // IP'yi al
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &address.sin_addr, ip, INET_ADDRSTRLEN);

        // Listeye ekle
        client_sockets.push_back(new_socket);
        client_ips.push_back(std::string(ip));

        std::cout << "[+] Yeni bağlantı: " << ip << std::endl;
    }
}

inline void send_to_all(const char* message) {
    for (int sock : client_sockets) {
        send(sock, message, strlen(message), 0);
    }
}

inline void send_to_ip(const std::string& ip, const char* message) {
    for (size_t i = 0; i < client_ips.size(); ++i) {
        if (client_ips[i] == ip) {
            send(client_sockets[i], message, strlen(message), 0);
            break;
        }
    }
}

inline void list_clients() {
    std::cout << "[+] Bağlı istemciler (" << client_sockets.size() << " adet):" << std::endl;
    for (size_t i = 0; i < client_ips.size(); ++i) {
        std::cout << "    " << i+1 << ". " << client_ips[i] << std::endl;
    }
}

inline int quit() {
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
        std::cout << "[+] Bağlantı kapatıldı." << std::endl;
    } else {
        std::cout << "[*] Zaten bağlantı yok." << std::endl;
    }
    return 0;
}

#endif