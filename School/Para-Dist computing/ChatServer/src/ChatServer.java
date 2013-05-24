/**
 * ChatServer - 
 * 
 * This implements a chatserver for part one of CSS 343 project one. 
 * 
 * This chatserver scans and accepts new sockets and adds them to an array
 * of connected clients. It them iterates through the clients and broadcasts
 * messages as they arrive. This program is very simple in implementation.
 * 
 * Assumptions:
 * - Clients will be using the supplied chatClient.java or will be using 
 * something
 *      compatible. 
 * - The port that the server uses will be clear and allow incoming and outgoing 
 * connections
 * - The security settings allow for this program to be run. 
 * 
 * @author Jonathan Difrancesco - 10/14/12
 */

import java.net.*;
import java.io.*;
import java.util.*;

public class ChatServer {
    /**
     * Chat server
     * 
     * Broadcasts input from connected users to all other users connected. 
     * 
     */
    
    private int connectedClients = 0;
    private Thread acceptThread = null;
    private int MAX_USERS = 100; 
    
        
    public ChatServer(int serverPort)
    {/**
     * Starts a new chat server on the specified serverPort
     * 
     * @param serverPort server port to use when launching the chat server
     */
       String read = "";
       boolean run = true; // keeps the main thread running
        
        try { 
            
            System.out.println("Binding server to port:  " + serverPort); 
            ServerSocket server = new ServerSocket(serverPort); 
            // Bind ServerSocket to port
            System.out.println(server);
            
            server.setSoTimeout(50);  // Set network timeout to 50ms

            ArrayList<clientConnection> clients = 
                    new ArrayList<clientConnection>();
            //List that holds all connected client information
            
            while(run) // Main program loop
            {
                while(true) // gets clients until connected clients returns false
                {
                    if(!getClients(server, clients)) // get clients if available 
                    { break;}
                }
                
                for(clientConnection client : clients) 
                { //Iterates through each client checking for user data
                    
                    DataInputStream in = new DataInputStream
                            (client.socket.getInputStream());
                    //recieve Cliet data stream
                    
                    if(in.available() > 0)
                    {
                        read = in.readUTF(); // If data is available receive input
                        
                        if(read.equals(".quit")) // quit program if command entered
                        {
                           run = false; 
                           break; 
                        }
                        
                        for(clientConnection inClient : clients) // broadcast recieved data 
                        {
                            DataOutputStream out = new DataOutputStream
                                    (inClient.socket.getOutputStream());
                            out.writeUTF(client.name +": >> " + read);
                        }
                    }
                }
                cleanClients(clients); // clean client list
            }//END OF MAIN LOOP
            
         }catch (Exception e) 
         {
             e.printStackTrace();
         }
    }

    public static void main ( String args[] )  
    {/**
     * main function of program, handles args and instaciates the chatserver. 
     */
        // Check for only port
        if ( args.length != 1)
        {
            System.err.println( "Syntax: java ChatServer <server port>");
            System.exit(1);
        }
        
        //Convert args to a port
        int port = Integer.parseInt(args[0]); 

        //Instatiate main ChatServer application
        new ChatServer(port);
    }  

    private boolean getClients(ServerSocket server, ArrayList<clientConnection> clients)
    {/**
     * Gets clients from the server and stores them in an ArrayList container
     * 
     * @param server Server socket to use to get clients
     * @param clients ArrayList of connected clients
     */
        Socket socket; // placeholder for sockets to get
     
        try{
            socket = server.accept(); // Get connections from socket if there
            
            clientConnection newClient;
            
            newClient = new clientConnection(); 
            
            newClient.socket = socket; // add socket to client's information
            DataInputStream in = new DataInputStream(socket.getInputStream());
          
            newClient.name = in.readUTF();  // add name to client information
                
            System.out.println("New user Connected: " + newClient.name);
            
            clients.add(newClient); // add client to ArrayList
            //in.close(); 
            
            return true; // return true to indicate that a user connected
            
         }catch(IOException i )
         {
             return false; 
         }
           
         
    }////END OF getClients
    
    void cleanClients(ArrayList<clientConnection> clients)
    {/**
     * clean the client list of any disconnected clients.
     * 
     * @param clients ArrayList of clients to clean
     */
        for(clientConnection client : clients) // Pull closed connections out of list
         {
             if(client.socket.isClosed())
             {
                 System.out.println("User disconnected: " + client.name);
                 clients.remove(client);
             }
         }
    }

    class clientConnection
    {/**
     * Container class for clients
     */
        Socket socket = null; 
        String name = null; 
    }
}/// END OF CHATSERVER

