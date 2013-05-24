/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.rmi.*;
import java.rmi.server.*;
import java.util.*;
import java.net.MalformedURLException;

/**
 *This client iterated through a specified number of WhoServers set up
 * accross a network and performs a RMI operation on each one invoking a 
 * posix "who" command. After the results of each server are collected, they 
 * are displayed for the user. If more iterations are to occur, the program
 * loops back and starts agian. 
 * 
 * @author jondi521
 */
public class WhoClient {
    private static Vector<String> returnValue;
    private static Vector<String> ipAddresses;
    private static int port; 
    private static int iterations; 

    /**
     * @param args the command line arguments
     */
    
    public WhoClient()
    {/**
     *This loops through a list of servers and executes a "who" command on
     * each one then returns the results. 
     * 
     */
        Date startTime = new Date(); 
        System.out.println();
        
        for(int i = 1; i <= iterations; i++) // loop through whole server list
        {
            System.out.println("Loop# " + i);
            System.out.println("=================\n");
            
            for(String str : ipAddresses) // for each string in ipAddresses
            {
                try{
                     System.out.println("Connected to: " + str);
                     ServerInterface server = //Connect to server in args
                          (ServerInterface)Naming.lookup
                          ( "rmi://" + str + ":"+ port +"/whoserver");

                     returnValue = server.get();// get vector array

                 }catch(NotBoundException e){System.out.println(e);}
                  catch(RemoteException ex){System.out.println(ex);}
                  catch(MalformedURLException xx) {System.out.println(xx);}
            }
            vectorOutput();
        }
         Date endTime = new Date();
         System.out.println( "\ntime elapsed = " +
	           ( endTime.getTime( ) - startTime.getTime( ) ) +
		   " msec" ); 
    }
    
    private void vectorOutput()
    {/**
     * Output vectors to console
     */
        if( returnValue == null)// if no elements, bail
            return;
        
        for(String str : returnValue)
        {
            System.out.println(str);
        }
    }
    
    public static void main(String[] args)
    { /**
     * Main function, initialized the main function and checks inputs
     * 
     */
       ipAddresses = new Vector<String>(); 
        
        
        if ( args.length < 2 ) { 
	    System.err.println( "usage: java DFS_Client port "
                    + "ip-address" );
	    System.exit( -1 );
	}
        
        port = Integer.parseInt(args[0]);
        iterations = Integer.parseInt(args[1]);
        
        
        
        new WhoClient(); // start 
    }
}
