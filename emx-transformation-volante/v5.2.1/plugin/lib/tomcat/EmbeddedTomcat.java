import java.net.URL;
import org.apache.catalina.connector.Connector;
import org.apache.catalina.Context;
//import org.apache.catalina.deploy.Deployer;
import org.apache.catalina.Engine;
import org.apache.catalina.Host;
//import org.apache.catalina.logger.SystemOutLogger;
import org.apache.catalina.startup.Embedded;
import org.apache.catalina.Container;
public class EmbeddedTomcat {
    private String path = null;
    private Embedded embedded = null;
    private Host host = null;
    /**
    * Default Constructor
    *
    */
    
    public EmbeddedTomcat() {
        
    }
    /**
    * Basic Accessor setting the value of the context path
    *
    * @param path - the path
    */
    
    public void setPath(String path) {
        this.path = path;
    }
    /**
    * Basic Accessor returning the value of the context path
    *
    * @return - the context path
    */
    
    public String getPath() {
        return path;
    }
    /**
    * This method Starts the Tomcat server.
    */
    
    public void startTomcat() throws Exception {
        Engine engine = null;
        // Set the home directory
        System.setProperty("catalina.home", getPath());
        // Create an embedded server
        embedded = new Embedded();
        // print all log statments to standard error
        //embedded.setDebug(0);
        //embedded.setLogger(new SystemOutLogger());
        // Create an engine
        engine = embedded.createEngine();
        engine.setDefaultHost("localhost");
        // Create a default virtual host
        host = embedded.createHost("localhost", getPath() + "/webapps");
        engine.addChild(host);
        // Create the ROOT context
        Context context = embedded.createContext("", getPath() + "/webapps/ROOT");
        host.addChild(context);
        // Install the assembled container hierarchy
        embedded.addEngine(engine);
        // Assemble and install a default HTTP connector
        Connector connector = embedded.createConnector((String)null, 8070, false);
        embedded.addConnector(connector);
        // Start the embedded server
        embedded.start();
    }
    /**
    * This method Stops the Tomcat server.
    */
    
    public void stopTomcat() throws Exception {
        // Stop the embedded server
        embedded.stop();
    }

    public void registerWAR(String contextPath, String warFile) throws Exception {
        if(contextPath == null) {
            throw new Exception("Invalid Path : " + contextPath);
        }
        if(contextPath.equals("/")) {
            contextPath = "";
        }
        if(warFile == null) {
            throw new Exception("Invalid WAR : " + warFile);
        }
        Context context = embedded.createContext(contextPath, warFile);
        host.addChild(context);

    }

    /**
    * Registers a WAR with the container.
    *
    * @param contextPath - the context path under which the
    *               application will be registered
    * @param warFile - the URL of the WAR to be
    * registered.
    */
    /*
    public void registerWAR(String contextPath, URL warFile) throws Exception {
        if(contextPath == null) {
            throw new Exception("Invalid Path : " + contextPath);
        }
        if(contextPath.equals("/")) {
            contextPath = "";
        }
        if(warFile == null) {
            throw new Exception("Invalid WAR : " + warFile);
        }
        Deployer deployer = (Deployer)host;
        Context context = deployer.findDeployedApp(contextPath);
        if(context != null) {
            throw new Exception("Context " + contextPath + " Already Exists!");
        }
        deployer.install(contextPath, warFile);
    }*/
    /**
    * Unregisters a WAR from the web server.
    *
    * @param contextPath - the context path to be removed
    */
    /*
    public void unregisterWAR(String contextPath) throws Exception {
        Context context = host.map(contextPath);
        if(context != null) {
            embedded.removeContext(context);
        }
        else {
            throw new Exception("Context does not exist for named path : " + contextPath);
        }
    }*/
    
    public static void main(String args[]) {
        try {
            EmbeddedTomcat tomcat = new EmbeddedTomcat();
			String path = new java.io.File(".").getAbsolutePath();
            tomcat.setPath(path);
            tomcat.startTomcat();
            //URL url = new URL("file:D:/jakarta-tomcat-4.0.1" + "/webapps/onjava");
            //tomcat.registerWAR("/onjava", url);
            //URL url = new URL("file:G:/java/apache-tomcat-5.5.27/webapps/servlets-examples");
            tomcat.registerWAR("/onjava", "F:/Volante3.51/Cartridges/Webform/App/testwebapp");
            Thread.sleep(1000000);
            tomcat.stopTomcat();
            System.exit(0);
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }
}
