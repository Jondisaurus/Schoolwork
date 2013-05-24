/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import mpi.*; 
/**
 *
 * @author jondi521
 */
public class MPITest {
      
    public MPITest()
    {
    
        double[] array = new double[100]; 
        
        
        
        
        if (rank == 0)
        {
            for( int i = 0; i < 100; i++)
            {
                array[i] = i; 
            }
            
            for( int i = 1; i <= 3; i++)
            {
                MPI.COMM_WORLD.send (array, 25 * i, 25, MPI.DOUBLE, i, 0)
            }
        }
        else 
        {
            MPI.COMM_WORLD.recv(array,0,25,MPI.DOUBLE,0,0);
        }
        
        for(int i = 0; i < 25; i ++)
        {
            array[i]= Math.sqrt(array[i]);
        }
        
       
    }
    
    public static void main ( String args[] )  
    {/**
     *
     */
       
    }
}
 

