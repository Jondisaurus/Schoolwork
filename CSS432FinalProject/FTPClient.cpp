
#include "FTPClient.h"

FTPClient::FTPClient(){
	clientSD = 0;
} 
FTPClient::~FTPClient(){
}
bool FTPClient::open(char* hostName, int port){
	//Setup
	char read[1450];

	for(int i = 0; i < 1448; i++ && read[i] = '');

	// Attempt to connect to server
	sock = new Socket(port);
	clientSD = sock->getClientSocket(hostName);

	// Read Connection acknoledgement from server. 
	read(clientSD, read, 1450);

	std::cout << '\n' << read; 


	if(clientSD > 0){
		return true;
	}
}
bool FTPClient::close(){
	std::cout << "\nConsider yourself STUBBED!!"
	close(clientSD);
	return true;
}
void FTPClient::quit(){
	std::cout << "\nConsider yourself STUBBED!!"
	close(clientSD);
	exit(1);
} 
bool FTPClient::sendUserName(char* nameToSend){
	write(clientSD, nameToSend);
	return true;
}
bool FTPClient::sendPassword(char* passToSend){
	std::cout << "\nConsider yourself STUBBED!!"
	return true;
}
bool FTPClient::changeDir(char* dirName){
	std::cout << "\nConsider yourself STUBBED!!"
	return true;
}
char* FTPClient::getCurrentDirContents(){
	std::cout << "\nConsider yourself STUBBED!!"
	return NULL; 
} //returns buffer with directory contents
bool FTPClient::getFile(char* fileName){
	std::cout << "\nConsider yourself STUBBED!!"
	return true; 
}
bool FTPClient::putFile(char* fileName){
	std::cout << "\nConsider yourself STUBBED!!"
	return true;
}