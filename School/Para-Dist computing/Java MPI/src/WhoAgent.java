/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import UWAgent.*; 
import java.io.*;
import java.util.*;

/**
 *This program creates a client using the UWAgent program developed at
 * UW bothell. This program migrates an agent to a specified number of 
 * computers, executes a posix "who" command, then takes the results back
 * to the main class for output. 
 * 
 *
 * @author jondi521
 */
public class WhoAgent extends UWAgent implements Serializable{
    private Vector<String> whoReturn;
    private Vector<String> hosts;
    private int iterations; 
    private int completeIter = 0; 
    private String glblArgs[];
    private Date startTime; 
    private int jumps;

    public void init()
    {//Initial state of agent
        
        startTime = new Date();
         
        getHosts();
        jumps = hosts.size() - 1;
        
        hop(hosts.elementAt(jumps), "nextHop", null);
        
    }

    public WhoAgent(String args[])
    {   
        glblArgs = args.clone(); // copy args into global variable
    }
    
    public void getHosts()
    {//get hosts from the Arguments, as well as number of iterations to do
        
        hosts = new Vector<String>(); 

        if ( glblArgs.length < 2 ) {
            System.err.println( "usage: java WhoAgent #iterations "
                    + "ip-addresses(seperated by spaces)" );
            System.exit( -1 );
        }
        iterations = Integer.parseInt(glblArgs[0]);

        for(int i = 1; i < glblArgs.length; i++)
        {
            hosts.add(glblArgs[i]);
        }

        try {
            hosts.add(java.net.InetAddress.getLocalHost().getHostName());
        } catch (java.net.UnknownHostException ex) {}
        // Add localHost to the hosts vector. 
    }
    
    public void get( ) 
    {//Performs a "who" command on the agent's current host. 
	String line;
	try {
	    Runtime runtime = Runtime.getRuntime( );
	    Process process = runtime.exec( "who" );
	    InputStream input = process.getInputStream();
	    BufferedReader bufferedInput
		= new BufferedReader( new InputStreamReader( input ) );
	    while ( ( line = bufferedInput.readLine( ) ) != null ) {
		System.out.println( line );
		whoReturn.addElement( line );
	    }
	} catch ( IOException e ) {
	    e.printStackTrace( );
	}
    }
    
    public void nextHop() throws InterruptedException
    {//Recusivly jumps to each node and performs a get command then returns
     //home
        
        jumps--;
        get();
        
        vectorOutput(); ///<-- debug
        
        if(jumps == 0)
        {
            hop(hosts.elementAt(hosts.size()), "homeCall", null);
        }
        else
        {hop(hosts.elementAt(jumps), "nextHop", null);}
        
        
    }
    
    public void homeCall() throws InterruptedException
    {// This function handles outputting data then setting up for the next
     // iteration of the loop. 
        if(completeIter < iterations) //Hop back to first host and start over
        {
            jumps = hosts.size() - 1;
            
            hop(hosts.elementAt(jumps), "nextHop", null);
            
            Thread.sleep(100); //Code added for output consistancy
            completeIter++;
        }

        vectorOutput();
    }
        
    public void vectorOutput()
    {// Output the vector to the user as well as current execution time
        if( whoReturn == null)
            return;
        
        for(String str : whoReturn)
        {
            System.out.println(str);
        }
        
        Date endTime = new Date();
        System.out.println( "\ntime elapsed = " +
	           ( endTime.getTime( ) - startTime.getTime( ) ) +
		   " msec\n" ); 
    }
}
