#include FTPClient.h


int main( int argc, char* argv[] ) {

  FTPClient* client = new FTPClient();
  char* userName = new char[100];
  char* password = new char[100];
  char* dirName = new char[100];

  if(argc != 3){
    std::cout << "\nUSAGE: " << argv[0] << " [hostname] [port]";
  }

  //Get User/Pass
  std::cout << "\nUsername: ";
  std::cin >> userName;

  std::cout << "\nPassword: ";
  std::cin >> password;


  //connect to server
  while(!client->open(hostName,port)){
    std::cout << "\nConnection refused, attempting reconnection...";
  }

  //Send user/pass
  client->sendUserName(userName);
  client->sendPassword(password);

  client->changeDir(dirName);

  delete client; 
}