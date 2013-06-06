#include "FTPClient.h"
#include <iostream>
#include <fstream>
#define CHAR_SIZE 1000
#define MAX_FTP_ARGS 10

char** userInput;
int inputSize = 0; 

char** getUserInput() {
    if(userInput){
        delete userInput; 
    }
    userInput = new char*;

    char* temp;
    char input[CHAR_SIZE];

    memset(input, '\0', sizeof(input));
    //memset(userInput, '\0', sizeof(userInput));

    inputSize = 0;

    for(int i = 0; i < CHAR_SIZE; i++) {
        input[i] = ' ';
    }
    //for(int i = 0; i < MAX_FTP_ARGS; toReturn[i] = NULL && i++);
    std::cout << "\nftp> ";
    std::cin.getline(input, CHAR_SIZE, '\n');

    std::cout << "\nSplitting " << input << " into tokens";

    userInput[inputSize] = strtok(input, " ");
 
    std::cout << "\nTOKEN: " << userInput[inputSize];
    //inputSize++;

    while(userInput[inputSize] != NULL) {
        inputSize++;
        userInput[inputSize] = strtok(NULL, " \n");
        //if(userInput[inputSize] == NULL){
            //inputSize--; 
            //break;
        //}

        //std::cout << "\nTOKEN: " << userInput[inputSize];
    }
    //inputSize++; // because I love one-off errors
    return userInput;
}

void getUserCredentials(char*& userName, char*& password) {
#if 0
    //Get User/Pass
    std::cout << "\nTo login please enter your...";
    std::cout << "\nUsername: ";
    std::cin >> userName;

    std::cout << "\nPassword: ";
    std::cin >> password;
#endif
}

void outputHelp() {
    std::cout << "this is a stub :<";
}


int main( int argc, char* argv[] ) {

    FTPClient* client = new FTPClient();
    char* userName = new char[CHAR_SIZE];
    char* password = new char[CHAR_SIZE];
    char* dirName = new char[CHAR_SIZE];



    //TESTING GET USER INPUT!!!
    getUserInput();

    for(int i = 0; i <= inputSize; i++){
        std::cout << userInput[i] << std::endl; 
    }



#if 0
    for(int i = 0; i < CHAR_SIZE; i++) {
        userName[i] = password[i] = dirName[i] = ' ';
    }

    if(argc != 3) {
        std::cout << "\nUSAGE: " << argv[0] << " [hostname] [port]";
    }



    //connect to server
    if(!client->open(argv[1],atoi(argv[2]))) {
        std::cout << "\nConnection refused...";
        exit(0);
    }

    std::cout << "\nClient connected! Woop woop!";

    bool runProgram = true;
    while(runProgram) {

        char** userInput = getUserInput();
#endif
#if 0
        //NOTE I DONT KNOW HOW TO WRITE C SWITCHES APPARENTLY
        //DUMB DUMB DUMB DUMB DUMB
        switch(userInput[0]) {
        case "login":
            getUserCredentials(userName, password);
            break;
        case "get":
            client->getFile(userInput[1]);
            break;
        case "put":
            client->putFile(userInput[1]);
            break;
        case "quit":
            client->quit();
            runProgram = false;
            break;
        case "close":
            client->close();
            break;
        case "ls":
            client->changeDir(userInput[1]);
            break;
        case "?":
            outputHelp();
            break;
        default:
            std::cout << "\nInput not recognized, please re-enter or type ? for help";
            break;
        }
#endif
//    }





    //Send user/pass
    //client->sendUserName(userName);
    //client->sendPassword(password);

    //client->changeDir(dirName);

    //delete client;
}
