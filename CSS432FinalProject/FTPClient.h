


class FTPClient{
	char* userName;
	char* password;

public:
	FTPClient(); 
	~FTPClient(); 
	bool open(char* hostName, int port); //open a TCP connection to port
	bool close();
	void quit(); 
	bool sendUserName(char* nameToSend);
	bool sendPassword(char* passToSend);
	bool changeDir(char* dirName);
	char* getCurrentDirContents(); //returns buffer with directory contents
	bool getFile(char* fileName);
	bool putFile(char* fileName);
private:

};

