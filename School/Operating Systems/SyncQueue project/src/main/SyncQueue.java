r/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author jondi521
 */
public class SyncQueue {
    
    private final int _defaultNumConditions = 10;
    private QueueNode[] queue; // holds the Queue with the waiting threads
    


    public SyncQueue()
    {/**
     * Create array with default numbers of conditions
     * 
     */
        queue = new QueueNode[_defaultNumConditions]; 
    }
    
    public SyncQueue(int condMax)
    {
        queue = new QueueNode[condMax];
    }
    
    public int enqueueAndSleep(int condition)
    {/**
     * 
     * Test cases
     * - check to make sure threads go into right spots
     * - have each thread announce their thread after getting stored
     * 
     * -announce when threads are awoke, asleepened. 
     * 
     * More like Sleep and Enque amirite? No, you arent
     */        
        
        
        return queue[condition].sleep();
        
    }
    
    public void dequeueAndWakeup(int condition, int tid)
    {/**
     * 
     * Same and enque really, make sure things announce what happened when spawned. 
     */
       queue[condition].wakeup(tid);
        
    }
    
    public void dequeueAndWakeup(int condition)
    { 
       queue[condition].wakeup(0);
   
    }
    
    
    
    
    
}
