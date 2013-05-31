// ------------------------------------
//  CSS432 Program 1: Client interface
// ------------------------------------
//  This program was written to the specifications for the client interface for Assignment 1 of
//  CSS432 at University of Washington: Bothell for Spring 2013, taught by Francis Wang.
//
//  The program implements a command line client interface that connects with a server using
//  sockets, completes nReps number of writes to the server, then recieves a buffer as an
//  acknoledgement containing the number of times the server called read()
//
// ------------------------------------
//  By Jonathan Difrancesco, 2013
// ------------------------------------

#include <sys/types.h>    // socket, bind
#include <sys/socket.h>   // socket, bind, listen, inet_ntoa
#include <netinet/in.h>   // htonl, htons, inet_ntoa
#include <arpa/inet.h>    // inet_ntoa
#include <netdb.h>        // gethostbyname
#include <unistd.h>       // read, write, close
#include <string.h>       // bzero
#include <netinet/tcp.h>  // SO_REUSEADDR
#include <sys/uio.h>      // writev
#include <sys/time.h>
#include <iostream>

//-Global variables
const int CHARS_RECIEVED = 33;

int main(int argc, const char * argv[])
{
    //-Check args
    if(argc != 7){
        std::cout << "Invalid arguments! client serverPort nReps nBufs bufSize serverIp type\n";
        return 0;
    }

    //-Setup program
    int server_port = atoi(argv[1]);
    int nReps = atoi(argv[2]);
    int nBufs = atoi(argv[3]);
    int bufSize = atoi(argv[4]);
    const char* server_name = argv[5];
    int type = atoi(argv[6]);
    
    int clientSd;
    int numOfReads = 0;
    int count = 0;
    struct timeval getTime;
    long startTime,
         sendTime,
         roundTripTime;
    
    char databuf[nBufs][bufSize];
    char returnBuf[CHARS_RECIEVED];
    struct hostent* host = gethostbyname( server_name );
    
    //-Output connection info
    std::cout << "\nClient program started with Args:\n";
    
    fprintf(stdout, "Server port: %i   nReps: %i   nBufs: %i   \nbufSize: %i   serverName: %s   type: %i\n\n", server_port,
            nReps, nBufs, bufSize, server_name, type);
    
    if (!host) {
         fprintf(stderr, "%s: unknown hostname: %s\n", argv[0], host);
         exit(1);
    }
    
    //-Declaration of sockaddr_in structure. 
    sockaddr_in sendSockAddr;
    memset( (char *) &sendSockAddr, '\0', sizeof( sendSockAddr ) );
    sendSockAddr.sin_family      = AF_INET; // Address Family Internet
    sendSockAddr.sin_addr.s_addr =
          inet_addr( inet_ntoa( *(struct in_addr *) *host->h_addr_list ) );
    sendSockAddr.sin_port        = htons( server_port );  // convert host byte-order
    
    //-Create socket to be used. SD is the FD to use. 
    if((clientSd = socket(AF_INET, SOCK_STREAM, 0)) <0){
       fprintf(stderr, "%s: socket failure", argv[0]);
       exit(1);
    }
    
    //-Connect socket to the server
    while(connect(clientSd, (struct sockaddr *) &sendSockAddr, sizeof(sendSockAddr)) == -1){
       std::cout << "Connection refused. Retrying Connection...\n";
       sleep(1);
    }
    
    //-Start of clock
    gettimeofday(&getTime, NULL);
    startTime = getTime.tv_usec + (getTime.tv_sec * 1000000);
    
    //-Perform nReps writes
    for (int i = 0; i < nReps; i++) {
       
       switch (type) {
           case 1:{
               for ( int j = 0; j < nBufs; j++ ){
                   write( clientSd, databuf[j], bufSize );
                   count++;
               }
               break;
           }
           case 2:{
               struct iovec vector[nBufs];
               for ( int j = 0; j < nBufs; j++ ) {
                   vector[j].iov_base = databuf[j];
                   vector[j].iov_len = bufSize;
                   count++;
               }
               writev( clientSd, vector, nBufs );           // sd: socket descriptor

               count++;
               break;
           }
           case 3:{
               write( clientSd, databuf, nBufs * bufSize ); // sd: socket descriptor
               count++;
               break;
           }
           default:{
               std::cout << "\nINCORRECT TYPE! Use (1) for multiple writes (2) for writeev, or (3) for single Write.\n";
               break;
           }
       }
    }
    
    //-End of sent data clock
    gettimeofday(&getTime, NULL);
    sendTime = getTime.tv_usec - startTime + (getTime.tv_sec * 1000000);
    
    //-Read back from server
    read(clientSd, returnBuf, sizeof(returnBuf));
    numOfReads = atoi(returnBuf);
    
    //-End of roundtrip clock
    gettimeofday(&getTime, NULL);
    roundTripTime = getTime.tv_usec - startTime + (getTime.tv_sec * 1000000);
    
    std::cout << "Test " << type << ": data-sending time = " << sendTime << "usec, round-trip time = " << roundTripTime
            << "usec, # of reads = " << numOfReads << '\n';
    
    
    close(clientSd);
    
    exit(0);
}

