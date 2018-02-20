/*
* Main.java
*
*  © Copyright 2001-2004 Volante Technologies, Inc.
*  All rights reserved.
*
*  This software is the confidential and proprietary information of Volante
*  Technologies Inc. Your use of this software is governed by the terms of the
*  license agreement and/or any nondisclosure agreements you have entered
*  into with Volante.  This software may not be disseminated, distributed
*  or otherwise disclosed without the prior, written permission of Volante.
*/
package test;

import com.tplus.transform.runtime.*;
import com.tplus.transform.runtime.io.*;
import java.util.*;
import java.io.*;
import javax.naming.*;
import java.rmi.*;
import com.tplus.transform.util.ArrayUtils;
import com.tplus.transform.runtime.external.client.StaticContextOutputDeviceFactory;
import com.tplus.transform.runtime.external.client.DeviceHelper;
import com.tplus.transform.util.SequencedHashMap;

public class PerfMain {
    private static int _loopCount = 10000; 
    
    public PerfMain() throws Exception {
        
    }

	private void populateOutputDeviceResult(StaticContextOutputDeviceFactory outputDeviceFactory, Map fieldAndValueMap, Map fieldAndTypeMap) throws TransformException, RemoteException {
		Map result = new SequencedHashMap();
		DeviceHelper.populateResult(outputDeviceFactory, result);
		List outputDeviceNames = new ArrayList(result.keySet());
		for (int i=0; i < outputDeviceNames.size(); ++i) {
			String outputDeviceName = (String)outputDeviceNames.get(i);
			Object deviceOutput = result.get(outputDeviceName);
			fieldAndValueMap.put(outputDeviceName, deviceOutput);
			fieldAndTypeMap.put(outputDeviceName, DesignerTypes.DESIGNER_BINARY_TYPE);
		}		
	}

    public void simpleTesting(MessageFlow messageFlow, DataObject inputDataObject, Map fieldAndValueMap, Map fieldAndTypeMap) throws NamingException, TransformException, IOException {
		StaticContextOutputDeviceFactory outputDeviceFactory = DeviceHelper.prepareDevices(messageFlow);
        DataObject outputDataObject = messageFlow.run(inputDataObject, new TransformContextImpl());		
		for (int i=0; i < outputDataObject.getFieldCount(); ++i) {
			String fieldName = outputDataObject.getFieldName(i);
			String fieldType = outputDataObject.getFieldType(i);
			Object fieldValue = outputDataObject.getField(fieldName);
			fieldAndValueMap.put(fieldName, fieldValue);
			fieldAndTypeMap.put(fieldName, fieldType);
		}
		DeviceHelper.finishDevices(messageFlow);
		populateOutputDeviceResult(outputDeviceFactory, fieldAndValueMap, fieldAndTypeMap);
    }

    public long perfTesting(MessageFlow messageFlow, DataObject inputDataObject) throws NamingException, IOException, TransformException {
        int loopCount = _loopCount;

        long start = System.currentTimeMillis();
        for (int i = 0; i < loopCount; ++i) {
			simpleTesting(messageFlow, inputDataObject, new SequencedHashMap(), new SequencedHashMap());
        }
        long end = System.currentTimeMillis();
        long timeTaken = (end - start);
        return (long)(loopCount / ((double) timeTaken / 1000));
    }    
}
