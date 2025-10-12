#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 7; // Порт службы echo
const char* SERVER_IP = "172.16.40.1";

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Ошибка создания сокета");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка подключения");
        close(sockfd);
        return 1;
    }

    std::string message;
    std::cout << "Введите сообщение для отправки: ";
    std::getline(std::cin, message);

    ssize_t sent = send(sockfd, message.c_str(), message.length(), 0);
    if (sent < 0) {
        perror("Ошибка отправки");
        close(sockfd);
        return 1;
    }

    char buffer[1024];
    ssize_t received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (received < 0) {
        perror("Ошибка приёма");
        close(sockfd);
        return 1;
    }

    buffer[received] = '\0';
    std::cout << "Ответ от сервера: " << buffer << std::endl;

    close(sockfd);
    return 0;
}
