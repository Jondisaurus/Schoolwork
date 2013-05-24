/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author jondi521
 */
import java.rmi.*;
import java.util.*;

public interface ClientInterface extends Remote {
    public boolean invalidate() throws RemoteException;
    public boolean writeback() throws RemoteException;
}
