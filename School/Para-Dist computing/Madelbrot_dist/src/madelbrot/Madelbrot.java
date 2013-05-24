
/**
 * SOURCES: The Madelbrot code is partially adapted from the algorithm found
 * from http://warp.povusers.org/Mandelbrot/ 
 * 
 * The code for this lab is also based off the MatrixMult code supplied as
 * an example with the assignment. 
 * 
 * This program divides up a Madelbrot program into multiple slices and sends it
 * to other systems via MPI and Prunjava
 * 
 * ASSUMPTIONS:
 * 
 * This code will only work with select number of computers due to shortage
 * of implementation time,
 * 
 * This program is tested to work with 1,2,4,8 computers. 
 * 
 * The program is pretty straight forward, only requiring the command
 * prunjava #computers Madelbrot to start. 
 * 
 * @author Jonathan Difrancesco - 10/26/12
 */
//package madelbrot;
import java.net.InetAddress; // for host name
import java.net.UnknownHostException;
import mpi.MPI; 
import mpi.MPIException; 


import java.util.*;

/**
 *
 * @author jondi521
 */
public class Madelbrot {
    private static boolean graph[]; //Main graph that stores if point is in set
    private static boolean graphRun[]; // Graph that works with sent pieces
    //NOTE: The arrays are set up as one dimension then handled using 
    // multiplication and division to run as a 2-d array
    
    private static int ImageHeight = 80; // Height of graph
    private static int ImageWidth = 80; // Width of graph
 
    //Variables that handle complex numbers used in the main algorithm. 
    double MinRe = -2.0;
    double MaxRe = 1.0;
    double MinIm = -1.2;
        
    double MaxIm = MinIm+(MaxRe - MinRe) * ImageHeight/ImageWidth;
    double Re_factor = (MaxRe-MinRe) / (ImageWidth-1);
    double Im_factor = (MaxIm-MinIm) / (ImageHeight-1);
    int MaxIterations = 30;
    int mtype; 
    
    final static int tagFromMaster = 1;
    final static int tagFromSlave = 2;
    final static int master = 0;
    
    
    public Madelbrot() throws MPIException {
        /**
         * Madelbrot Main class of program. Handles setting up MPI computers
         * and processing the rows into an array then sending the rows off to
         * be checked to see if they fit in the madelbrot set. 
         */
        
        //Set up MPI components
        int myrank = 0;
        int nprocs = 0;
        boolean row[] = new boolean[ImageWidth];

        myrank = MPI.COMM_WORLD.Rank();
        nprocs = MPI.COMM_WORLD.Size(); 
        
        int toSend = (ImageHeight) / nprocs; 
            // Tells number of rows to divide process into
        
        
        graph = new boolean[ImageHeight * ImageWidth]; 
            //Array that holds whether a current point is within the set
        graphRun = new boolean[ImageHeight * ImageWidth];
            // Arrray that holds the data coming in/out from other arrays
        
        
        //Initialize array with all blank chars
        for(int i = 0; i < ImageWidth * ImageHeight; i++)
        {
            graph[i] = false;
            graphRun[i] = false;
        }
        
        if(myrank == 0)
        { // IM THE MASTER   
            Date startTime = new Date(); // Start of processing time check     
            mtype = tagFromSlave; 

            // get rows ready to send
            processRow(toSend * myrank, toSend); // Process this ranks rows
            System.arraycopy(graphRun, 0, graph, 0, (toSend * ImageHeight));
            //copy points into array
            
            
            for ( int source = 1; source < nprocs; source++)
            {// This loop grabs the graphRun array from each rank 
             // then copies them into the main Graph array.
                MPI.COMM_WORLD.Recv(graphRun, 
                        ( ImageHeight * source * toSend), 
                        (toSend * ImageHeight), MPI.BOOLEAN, source, mtype);
                System.arraycopy(graphRun, ( ImageHeight * source * toSend), 
                        graph, ( ImageHeight * source * toSend), 
                        (toSend * ImageHeight));
            }

            Date endTime = new Date(); // end of processing time
        
            System.out.println( "time elapsed = " +
				( endTime.getTime( ) - startTime.getTime( ) ) +
				" msec" ); 
 
            try {
                // Print out a complication message.
                InetAddress inetaddr = InetAddress.getLocalHost( );
                String ipname = inetaddr.getHostName( );
                System.out.println( "rank[" + myrank + "] at " + ipname + 
                                  " completed processing " + toSend + " rows" );
            } catch ( UnknownHostException e ) {
                System.err.println( e );
            }
            showGraph(); //output Graph array
            
        }
        else{ // ...im a slave
             mtype = tagFromSlave; 
            
             processRow(toSend * myrank, toSend); // process this ranks rows
            
             MPI.COMM_WORLD.Send(graphRun, (myrank * toSend * ImageHeight), 
                     (toSend * ImageHeight), MPI.BOOLEAN, 0, mtype);
             //Return processed rows to main funtion
             
           try {
                // Print out a complication message.
                InetAddress inetaddr = InetAddress.getLocalHost( );
                String ipname = inetaddr.getHostName( );
                System.out.println( "rank[" + myrank + "] at " + ipname + 
                                  " completed processing " + toSend + " rows" );
            } catch ( UnknownHostException e ) {
                System.err.println( e );
            }
            
        }     
    }/// END OF MANDELBROT CLASS
    
    
    public void processRow(int yStart, int numProcess)
    {/**
     * Process supplied rows through the Madelbrot algorithm and if found in set
     * set them as true in the graph
     */ 
        
        //int y = yStart * numProcess; 
        System.out.println("Ystart = " + yStart + " NumProc = " + numProcess);

        for(int y = yStart; y < (yStart + numProcess); y++)
        {
            
            double c_im = MaxIm - y*Im_factor;
            for(int x=0; x<ImageWidth; ++x)
            {
                double c_re = MinRe + x * Re_factor;

                double Z_re = c_re, Z_im = c_im;
                boolean isInside = true;
                for(int n=0; n<MaxIterations; ++n)
                {
                    double Z_re2 = Z_re * Z_re, Z_im2 = Z_im * Z_im;
                    if(Z_re2 + Z_im2 > 4)
                    {
                        isInside = false;
                        break;
                    }
                    Z_im = 2 * Z_re * Z_im + c_im;
                    Z_re = Z_re2 - Z_im2 + c_re;
                }
                if(isInside) { graphRun[x + (ImageHeight * y)] = true; }
                // Sets point in the graph to true if found
                
            }  
        }
    }
 
    public void showGraph() // Displays the rendered graph t
    { /**
     * Output graph and changes spaces to '.'s if found in set
     */
        for(int i = 0; i < (ImageHeight * ImageWidth); i++)
        {
            
            if(graph[i]) 
                {System.out.print(".");} // Print . if is in set
            else
                {System.out.print(" ");} // print ' ' if not in set
            if(i % ImageHeight == 0) // divides out the rows to be processed
                {System.out.print("||\n||");}
        }
        System.out.print("||\n");
        
    }
    
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws MPIException {
       /**
        * Starts the Madelbrot program after checking args
        * 
        */ 
       if (args.length != 1)
       {
           System.out.println( "To start: prunjava 5 Mandelbrot");
           System.exit(-1);
       }
      
       int size[] = new int[1];
       MPI.Init( args );  
       new Madelbrot();  
       MPI.Finalize();
    }
}
