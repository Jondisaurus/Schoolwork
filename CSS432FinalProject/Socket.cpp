
#include "Socket.h"


Socket::Socket(int serverport){
    port = serverport;
}

int Socket::getServerSocket(){
	int serverSd = 0;
	int client = 0;


	//-Declare and initialize socket structure
    struct sockaddr_in acceptSockAddr;
    memset( (char *) &acceptSockAddr, '\0', sizeof( acceptSockAddr ) );
    acceptSockAddr.sin_family      = AF_INET; // Address Family Internet
    acceptSockAddr.sin_addr.s_addr = htonl( INADDR_ANY );
    acceptSockAddr.sin_port        = htons( port );
    
    //-Open new socket
    serverSd = socket( AF_INET, SOCK_STREAM, 0 );
    
    //-Enable the socket to be reused
    const int on = 1;
    setsockopt( serverSd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof( int ) );
    
    //-Bind the socket to the SD
    bind( serverSd, (sockaddr *) &acceptSockAddr, sizeof( acceptSockAddr ) );
    listen(serverSd, 1);
    
    //-Accept connection
    std::cout << "Setting up client\n";
    sockaddr_in newSockAddr;
    memset( (char *) &newSockAddr, '\0', sizeof( newSockAddr ) );
    socklen_t newSockAddrSize = sizeof( newSockAddr );
    int newSd;
    
    //-Accept Client
    client = accept( serverSd, (struct sockaddr *) &newSockAddr, &newSockAddrSize );

    return client; 
}

int Socket::getClientSocket(char* server_name){
	int clientSd = 0;

	struct hostent* host = gethostbyname( server_name );

	if (!host) {
         fprintf(stderr, "%s: unknown hostname: %s\n", server_name, host);
         exit(1);
    }

    //-Declaration of sockaddr_in structure. 
    sockaddr_in sendSockAddr;
    memset( (char *) &sendSockAddr, '\0', sizeof( sendSockAddr ) );
    sendSockAddr.sin_family      = AF_INET; // Address Family Internet
    sendSockAddr.sin_addr.s_addr =
          inet_addr( inet_ntoa( *(struct in_addr *) *host->h_addr_list ) );
    sendSockAddr.sin_port        = htons( port );  // convert host byte-order
    
    //-Create socket to be used. SD is the FD to use. 
    if((clientSd = socket(AF_INET, SOCK_STREAM, 0)) <0){
       fprintf(stderr, "%s: socket failure", server_name);
       exit(1);
    }
    
    //-Connect socket to the server
    while(connect(clientSd, (struct sockaddr *) &sendSockAddr, sizeof(sendSockAddr)) == -1){
       std::cout << "Connection refused. Retrying Connection...\n";
       sleep(1);
    }

    return clientSd; 
};
