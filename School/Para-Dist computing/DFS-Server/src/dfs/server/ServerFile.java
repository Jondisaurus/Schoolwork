import java.util.Vector;

//Contains information for a single file and it's user / state information
//This class allows all of the information for a single file to be maintainted
// within it's own class, which includes the file, the filename, the list of 
// readers, the owner, the state, and the FileContents
public class ServerFile 
{
    final int Not_Shared = 0;
	
    private int state;
    private String filename;
    private Vector<String> listOfReaders;
    private String owner;
    private FileContents contents; 
    	
    public 
    ServerFile(FileContents fileContents, String fileName) {
    	this.contents = fileContents;
    	this.filename = fileName;
    	this.state = Not_Shared;
    	this.listOfReaders = new Vector<String>();
    	this.owner = "null";
    }
    
    public
    void setOwner(String ownerSet){
        this.owner = ownerSet ;
    }

    public
    String getFilename() {
	return this.filename;
    }

    public
    void addReader(String reader) {
    	listOfReaders.add(reader);
    }
    
    public 
    int length(){
        return (contents.get()).length;
    }
    
    public
    void removeReader(String reader) {
    	listOfReaders.remove(reader);
    }
    
    public
    Vector<String> getAllReaders() {
    	return listOfReaders;
    }
   
    public 
    void changeOwner(String owner) {
    	this.owner = owner;
    }
    
    public
    String getOwner() {
    	return this.owner;
    }
    
    public 
    int getState() {
    	return this.state;
    }
    
    public
    void changeState(int state) {
    	this.state = state;
    }

    public 
    void setContents(FileContents contents) {
    	this.contents = contents;
    }
    
    public
    FileContents getContents() {
    	return this.contents;
    }
}
