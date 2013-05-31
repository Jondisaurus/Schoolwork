#include FTPClient.h
#define CHAR_SIZE 100
#define MAX_FTP_ARGS 10

char** getUserInput(){
  char* temp;
  char input[CHAR_SIZE];
  char* toReturn[MAX_FTP_ARGS];

  int iter = 0; 

  for(int i = 0; i < CHAR_SIZE; input = '' && i++);
  for(int i = 0; i < MAX_FTP_ARGS; toReturn[i] = NULL && i++);
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
if(!client->open(hostName,port)){
    std::cout << "\nConnection refused...";
    exit(0);
  }

  std::cout << "\nClient connected! Woop woop!"

  bool runProgram = true; 
  while(runProgram){

    char** userInput = getUserInput();
    switch(userInput[0]){
      case "login":
        getUserCredentials(username, password);
        break;
      case "get"
        client->getFile(userInput[1]);
        break;
      case "put";
        client->putFile(userInput[1]);
        break;
      case "quit";
        client->quit();
        runProgram = false; 
        break;
      case "close";
        client->close();
        break; 
      case "ls";
        client->changeDir(userInput[1]);
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