#include "BattleshipServer.h"


#define BACKLOG 10
#define BUF_SIZE 255

int main() {
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)perror("Socket error: ");

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(2345);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (struct sockaddr*) & sa, sizeof(sa)) == -1)perror("Bind error: ");
    listen(sd, BACKLOG);
    printf("Listening\n");

    while (1) {
        int cd = accept(sd, NULL, NULL);
        printf("Connected\n");

        char buf[BUF_SIZE];
        int l = read(cd, buf, BUF_SIZE - 1);
        buf[l] = '\0';

        printf("%s\n", buf);

        write(cd, buf, l);

        close(cd);
    }

    close(sd);
}
