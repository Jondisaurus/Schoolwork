import java.net.*;  // ServerSocket, Socket
import java.io.*;   // InputStream, ObjectInputStream, ObjectOutputStream
import java.util.*;


/**
     * This class starts a serverless chat system between connected clients. 
     * 
     * This was developed to fulfill the requirements of part 2 of Program1 for
     * CSS434. 
     * 
     * This class is based heavily on the code given from the Chat.java example
     * as well as code given by Professor Fukuda in class. 
     */
public class Chat {
    
    
    
    
    
    // Each element i of the follwoing arrays represent a chat member[i]
    private Socket[] sockets = null;             // connection to i
    private InputStream[] indata = null;         // used to check data from i
    private ObjectInputStream[] inputs = null;   // a message from i
    private ObjectOutputStream[] outputs = null; // a message to i
    
    
    //Create local vector container and queue for casual ordering
    int[] vector = null; 
    Vector<int []> queue_vec = new Vector<int[]>();
    Vector<String> queue_msg = new Vector<String>();
    Vector<Integer> queue_src = new Vector<Integer>(); 

    /**
     * Is the main body of the Chat application. This constructor establishes
     * a socket to each remote chat member, broadcasts a local user's message
     * to all the remote chat members, and receive a message from each of them.
     *
     * @param port  IP port used to connect to a remote node as well as to
     *              accept a connection from a remote node.
     * @param rank  this local node's rank (one of 0 through to #members - 1)
     * @param hosts a list of all computing nodes that participate in chatting
     */
    public Chat( int port, int rank, String[] hosts ) throws IOException {
	// print out my port, rank and local hostname
	System.out.println( "port = " + port + ", rank = " + rank +
			    ", localhost = " + hosts[rank] );

	// create sockets, inputs, outputs, and vector arrays
	sockets = new Socket[hosts.length];
	indata = new InputStream[hosts.length];
	inputs = new ObjectInputStream[hosts.length];
	outputs = new ObjectOutputStream[hosts.length];
        
        vector = new int[hosts.length];
        
        //Initialize local vector array
        for(int i = 0 ; i < vector.length; i++)
        {
            vector[i] = 0; 
        }

	// establish a complete network
	ServerSocket server = new ServerSocket( port );
	for ( int i = hosts.length - 1; i >= 0; i-- ) {
	    if ( i > rank ) {
		// accept a connection from others with a higher rank
		Socket socket = server.accept( );
		String src_host = socket.getInetAddress( ).getHostName( );

		// find this source host's rank
		for ( int j = 0; j < hosts.length; j++ )
		    if ( src_host.startsWith( hosts[j] ) ) {
			// j is this source host's rank
			System.out.println( "accepted from " + src_host );

			// store this source host j's connection, input stream
			// and object intput/output streams.
			sockets[j] = socket;
			indata[j]= socket.getInputStream( );
			inputs[j] = 
			    new ObjectInputStream( indata[j] );
			outputs[j] = 
			    new ObjectOutputStream( socket.getOutputStream( ));
		    }
	    }
	    if ( i < rank ) {
		// establish a connection to others with a lower rank
		sockets[i] = new Socket( hosts[i], port );
		System.out.println( "connected to " + hosts[i] );

		// store this destination host j's connection, input stream
		// and object intput/output streams.
		outputs[i] 
		    = new ObjectOutputStream( sockets[i].getOutputStream( ) );
		indata[i] = sockets[i].getInputStream( );
		inputs[i] 
		    = new ObjectInputStream( indata[i] );
	    }
	}

	// create a keyboard stream
	BufferedReader keyboard
	    = new BufferedReader( new InputStreamReader( System.in ) );

	// now goes into a chat
	while ( true ) {
	    // read a message from keyboard and broadcast it to all the others.
	    if ( keyboard.ready( ) ) {
		// since keyboard is ready, read one line.
		String message = keyboard.readLine( );
		if ( message == null ) {
		    // keyboard was closed by "^d"
		    break; // terminate the program
		}
                
                vector[rank]++; // Increment vector for rank
                
		// broadcast a message to each of the chat members.
		for ( int i = 0; i < hosts.length; i++ )
		    if ( i != rank ) {
			// of course I should not send a message to myself
                        outputs[i].writeObject (vector);
			outputs[i].writeObject( message );
			outputs[i].flush( ); // make sure the message was sent
		    }
	    }

	    // read a message from each of the chat members
	    for ( int i = 0; i < hosts.length; i++ ) {
		// to intentionally create a misordered message deliveray, 
		// let's slow down the chat member #2.
		try {
		    if ( rank == 2 )
			Thread.currentThread( ).sleep( 5000 ); // sleep 5 sec.
		} catch ( InterruptedException e ) {}

		// check if chat member #i has something
		if ( i != rank && indata[i].available( ) > 0 ) {
		    // read a message from chat member #i and print it out
		    // to the monitor
		    try {
                        
                        int[] recvVec = ( int [] ) inputs[i].readObject(); 
			String message = ( String )inputs[i].readObject( );
                        
                        
                        //!!NEW CODE HEAVILY BASED ON CODE FROM LECTURE!!
                        
                        //If compared vector is not ready, queue message from
                        // host
                        if (compareMyVector(recvVec) == false)
                        {
                            queue_vec.add( recvVec);
                            queue_msg.add( message);
                            queue_src.add( new Integer(i) );
                        }
                        
			//
		    } catch ( ClassNotFoundException e ) {}
		}
	    }
            
            // Checks to see if the source vector syncs up then outputs 
            // vector from Queue if synced
            for(int i = 0 ; i < queue_vec.size() ; i++)
            {
                if (compareMyVector(queue_vec.elementAt(i)) == true)
                {
                    int[] recv_vec = queue_vec.remove(i);
                    String message = queue_msg.remove(i);
                    int src = (queue_src.remove(i)).intValue(); 
                    
                    vector[src]++; // increment local vector from rank
                    
                    System.out.println( hosts[i] + ": " + message );
                }
            }
        }
    }
    
