/*
* Main.java
*
*  � Copyright 2001-2004 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/
import com.tplus.transform.runtime.*;
import com.tplus.transform.runtime.io.*;
import java.util.*;
import java.io.*;
import javax.naming.*;
import java.rmi.*;
/**
  * @deprecated This file is no longer applicable for Volante 3.0.  It is generated for compatability 
  * purposes only.
 */
public class Main {
    protected static com.tplus.transform.util.log.Log log = com.tplus.transform.util.log.LogFactory.getLog(Main.class);
    public Main() throws Exception {
        
    }
	void dumpOutputs(TransformContext tcxt) throws TransformException, RemoteException, IOException {    
        OutputContext outputContext = tcxt.getOutputContext();
        List outputs = outputContext.getOutputNames();
	    for(int i = 0;i < outputs.size();++i) {
	        String outputName = (String)outputs.get(i);
	        System.out.println("***** Output " + outputName + " *****");
	        ByteArrayOutputDevice outputDevice = outputContext.getOutputDevice(outputName);
	        byte[] transformedData = outputDevice.getAsBytes();
	        System.out.println("Length = " + transformedData.length);
	        System.out.write(transformedData);
	        System.out.println();
	    }
	}
    void run(String fileName) throws Exception {
         String outputDeviceName = "testout";
        TransformContext tcxt = new TransformContextImpl();
        LookupContext cxt = getLookupContext();
        tcxt.setProperty(TransformContext.INPUT_SOURCE_PROPERTY, fileName);
        tcxt.setProperty(TransformContext.OUTPUT_FORMAT_PROPERTY, "${OutputFormat}");
        tcxt.setProperty(TransformContext.OUTPUT_PROTOCOL_PROPERTY, "contextprotocol");
        tcxt.setProperty(TransformContext.OUTPUT_DEVICE_PROPERTY, outputDeviceName);

        try {
            InputFormat inputFormat = cxt.lookupInputFormat("${InputFormat}");
            FileInputSource fis = new FileInputSource(fileName);
			try {
                tcxt.createOutputContext();
                inputFormat.processInput(fis, tcxt);
                OutputContext outputContext = tcxt.getOutputContext();
				dumpOutputs(tcxt);
            }
			catch(TransformException e) {
				//System.err.println(e.toXMLString());
				System.out.println(e.toXMLString());
			}
			finally {
                tcxt.clear();
			}

			//////////////////////////////////////////
			// Give a chance for hotspot compiler
            for(int i = 0;i < 2000;++i) {
                tcxt.createOutputContext();
                inputFormat.processInput(fis, tcxt);
                tcxt.clear();
            }
            System.gc();
            Thread.yield();

			{
				// Parsing
	            long startTime = System.currentTimeMillis();
	            int loopCount = 10000;
	            for(int i = 0;i < loopCount;++i) {
					try {
	                	tcxt.createOutputContext();
	                	inputFormat.getInputParser().parseBatch(fis, tcxt);
					}
					catch(Exception e) {
						// ignore
					}
					finally {
	                	tcxt.clear();
					}
	            }
	            long endTime = System.currentTimeMillis();
	            System.out.println("Elapsed time        = " + (endTime - startTime));
				double transformationRate = ((double)loopCount) * 1000 / (endTime - startTime);
				double throughput = transformationRate * (fis.getAsBytes().length)/1000; 
	            System.out.print("Parsings/sec = " + Math.round(transformationRate));
	            System.out.println(", Data Parsed/sec = " + Math.round(throughput) + "KB");
	            System.gc();
	            Thread.yield();
			}

			//////////////////////////////////////////
			// Timing
            long startTime = System.currentTimeMillis();
            int loopCount = 10000;
            for(int i = 0;i < loopCount;++i) {
				try {
                	tcxt.createOutputContext();
                	inputFormat.processInput(fis, tcxt);
				}
				catch(Exception e) {
					// ignore
				}
				finally {
                	tcxt.clear();
				}
            }
            long endTime = System.currentTimeMillis();
            System.out.println("Elapsed time        = " + (endTime - startTime));
			double transformationRate = ((double)loopCount) * 1000 / (endTime - startTime);
			double throughput = transformationRate * (fis.getAsBytes().length)/1000; 
            System.out.print("Transformations/sec = " + Math.round(transformationRate));
            System.out.println(", Data Processed/sec = " + Math.round(throughput) + "KB");
        }
        catch(Exception e) {
            String errorMessage = e.getMessage();
            //e.printStackTrace();
			e.printStackTrace(System.out);
        }
    }
    
    private static LookupContext getLookupContext() throws NamingException {
        return LookupContextFactory.getLookupContext();
    }
    
    public static void main(String args[]) throws Exception {
		com.tplus.transform.util.LoggingUtil.enableLogging("log.xml");
        Main client = new Main();
        log.info("Processing ... ");
        String fileName = "data.txt";
        if(args.length > 0) {
            fileName = args[0];
        }
        client.run(fileName);
        System.exit(0);
    }
}
