//Kyle Morrison and Jon Di Francesco
//DFS_Server Class
//This class is the file server for DFS_Client, which allows you to remotely 
//    edit text documents via RPC
import java.io.*;
import java.util.*;
import java.rmi.*;
import java.rmi.server.*;
import java.io.File;
import java.nio.file.*;

//This is the instantiatable Server class
//This class performs all of the actions dictated in the assignment
public class DFS_Server extends UnicastRemoteObject
        implements ServerInterface {
    //Constants representing the four possible states of a file

    final int Not_Shared = 0;
    final int Read_Shared = 1;
    final int Write_Shared = 2;
    final int Ownership_Change = 3;
    //Holds all of the actual files, and information for each file
    Vector<ServerFile> files;
    private static int port;

    public static void main(String args[]) {

        String bind = "error";
        //If you have provided arguments
        if (args.length != 1) {
            System.err.println("usage: java WhoServer port$");
            System.exit(-1);
        }

        try {
            DFS_Server server = new DFS_Server();
            port = Integer.parseInt(args[0]);
            bind = ("rmi://localhost:"
                    + Integer.toString(port) + "/DFS_Server");
            Naming.rebind(bind, server);
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }

        System.out.println(bind + " invoked");
    }

    //Instantiate the server
    public DFS_Server() throws RemoteException {
        //Create cache
        files = new Vector<ServerFile>();

        //Search through working directory for any existing files, 
        //and if any exist, add them to the cache
        final File folder = new File("/");
        File[] listOfFiles = folder.listFiles();

        for (File listOfFile : listOfFiles) {
            //Find files in directory, and make sure they arent .java or 
            //.class so as to not grab themselves
            if (listOfFile.isDirectory()) {
                try {
                    //Create new server file from the file you just 
                    //created on your local drive
                    ServerFile sFile = new ServerFile(new FileContents(
                            Files.readAllBytes(Paths.get(listOfFile.
                            getAbsolutePath()))), listOfFile.getName());
                    sFile.changeState(Not_Shared);
                    files.add(sFile);
                } catch (IOException e) {
                }
            }
        }
    }

    //Wrapper to make this call synchronized
    private synchronized boolean writeback(ClientInterface client) {
        try {
            return client.writeback();
        } catch (Exception e) {
            System.out.println(e);
        }
        return false;
    }

    //Wrapper to make this cal synchronized
    private synchronized boolean invalidate(ClientInterface client) {
        try {
            return client.invalidate();
        } catch (Exception e) {
            System.out.println(e);
        }
        return false;
    }

    //Prints the server feedback string
    private FileContents getServerFeedback(String user, String filename,
            ServerFile sfile, int state, String ownership,
            String mode, Vector<String> readers) {
        System.out.print("file(" + filename + ") requested by ");
        System.out.print(user + ":download(");
        if (mode.contains("w")) {
            System.out.print("w): state( ");
        } else {
            System.out.print("r): state( ");
        }

        if (state == 0) {
            System.out.print("notshared --> ");
        } else if (state == 1) {
            System.out.print("readshared --> ");
        } else if (state == 2) {
            System.out.print("writeshared --> ");
        } else {
            System.out.print("ownershipchange --> ");
        }

        if (mode.contains("w")) {
            System.out.println(" writeshared ) error_code = 0");
        } else {
            System.out.println(" readshared ) error_code = 0");
        }

        System.out.println("# readers = " + Integer.toString(readers.size()));
        for (String reader : readers) {
            System.out.println("reader = " + reader);
        }
        System.out.println("owner = " + ownership);


        return sfile.getContents();
    }

    //Downloads a given file "filename" in mode "mode" and returns the object
    //Note, if any mode other than "w" is given, it will return a read
    public FileContents download(String myIpName, String filename, String mode) {
        //First, look through cache for file
        for (ServerFile sFile : files) {
            //The file has been found
            if (sFile.getFilename().matches(filename)) {
                System.out.print("file read from: " + filename);
                System.out.println(" " + sFile.length() + " bytes");
                if (sFile.getState() == Not_Shared) {
                    if (mode.matches("w")) {
                        sFile.changeState(Write_Shared);
                        sFile.changeOwner(myIpName);
                    }
                }

                //Entry already exists in the cache, determine previous mode 
                //and new mode. If state is already in Read_Shared mode
                if (sFile.getState() == Read_Shared) {
                    if (mode.matches("w")) {
                        sFile.changeState(Write_Shared);
                        sFile.changeOwner(myIpName);
                    } else {
                        sFile.addReader(myIpName);
                    }
                }

                //If state is already in Write_Shared mode
                if (sFile.getState() == Write_Shared) {
                    if (mode.matches("w")) {
                        //Change the file's state to "Ownership_Change"
                        sFile.changeState(Ownership_Change);

                        //Call the file owner's writeback() function, wait 
                        //for the client to activate the server's upload()
                        //function to give the server latest version. If 
                        //writeback() == true, send the file to the person 
                        //waiting    
                        try {
                            ClientInterface client =
                                    (ClientInterface) Naming.lookup("rmi://"
                                    + sFile.getOwner() + ":" + port
                                    + "/DFS_Client");
                            if (client.writeback()) {
                                sFile.changeOwner(myIpName);
                                sFile.changeState(Write_Shared);
                            }
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                    } else {
                        sFile.addReader(myIpName);
                    }
                }

                //If state is already in Ownership_Change
                if (sFile.getState() == Ownership_Change) {
                    if (mode.matches("w")) {
                        try {
                            //Client must wait for other client to finish 
                            //ownership change
                            //Server must wait on download() until state 
                            //changes to Write_Shared
                            while (sFile.getState() == Ownership_Change) {
                                Thread.sleep(1000);
                            }
                            ClientInterface client = (ClientInterface) Naming.lookup("rmi://"
                                    + sFile.getOwner() + ":"
                                    + port + "/DFS_Client");
                            System.out.print("download "
                                    + filename + " ): ");
                            System.out.println(myIpName
                                    + " waits for writeback");
                            if (this.writeback(client)) {
                                sFile.changeOwner(myIpName);
                                sFile.changeState(Write_Shared);
                            }
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                    } else {
                        sFile.addReader(myIpName);
                    }
                }
                return getServerFeedback(myIpName, filename, sFile,
                        sFile.getState(),
                        sFile.getOwner(), mode, sFile.getAllReaders());
            }
        }


        //If the requested was not found, create it
        try {
            System.out.println("file: " + filename + " does not exist.");
            //Create an empty file in working directory
            File newFile = new File(filename);
            newFile.createNewFile();
            byte[] data = Files.readAllBytes(Paths.get(newFile.getAbsolutePath()));

            //Add data to FileContents
            FileContents fileContents = new FileContents(data);

            //Add FileContents to ServerFile
            ServerFile newSFile = new ServerFile(fileContents, filename);
            System.out.print("name= " + filename + " state = ");
            System.out.println(newSFile.getState() + " ownership = false");

            //Register mode and user information
            if (mode.matches("r")) {
                newSFile.changeState(Read_Shared);
                newSFile.addReader(myIpName);
            }

            if (mode.matches("w")) {
                newSFile.changeState(Write_Shared);
                newSFile.changeOwner(myIpName);
            }

            //Add ServerFile to files list
            files.add(newSFile);

            //Give the requested file to the client
            return getServerFeedback(myIpName, filename,
                    newSFile, newSFile.getState(),
                    newSFile.getOwner(), mode, newSFile.getAllReaders());
        } catch (Exception e) {
            System.out.println(e);
        }
        return null;
    }

    public boolean upload(String myIpName, String filename, FileContents contents) {
        //Second, check the states
    for (ServerFile sFile : files) {
            //The file has been found
            if (sFile.getFilename().matches(filename)){
            if((sFile.getState() == Not_Shared) || sFile.getState() == Read_Shared) {
                sFile.removeReader(myIpName);
                return false;
            }
            //Invalidate for all readers
            for (String user : sFile.getAllReaders()) {
                try {
                    boolean response = this.invalidate((ClientInterface) Naming.lookup("rmi://" + user + ":"
                            + port + "/DFS_Client"));
                    if (response) {
                        System.out.print("download( " + filename + " ): ");
                        System.out.println(user + "'s copy was invalidated");
                        if (!(sFile.getOwner()).contains("null")) {
                            sFile.removeReader(user);
                        } else {
                            sFile.setOwner("null");
                        }
                    } else {
                        System.out.print(user
                                + " was unable to invalidate this file.");
                        System.out.println("Not sure how to proceed");
                    }
                } catch (Exception e) {
                    System.out.print("Exception caught connecting to client.");
                    System.out.println("Could not connect to: " + user);
                }
            }

            //if the entry state is 
            //"Write_Shared", change state to "Not Shared"
            if (sFile.getState() == Write_Shared) {
                sFile.changeState(Not_Shared);
            }

            if (sFile.getState() == Ownership_Change) {
                sFile.changeState(Write_Shared);
            }

            System.out.println(myIpName + " upload: file = " + filename);
            System.out.println("bytes = " + contents);

            sFile.setContents(contents);
            return true;
        }

    }
    return false;
    }

}