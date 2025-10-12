#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 13; // Порт службы daytime
const char* SERVER_IP = "172.16.40.1";

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Ошибка создания сокета");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Отправляем пустой датаграммы для получения ответа
    if (sendto(sockfd, nullptr, 0, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка отправки");
        close(sockfd);
        return 1;
    }

    char buffer[1024];
    socklen_t len = sizeof(server_addr);
    ssize_t n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_addr, &len);
    if (n < 0) {
        perror("Ошибка приёма");
        close(sockfd);
        return 1;
    }

    buffer[n] = '\0';
    std::cout << "Ответ от сервера: " << buffer;

    close(sockfd);
    return 0;
}
