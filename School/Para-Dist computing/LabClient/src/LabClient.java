/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import java.net.*;
import java.io.*;
/**
 *
 * @author jondi521
 */
public class LabClient {
    
    public LabClient(int serverPort, String IPaddr)
    {
        Socket socket; //create socket for client
        double[] read = new double[100]; 
        
        for(int i = 0; i < 100; i++)
        {
            read[i] = i; 
        }
       
        try
        {
            socket = new Socket(IPaddr, serverPort);
            DataInputStream in = new DataInputStream (socket.getInputStream());
            DataOutputStream out = new DataOutputStream 
                    (socket.getOutputStream());
            
            for(int i = 0; i < 100; i++)
            {
                out.writeDouble(read[i]);
            }
            
            for(int i = 0; i < 100; i++)
            {
                read[i] = in.readDouble();
                System.out.println(read[i]);
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
        if ( args.length != 2)
        {
            System.err.println( "Syntax: java LabClient <server port> <server IP>");
            System.exit(1);
        }
        
        //Convert args to a port
        int port = Integer.parseInt(args[0]); 

        new LabClient(port, args[1]);
    }
   
}  

