#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Создание сокета
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Подготовка адресной структуры сервера
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7); // Порт службы echo
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1");

    // Установка соединения
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Ошибка соединения" << std::endl;
        close(sock);
        return 1;
    }

    std::cout << "Подключено к серверу echo. Введите сообщение: ";
    
    // Чтение сообщения от пользователя
    std::string message;
    std::getline(std::cin, message);

    // Отправка сообщения
    ssize_t bytes_sent = send(sock, message.c_str(), message.length(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Ошибка отправки" << std::endl;
        close(sock);
        return 1;
    }

    // Прием ответа
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    
    ssize_t bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_received == -1) {
        std::cerr << "Ошибка приема" << std::endl;
    } else {
        buffer[bytes_received] = '\0';
        std::cout << "Ответ от сервера: " << buffer << std::endl;
    }

    close(sock);
    return 0;
}
