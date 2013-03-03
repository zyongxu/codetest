#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int sock_handler;        // client socket
    sockaddr_in clnt_addr;   // client address the socket to bind
    struct ip_mreq mc_req;   // multicast group address
    unsigned char msg_buf[2048];

    if ((sock_handler = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        cerr<<"Client Error: Unable to open socket!"<<endl;
        exit(1);
    }
    memset(&clnt_addr, 0, sizeof(clnt_addr));
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_port = htons(54322);
    clnt_addr.sin_addr.s_addr = htonl(INADDR_ANY); // WARNING: differs from sender
    if (bind(sock_handler, (sockaddr *) &clnt_addr, sizeof(clnt_addr)) < 0) {
        cerr<<"Server Error: Failed to bind the socket with localhost"<<endl;
        exit(1);
    }

    mc_req.imr_multiaddr.s_addr = inet_addr("127.0.0.1"); // The address of the mc group
    mc_req.imr_interface.s_addr = htonl(INADDR_ANY);      // The address of the interface
    setsockopt(sock_handler, IPPROTO_IP, IP_ADD_MEMBERSHIP, 
               (void *) &mc_req, sizeof(mc_req));

    int len = recvfrom(sock_handler, (void *) msg_buf, 2048,
                       0, NULL, NULL);

    cout<<msg_buf<<endl;
    return 0;
}

