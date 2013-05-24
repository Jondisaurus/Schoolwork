

import java.rmi.*;
import java.util.*;

public interface ServerInterface extends Remote {
    public FileContents download(String myIpName, String filename, String mode) throws RemoteException;
    
    
    
    public boolean upload(String myIpName, String filename, FileContents contents) throws RemoteException;
}