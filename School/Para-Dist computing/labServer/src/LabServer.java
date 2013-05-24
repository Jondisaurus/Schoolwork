/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 * 
 * 
 * Jonathan Difrancesco LAB 1
 * 
 * This lab program relies heavily on Blocking to handle sycronization problems
 * This is not built to handle any sort of network errors, if one occurs this 
 * program will not operate at all. 
 */

/**
 *
 * @author jondi521
 */

import java.net.*;
import java.io.*;




public class LabServer {
  
     
    public LabServer(int serverPort)
    {
        Socket socket; //create socket for client
        double[] read = new double[100]; 
       
        try
        {
            System.out.println("Binding server to port:  " + serverPort); 
            ServerSocket server = new ServerSocket(serverPort); 
                // Bind ServerSocket to port
            System.out.println(server);
            server.setSoTimeout(50);
            
            socket = server.accept(); // blocks till client connects
            
            DataInputStream in = new DataInputStream(socket.getInputStream());
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            
            for(int i = 0 ; i < 100 ; i++)
            {
                read[i] = in.readDouble();
                read[i] = Math.sqrt(read[i]); 
            }
            
            for(int i = 0 ; i < 100 ; i++)
            {
                out.writeDouble(read[i]);
            }
        }
        catch(IOException ioe)
        {
            System.out.println("somethin' went wrong, probably");
        }
        
    }
    
    public static void main ( String args[] )  
    {/**
     * main function of program, handles args and instaciates the chatserver. 
     */
        // Check for only port
        if ( args.length != 1)
        {
            System.err.println( "Syntax: java LabServer <server port>");
            System.exit(1);
        }
        
        //Convert args to a port
        int port = Integer.parseInt(args[0]); 

        new LabServer(port);
    }
}
