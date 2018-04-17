#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sstream>

class NtpTimer {
public:
    NtpTimer()
    {
        hostname=(char *)"200.20.186.76";

        portno = 123;
        maxlen = 1024;

        buf = new unsigned long[maxlen];
        
        proto = getprotobyname("udp");
        s = socket(PF_INET, SOCK_DGRAM, proto->p_proto);
         
        memset( &server_addr, 0, sizeof( server_addr ));

        server_addr.sin_family=AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(hostname);
        server_addr.sin_port=htons(portno);
    };

    std::string GetTime()
    {
        int i=sendto(s,msg,sizeof(msg),0,(struct sockaddr *)&server_addr,sizeof(server_addr));

        struct sockaddr saddr;
        socklen_t saddr_l = sizeof (saddr);

        i=recvfrom(s,buf,48,0,&saddr,&saddr_l);

        tmit=ntohl((time_t)buf[4]); //# get transmit time
     
        tmit-= 2208988800U;

        struct tm * locTime = localtime(&tmit);

        std::ostringstream ss;
        ss << locTime->tm_hour << ":";
        ss << locTime->tm_min  << ":";
        ss << locTime->tm_sec;
        
        return ss.str();
    };

    ~NtpTimer() { delete buf; }
private:
    char *hostname;

    int portno;
    int maxlen;

    unsigned char msg[48] = {010,0,0,0,0,0,0,0,0};

    unsigned long *buf;

    struct protoent *proto; 
    struct sockaddr_in server_addr;
    int s; // socket
    long tmit; 
   
};
