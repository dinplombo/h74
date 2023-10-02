#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   

int main() {
        
    int socket_server;
    if ( (socket_server = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket create failed");
        return 1;
    }
        
    struct sockaddr_in server_sin;
    memset(&server_sin, 0, sizeof(server_sin));
    server_sin.sin_family    = AF_INET; 
    server_sin.sin_addr.s_addr = INADDR_ANY;
    server_sin.sin_port = htons(1050);
        

    if ( bind(socket_server, (const struct sockaddr *)&server_sin,sizeof(server_sin)) < 0 )
    {
        perror("bind failed");
        return 1;
    }

    struct sockaddr_in client_sin;
    int buffer_len;
    socklen_t client_sin_len = sizeof(client_sin); 
    char buffer[1024];
    buffer_len = recvfrom(socket_server, buffer, sizeof(buffer), 0, ( struct sockaddr *) &client_sin, &client_sin_len);
    buffer[buffer_len] = '\0';
    printf("Client : %s\n", buffer);
        
    return 0;
}