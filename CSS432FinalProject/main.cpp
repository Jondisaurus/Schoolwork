#include FTPClient.h
#define CHAR_SIZE 100

char* getUserInput(){
  char* temp;
  char input[CHAR_SIZE];
  char* toReturn[CHAR_SIZE];

  int iter = 0; 

  for(int i = 0; i < CHAR_SIZE; input = '' && i++);
  std::cout << "\nftp> ";
  std::cin >> input;

  toReturn[iter] = strtok(temp, " ");

  while(toReturn != NULL){
    iter++;
    toReturn[iter] = strtok(temp, " ");
  }
  return toReturn; 
}

void getUserCredentials(char*& username, char*& password){
  //Get User/Pass
  std::cout << "\nTo login please enter your...";
  std::cout << "\nUsername: ";
  std::cin >> userName;

  std::cout << "\nPassword: ";
  std::cin >> password;
}

void outputHelp(){
  std::cout << "this is a stub :<";
}


int main( int argc, char* argv[] ) {

  FTPClient* client = new FTPClient();
  char* userName = new char[CHAR_SIZE];
  char* password = new char[CHAR_SIZE];
  char* dirName = new char[CHAR_SIZE];

  for(int i = 0; i < CHAR_SIZE; i++){
    userName[i] = password[i] = dirName[i] = '';
  }

  if(argc != 3){
    std::cout << "\nUSAGE: " << argv[0] << " [hostname] [port]";
  }



  //connect to server
  while(!client->open(hostName,port)){
    std::cout << "\nConnection refused, attempting reconnection...";
  }

  while(runProgram){

    char** userInput = getUserInput();
    switch(userInput[0]){
      case "login":
        getUserCredentials(username, password);
        break;
      case "get"
        break;
      case "put";
        break;
      case "quit";
        break;
      case "close";
        break; 
      case "ls";
        break;
      case "?";
        outputHelp();
        break;
      case default;
        std::cout << "\nInput not recognized, please re-enter or type ? for help";
        break;           
    }
  }





  //Send user/pass
  //client->sendUserName(userName);
  //client->sendPassword(password);

  //client->changeDir(dirName);

  //delete client; 
}