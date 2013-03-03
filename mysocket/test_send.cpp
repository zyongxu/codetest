#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int sock_handler;
    struct sockaddr_in serv_addr, mc_addr;
    size_t msg_len=0;
    unsigned char msg_buf[2048];

    if ((sock_handler = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        cerr<<"Server Error: Unable to open socket!"<<endl;
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(54321);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bzero((char *) &mc_addr, sizeof(mc_addr));
    mc_addr.sin_family = AF_INET;
    mc_addr.sin_port = htons(54322);
    mc_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_handler, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cerr<<"Server Error: Failed to bind the socket with localhost"<<endl;
        exit(1);
    }

    FILE *fp = fopen("msg.bin", "r");
    if (!fp) {
        cerr<<"Could not open msg.bin!"<<endl;
        exit(1);
    }
    msg_len = fread(msg_buf, sizeof(msg_buf[0]), 2048, fp);
    fclose(fp);

    if ((sendto(sock_handler, (void*) msg_buf, msg_len, 0,
                (struct sockaddr*) &mc_addr, sizeof(mc_addr))) < 0 ) {
        cerr << "Sendto failed with error " << endl;
    }

    return 0;
}

