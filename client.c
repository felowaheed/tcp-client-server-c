#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 12345
int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char buffer[1024];
    WSAStartup(MAKEWORD(2, 2), &wsa);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    InetPton(AF_INET, "127.0.0.1", &server.sin_addr);
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        return 1;
    }
    char *message = "Hello from client!";
    send(sock, message, strlen(message), 0);
    int recv_size = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (recv_size > 0) {
        buffer[recv_size] = '\0';
        printf("Server reply: %s\n", buffer);
    } else if (recv_size == 0) {
        printf("Server closed connection\n");
    } else {
        printf("recv failed: %d\n", WSAGetLastError());
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}
