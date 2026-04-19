#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 12345
DWORD WINAPI handle_client(LPVOID client_socket_ptr) {
    SOCKET client = *(SOCKET*)client_socket_ptr;
    free(client_socket_ptr);
    char buffer[1024];
    int recv_size;
    recv_size = recv(client, buffer, sizeof(buffer) - 1, 0);
    if (recv_size > 0) {
        buffer[recv_size] = '\0';
        printf("Client says: %s\n", buffer);
        char *response = "Hello from server!";
        send(client, response, strlen(response), 0);
    } else if (recv_size == 0) {
        printf("Client disconnected\n");
    } else {
        printf("recv failed: %d\n", WSAGetLastError());
    }
    closesocket(client);
    return 0;
}
int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c = sizeof(struct sockaddr_in);
    WSAStartup(MAKEWORD(2, 2), &wsa);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket failed\n");
        return 1;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Bind failed\n");
        return 1;
    }
    listen(server_socket, 5);
    printf("Server listening on port %d...\n", PORT);
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client, &c);
        if (client_socket == INVALID_SOCKET) {
            printf("Accept failed\n");
            continue;
        }
        printf("Client connected\n");
        SOCKET* new_sock = malloc(sizeof(SOCKET));
        *new_sock = client_socket;
        HANDLE thread = CreateThread(NULL, 0, handle_client, (LPVOID)new_sock, 0, NULL);
        CloseHandle(thread);
    }
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