    boolean compareMyVector(int[] srcVector)
    {/**
     * Compares a source vector with the local vectors and returns true if the 
     * srcVector is at least one larger than each of the local elements, 
     * otherwise returns false. 
     * 
     * This function 
     * 
     * @param srcVector Source vector to be compared. 
     */
        
        boolean equal = true; 
        
        for(int i = 0; i < srcVector.length ; i++)
        {
            if(srcVector[i] > vector[i] + 1) // return false if not synced
            { 
                equal = false; 
            }
        }
        return equal; 
    }  
    
    /**
     * Is the main function that verifies the correctness of its arguments and
     * starts the application.
     *
     * @param args receives <port> <ip1> <ip2> ... where port is an IP port
     *             to establish a TCP connection and ip1, ip2, .... are a
     *             list of all computing nodes that participate in a chat.
     */
    public static void main( String[] args ) {

	// verify #args.
	if ( args.length < 2 ) {
	    System.err.println( "Syntax: java Chat <port> <ip1> <ip2> ..." );
	    System.exit( -1 );
	}

	// retrieve the port
	int port = 0;
	try {
	    port = Integer.parseInt( args[0] );
	} catch ( NumberFormatException e ) {
	    e.printStackTrace( );
	    System.exit( -1 );
	}
	if ( port <= 5000 ) {
	    System.err.println( "port should be 5001 or larger" );
	    System.exit( -1 );
	}

	// retireve my local hostname
	String localhost = null;
	try {
	    localhost = InetAddress.getLocalHost( ).getHostName( );
	} catch ( UnknownHostException e ) {
	    e.printStackTrace( );
	    System.exit( -1 );
	}

	// store a list of computing nodes in hosts[] and check my rank
	int rank = -1;
	String[] hosts = new String[args.length - 1];
	for ( int i = 0; i < args.length - 1; i++ ) {
	    hosts[i] = args[i + 1];
	    if ( localhost.startsWith( hosts[i] ) ) 
		// found myself in the i-th member of hosts
		rank = i;
	}

	// now start the Chat application
	try {
	    new Chat( port, rank, hosts );
	} catch ( IOException e ) {
	    e.printStackTrace( );
	    System.exit( -1 );
	}
    }
}
