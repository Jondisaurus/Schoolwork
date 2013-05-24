//Kyle Morrison and Jon Di Francesco
//DFS_Client Class
//This class is the client file that interacts with the DFS_Server and allows
// file editing via emacs

import java.io.*;
import java.net.UnknownHostException;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author jonathan Difrancesco
 */
public class DFS_Client extends UnicastRemoteObject implements ClientInterface{
    
    String fileName;
    String accessMode;
    String userName;
    String filePath;
    boolean owner;
    int state; 
    boolean emacOpen;
    Process run; 
    File cache; 
    Thread T; 
    static String serverIP;
    static int port; 
    String myIP; 
    String fileToUpload; 
    
    
    public final int INVALID = 0;
    public final int WRITE_OWNED = 1;
    public final int READ_SHARED = 2; 
    public final int RELEASE_OWNERSHIP = 3;
    
    static final int EMACSCLOSED = 0;
    static final int EMACSOPEN = 1; 
    static final int NEWEMACS = 2;

    //user input
    
    public DFS_Client() throws RemoteException{
        userName = System.getProperty("user.name");
        filePath = ("/tmp/" + userName + ".txt");
        cache = null;
        state = INVALID;
        fileName = "";
        
        try {
            myIP = java.net.InetAddress.getLocalHost().getHostName();
            getCache();
            //getUserInput();
        } catch (UnknownHostException ex) {System.out.println(ex);}
          catch (IOException e) {System.out.println(e);}
    }
    private void getUserInput() throws IOException{
        // Sets the fileName and accessMode variables to be used in operation

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));      
        String curr;  
        boolean runAgain = true;
        System.out.println("FileClient: Next file to open");
        System.out.print("      File Name:  ");
        curr = fileToUpload = fileName;
        
        fileName = br.readLine();
        if(!curr.matches(fileName)){
            System.out.println("      file: " + fileName + " not cached");
            if(state == WRITE_OWNED || state == RELEASE_OWNERSHIP){
                uploadFile(); // release ownership and upload file
            }
                
            state = INVALID;
        }
        else{
            System.out.println("      file: " + fileName + " IS cached");
            //dont copy that floppy
            state = READ_SHARED; 
        }
        
        
        while(runAgain){ // validate accessMode input
            System.out.print("      How(r/w):  ");
            accessMode = br.readLine(); 

            if(!(accessMode.matches("r") || accessMode.matches("w"))){
                System.out.println("Invalid action: input again");
            }
            else{runAgain = false;}
        }
        
        
        if(accessMode.matches("r")){ // if reading, set state to read 
            if(state == INVALID){
                downloadFile(); 
            }
            state = READ_SHARED; 
            owner = false;
            emacsStart();
        }
        else{ 
            if(state == INVALID || state == READ_SHARED){
                downloadFile(); 
            }
            
            state = WRITE_OWNED; // otherwise, set set to Write
            owner = true;
            emacsStart();
        }
        
   
        System.out.println("name = " + fileName + " state = " + state +
                " Ownership = " + owner);
    }
    
    public synchronized void emacsClosed() throws IOException{
        ///emacs is closed stuff goes here
        //if(state == RELEASE_OWNERSHIP || state == WRITE_OWNED){ 
            // release ownership
            fileToUpload = fileName; 
            uploadFile(); 
            state = READ_SHARED; 
        if(state == INVALID){
            downloadFile();
        }; 
        
        if(T.isAlive()){ 
            //T.stop();
            T = null;
        }

        System.out.println("File closed in EMACS.");
        getUserInput();       
    }
    
    private boolean getCache() throws IOException{
        // Returns false if the file was not found and was created.    
        cache = new File(filePath);
        boolean cacheCreated = cache.createNewFile(); 
        return cacheCreated; 
    }
    private void downloadFile() throws IOException{
        //download current file from server
        if(cache == null){
            getCache();
        }
        OutputStream out = new FileOutputStream(filePath);
        try{
             System.out.println("Connected to: " + serverIP);
             ServerInterface server = //Connect to server in args
                  (ServerInterface)Naming.lookup
                  ( "rmi://" + serverIP + ":"+ port +"/DFS_Server");
            System.out.println("Debug stuff: "+myIP+" "+fileName+" "
                    +accessMode);

            FileContents fileC = server.download(myIP, fileName, accessMode);
            
            out.write(fileC.get()); 
         }catch(NotBoundException e){System.out.println(e);}
          catch(RemoteException ex){System.out.println(ex);}
    }
    
    private void clearFile() throws IOException{
        if(cache.delete()){
            System.out.println(cache.getName() + " is deleted!");
            getCache();
        }else{
            System.out.println("Delete operation is failed.");
        }
    }
    private boolean uploadFile() throws IOException{
        boolean uploadCompleted = false;
        byte[] input = new byte[(int)cache.length()];
        
        if(cache == null){
            System.out.println("ERROR Cache File not found!");
            return false;
        }
        InputStream in = new FileInputStream(filePath);
        in.read(input);
        System.out.println("input == " + input.toString());
        
        try{
             System.out.println("Connected to: " + serverIP);
             ServerInterface server = //Connect to server in args
                  (ServerInterface)Naming.lookup
                  ( "rmi://" + serverIP + ":"+ port +"/DFS_Server");
             FileContents upload = new FileContents(input);
            
             System.out.println("Debug stuff: "+myIP+" "+fileToUpload);
             upload.print(); 
            
             uploadCompleted = server.upload(myIP, fileToUpload, upload);
            
             if(!uploadCompleted){
                 System.out.println("ERROR uploading " + fileToUpload + "!");
             }
             else{
                 System.out.println("uploading: " + fileToUpload 
                         + " completed");
             }
         }catch(NotBoundException e){System.out.println(e);}
          catch(RemoteException ex){System.out.println(ex);}    
        if(uploadCompleted)
        {
            state = READ_SHARED;
            owner = false; 
        }
        return uploadCompleted; 
    }

    private boolean emacsStart(){
        //false = thread not started, true = thread started
        if(T != null){
            if(!T.isAlive())
            {
                T = null; 
            }
            else return false; 
        }
        else{
            T = new Thread(new clientEmacs(this), userName + "_EmacsThread");
            T.start();
            return true;
        }
        return false; //default
    }
    
    public synchronized boolean invalidate(){
        state = INVALID;
        return true;
    }
    
    public synchronized boolean writeback(){
        if(state == 1 || state == 3){
            try {
                state = 3;
                
                uploadFile();
                return true;
            } catch (IOException ex) {
            }
        }
        System.out.println("sent out writeback");
        return true;
    } 
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        if ( args.length < 2 ) { 
	    System.err.println( "usage: java DFS_Client port "
                    + "ip-address" );
	    System.exit( -1 );
        }
        
        port = Integer.parseInt(args[0]);
        serverIP = args[1];
        try {
            DFS_Client client = new DFS_Client();
            Naming.rebind("rmi://localhost:" + port + "/DFS_Client", client);
            client.getUserInput();
        } catch (RemoteException ex) {
            Logger.getLogger(DFS_Client.class.getName()).log(Level.SEVERE, 
                    null, ex);
        }catch (Exception e)
        {
            e.printStackTrace();
            System.exit(1);
        }
        
    }
}
