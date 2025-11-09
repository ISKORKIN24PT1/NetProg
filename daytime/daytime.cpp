#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Создание сокета
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Подготовка адресной структуры сервера
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13); // Порт службы daytime
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1");

    // Отправка пустого датаграмма для инициации ответа
    if (sendto(sock, nullptr, 0, 0, 
               (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Ошибка отправки" << std::endl;
        close(sock);
        return 1;
    }

    // Прием ответа
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    socklen_t server_len = sizeof(server_addr);
    
    ssize_t bytes_received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                     (sockaddr*)&server_addr, &server_len);
    
    if (bytes_received == -1) {
        std::cerr << "Ошибка приема" << std::endl;
    } else {
        buffer[bytes_received] = '\0';
        std::cout << "Время от сервера: " << buffer;
    }

    close(sock);
    return 0;
}
