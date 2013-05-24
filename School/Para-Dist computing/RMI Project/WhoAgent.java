/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import UWAgent.*; 
import java.io.*;
import java.util.*;


/**
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
    
    private int hops = 0;

    /**
     * @param args the command line arguments
     */
    public void init()
    {
        startTime = new Date();
         getHosts();
        
        jumps = hosts.size();
        
        
        hop(hosts.elementAt(jumps--), "nextHop", null);
        
    }

    public WhoAgent(String args[])
    {   
        glblArgs = args.clone();
    }
    
    public void getHosts()
    {
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
       
    }
    
    public void get( ) {
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
    {
        get();
        
        vectorOutput(); ///<-- debug
        
        if(jumps == 0)
        {
            hop(hosts.elementAt(hosts.size()), "homeCall", null);
        }
        else
        {hop(hosts.elementAt(jumps--), "nextHop", null);}
        
        
    }
    
    public void homeCall() throws InterruptedException
    {
        
        
        if(completeIter < iterations)
        {
           //start er over
            
            jumps = hosts.size() - 1;
            
            hop(hosts.elementAt(jumps--), "nextHop", null);
            
            Thread.sleep(100);
            completeIter++;
        }

        vectorOutput();
    }
        
    public void vectorOutput()
    {
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
