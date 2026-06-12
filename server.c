#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 10);

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        pid_t pid = fork();

        if (pid == 0) {
            char buffer[1024];
            read(client_fd, buffer, sizeof(buffer));
            printf("Request:\n%s\n", buffer);

            char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>C server mutha</h1>";
            write(client_fd, response, strlen(response));

            close(client_fd);
            exit(0);
        } else {
            close(client_fd);
        }
    }
}