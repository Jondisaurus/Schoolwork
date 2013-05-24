/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author jondi521
 */
public class clientEmacs implements Runnable {
   DFS_Client main; 
    
    public clientEmacs(DFS_Client source){
       main = source; 
    }
    
    
    public void run(){
        try{
            Process run = Runtime.getRuntime()
		.exec("emacs /tmp/" + System.getProperty("user.name") + ".txt");
            System.out.println("Waiting for EMACS to close . . . ");
            run.waitFor();
            
        }catch(InterruptedException e){}
        catch(IOException ex){}
        
       
        try {
            main.emacsClosed();

            //System.exit(0);
        } catch (IOException ex) {
          System.out.println(ex);
        }
        
        
    }
}
