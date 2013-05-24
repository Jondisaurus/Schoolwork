/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.*;
/**
     * QueueNode
     * ---------
     * 
     * Container class that holds monitors and functions as a queue/thread 
     * container for the SyncQueue class. 
     * 
     * This was written by Jonathan Difrancesco November 2012 to fit 
     * the specifications for the Program 3 assignment for CSS430 fall 12' 
     * 
     * @author Jon Difrancesco
     * 
     */

public class QueueNode {    
    public Vector q;
    
    QueueNode() 
    {/**
     * Default constructor
     */
        q = new Vector<Integer>();       
    }

    public synchronized int sleep()
    {/**
     * Adds the Thread to the Queue. 
     */ 
        try{
            wait(); 
        }catch(InterruptedException e){}
        
        int caller = (Integer)q.firstElement();
        q.remove(caller);
        return caller; 
    }
    
    public synchronized void wakeup(int tid)
    {/**
     * Adds the calling threads tid to the queue and awakens the 
     * next thread in the monitor
     */ 
        q.add(tid);
        notify();
    }
 
}

/* DEBUG CODE */