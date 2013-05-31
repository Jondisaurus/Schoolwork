
#include "FTPClient.h"

FTPClient::FTPClient(){
	clientSD = new int; 
	clientSD = 0;

} 
FTPClient::~FTPClient(){
}
bool FTPClient::open(char* hostName, int port){
	sock = new Socket(port);
	clientSD = sock->getClientSocket(hostName);

	if(clientSD > 0){
		return true;
	}
}
bool FTPClient::close(){
	close(clientSD);
	return true;
}
void FTPClient::quit(){
	close(clientSD);
	exit(1);
} 
bool FTPClient::sendUserName(char* nameToSend){
	write(clientSD, nameToSend);
	return true;
}
bool FTPClient::sendPassword(char* passToSend){
	return true;
}
bool FTPClient::changeDir(char* dirName){
	return true;
}
char* FTPClient::getCurrentDirContents(){
	return NULL; 
} //returns buffer with directory contents
bool FTPClient::getFile(char* fileName){
	return true; 
}
bool FTPClient::putFile(char* fileName){
	return true;
}