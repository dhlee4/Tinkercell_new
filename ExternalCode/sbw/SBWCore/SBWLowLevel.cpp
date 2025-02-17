/**
 * @file SBWLowLevel.cpp
 * @brief SBWLowLevel class implementation - low level interface API for SBW uses integers to represent objects etc
 * @author SBW Development Group <sysbio-team@caltech.edu>
 *
 * Organization: Caltech ERATO Kitano Systems Biology Project
 *
 * Created: @date 18th June 2001
 * $Id: SBWLowLevel.cpp,v 1.4 2008/07/13 19:12:53 fbergmann Exp $
 * $Source: /cvsroot/sbw/core/SBWCore/SBWLowLevel.cpp,v $
 */

/*
** Copyright 2001 California Institute of Technology and
** Japan Science and Technology Corporation.
** 
** This library is free software; you can redistribute it and/or modify it
** under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation; either version 2.1 of the License, or
** any later version.
** 
** This library is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
** MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  The software and
** documentation provided hereunder is on an "as is" basis, and the
** California Institute of Technology and Japan Science and Technology
** Corporation have no obligations to provide maintenance, support,
** updates, enhancements or modifications.  In no event shall the
** California Institute of Technology or the Japan Science and Technology
** Corporation be liable to any party for direct, indirect, special,
** incidental or consequential damages, including lost profits, arising
** out of the use of this software and its documentation, even if the
** California Institute of Technology and/or Japan Science and Technology
** Corporation have been advised of the possibility of such damage.  See
** the GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public License
** along with this library; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
**
** The original code contained here was initially developed by:
**
**     Andrew Finney, Herbert Sauro, Michael Hucka, Hamid Bolouri
**     The Systems Biology Workbench Development Group
**     ERATO Kitano Systems Biology Project
**     Control and Dynamical Systems, MC 107-81
**     California Institute of Technology
**     Pasadena, CA, 91125, USA
**
**     http://www.cds.caltech.edu/erato
**     mailto:sysbio-team@caltech.edu
**
** Contributor(s):
**
*/

// SBWLowLevel.cpp: implementation of the SBWLowLevel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SBWLowLevel.h"

#include "SBWModuleRPC.h"
#include "SBWServiceNotFoundException.h"
#include "Signature.h"
#include "MethodInline.h"
#include "ServiceInline.h"
#include "ModuleInline.h"
#include "SignatureElement.h"
#include "SBWListenerForC.h"
#include "SBWListenerConsolidator.h"

using namespace SystemsBiologyWorkbench ;

/// maintains the set of listeners inserted via the API and forwards events to them
SBWListenerConsolidator SBWLowLevel::listenerConsolidator ;

/** 
 * the underlying RPC used by the C and C++ client library
 */
SBW_API SBWRPC *SBWLowLevel::rpc = new SBWModuleRPC(&listenerConsolidator);

/// the callback object for the C API
SBWListenerForC *SBWLowLevel::listenerForC = NULL ;

/// C and C++ library version 
const std::string SBWLowLevel::version = "2.4.1"; //////////////// <<<< modify this <<<<<

SBWRPCListener *SBWLowLevel::getListenerConsolidator()
{
	return &listenerConsolidator;
}

void SBWLowLevel::setMasterListener(SBWRPCListener *l)
{
	rpc->setListener(l);
}

/**
 * returns the version of the C & C++ library
 * @return the version of the C & C++ library
 */
SBW_API std::string SBWLowLevel::getVersion()
{
	return version ;
}

/**
 * returns the version of the Broker
 * @return the version of the Broker
 */
SBW_API std::string SBWLowLevel::getBrokerVersion()
{
	std::string result ;

	//getBrokerMethod(
	//	"string getVersion()").call(DataBlockWriter()) >> result ;
	getBrokerMethod(
		GetVersion).call(DataBlockWriter()) >> result ;

	return result ;
}

/**
 * sets the incoming call processor for the underlying rpc mechanism.
 * @param t the incoming call processor for this module.
 */
SBW_API void SBWLowLevel::setReceiver(Receiver *r) { rpc->registerReceiver(r); }

/**
 * returns module descriptors for all the modules known to the broker.
 * the result should be deallocated using delete.
 * @param includeRunning the result should include running but unregistered modules.
 * @return module descriptors for all the modules known to the broker.
 */
SBW_API std::vector<ModuleDescriptor> *SBWLowLevel::getModuleDescriptors(bool includeRunning, bool localOnly)
{
	std::vector<DataBlockReader> lists ;
	
	//getBrokerMethod("{}[] getModuleDescriptors(boolean, boolean)").
	//	call(DataBlockWriter() << localOnly << includeRunning) >> lists ;
	getBrokerMethod(GetModuleDescriptors).
		call(DataBlockWriter() << localOnly << includeRunning) >> lists ;
	
	std::vector<ModuleDescriptor> *descriptors =
		new std::vector<ModuleDescriptor>(lists.size());

	unsigned int i = 0 ;
	
	while (i != lists.size())
	{
		(*descriptors)[i] = ModuleDescriptor(lists[i]);
		i++ ;
	}

	return descriptors ;
}

/**
 * returns the top level categories or the sub categrories of a given category.
 * the result should be deallocated using delete.
 * @param category if its empty then this function returns the top level categories
 *                 otherwise returns the sub categrories of a given category.
 */
std::vector<std::string> *SBWLowLevel::getServiceCategories(std::string category)
{
	std::vector<std::string> *result = new std::vector<std::string>();

	//getBrokerMethod(
	//	"string[] getServiceCategories(string)").call(DataBlockWriter() << category) >> *result ;
	getBrokerMethod(
		GetServiceCategories).call(DataBlockWriter() << category) >> *result ;

	return result ;
}

/**
 * return an array of module objects corresponding to a given array of numeric module instance identifiers.
 * @param moduleIds an array of numeric module instance identifiers.
 * @return an array of module objects corresponding to the given array of numeric module instance identifiers.
 */
std::vector<Module> *SBWLowLevel::createModuleArray(const std::vector<Integer>&moduleIds)
{
	std::vector<Module> *modules = new std::vector<Module>(moduleIds.size());

	unsigned int i = 0 ;

	while (i != moduleIds.size())
	{
		(*modules)[i] = Module(moduleIds[i]);
		i++;
	}

	return modules ;
}

/**
 * returns the numeric module instance identifier for this application
 * @return the numeric module instance identifier for this application
 */
SBW_API Integer SBWLowLevel::getThisModule()
{
	return rpc->getModuleId();
}

/**
 * register a callback which is called when this application disconnects from the broker
 * @param x a callback which is called when this application disconnects from the broker
 */
SBW_API void SBWLowLevel::registerShutdownListener(SimpleListener x)
{
	initialiseListenerForC();

	listenerForC->registerShutdownListener(x);
}
/**
 * register a callback which is called when another module disconnects from the broker
 * @param x a callback which is called when another module disconnects from the broker
 */
SBW_API void SBWLowLevel::registerModuleShutdownListener(ModuleListener x)
{
	initialiseListenerForC();

	listenerForC->registerModuleShutdownListener(x);
}
/**
 * register a callback which is called when another module connects to the broker
 * @param x a callback which is called when another module connects to the broker
 */
SBW_API void SBWLowLevel::registerModuleStartupListener(ModuleListener x)
{
	initialiseListenerForC();

	listenerForC->registerModuleStartupListener(x);
}
/**
 * register a callback which is called when the broker's register of modules changes
 * @param x a callback which is called when the broker's register of modules changes
 */
SBW_API void SBWLowLevel::registerRegistrationChangeListener(SimpleListener x)
{
	initialiseListenerForC();

	listenerForC->registerRegistrationChangeListener(x);
}
/**
 * remove a callback which is called when this application disconnects from the broker
 * @param x a callback which is called when this application disconnects from the broker
 */
SBW_API void SBWLowLevel::removeShutdownListener(SimpleListener x)
{
	initialiseListenerForC();

	listenerForC->removeShutdownListener(x);
}
/**
 * remove a callback which is called when another module disconnects from the broker
 * @param x a callback which is called when another module disconnects from the broker
 */
SBW_API void SBWLowLevel::removeModuleShutdownListener(ModuleListener x)
{
	initialiseListenerForC();

	listenerForC->removeModuleShutdownListener(x);
}
/**
 * remove a callback which is called when another module connects to the broker
 * @param x a callback which is called when another module connects to the broker
 */
SBW_API void SBWLowLevel::removeModuleStartupListener(ModuleListener x)
{
	initialiseListenerForC();

	listenerForC->removeModuleStartupListener(x);
}
/**
 * remove a callback which is called when the broker's register of modules changes
 * @param x a callback which is called when the broker's register of modules changes
 */
SBW_API void SBWLowLevel::removeRegistrationChangeListener(SimpleListener x)
{
	initialiseListenerForC();

	listenerForC->removeRegistrationChangeListener(x);
}
/**
 * register a callback which is called when this application disconnects from the broker
 * @param x a callback which is called when this application disconnects from the broker
 */
SBW_API void SBWLowLevel::registerShutdownListenerStdCall(SimpleListenerStdCall x)
{
	initialiseListenerForC();

	listenerForC->registerShutdownListenerStdCall(x);
}

/**
 * register a callback which is called when another module disconnects from the broker
 * @param x a callback which is called when another module disconnects from the broker
 */
SBW_API void SBWLowLevel::registerModuleShutdownListenerStdCall(ModuleListenerStdCall x)
{
	initialiseListenerForC();

	listenerForC->registerModuleShutdownListenerStdCall(x);
}

/**
 * register a callback which is called when another module connects to the broker
 * @param x a callback which is called when another module connects to the broker
 */
SBW_API void SBWLowLevel::registerModuleStartupListenerStdCall(ModuleListenerStdCall x)
{
	initialiseListenerForC();

	listenerForC->registerModuleStartupListenerStdCall(x);
}

/**
 * register a callback which is called when the broker's register of modules changes
 * @param x a callback which is called when the broker's register of modules changes
 */
SBW_API void SBWLowLevel::registerRegistrationChangeListenerStdCall(SimpleListenerStdCall x)
{
	initialiseListenerForC();

	listenerForC->registerRegistrationChangeListenerStdCall(x);
}

/**
 * remove a callback which is called when this application disconnects from the broker
 * @param x a callback which is called when this application disconnects from the broker
 */
SBW_API void SBWLowLevel::removeShutdownListenerStdCall(SimpleListenerStdCall x)
{
	initialiseListenerForC();

	listenerForC->removeShutdownListenerStdCall(x);
}


/**
 * remove a callback which is called when another module disconnects from the broker
 * @param x a callback which is called when another module disconnects from the broker
 */
SBW_API void SBWLowLevel::removeModuleShutdownListenerStdCall(ModuleListenerStdCall x)
{
	initialiseListenerForC();

	listenerForC->removeModuleShutdownListenerStdCall(x);
}

/**
 * remove a callback which is called when another module connects to the broker
 * @param x a callback which is called when another module connects to the broker
 */
SBW_API void SBWLowLevel::removeModuleStartupListenerStdCall(ModuleListenerStdCall x)
{
	initialiseListenerForC();

	listenerForC->removeModuleStartupListenerStdCall(x);
}

/**
 * remove a callback which is called when the broker's register of modules changes
 * @param x a callback which is called when the broker's register of modules changes
 */
SBW_API void SBWLowLevel::removeRegistrationChangeListenerStdCall(SimpleListenerStdCall x)
{
	initialiseListenerForC();

	listenerForC->removeRegistrationChangeListenerStdCall(x);
}

/**
 * create an event listener for the C API if one doesn't exist
 */
void SBWLowLevel::initialiseListenerForC()
{
	if (listenerForC == NULL)
	{
		listenerForC = new SBWListenerForC();
		listenerConsolidator.addListener(listenerForC);
	}
}

/** 
 * returns an array of module instance objects representing all the module instances connected to the broker.
 * Deallocate the result using delete.
 * @return an array of module instance objects representing all the module instances connected to the broker.
 */
SBW_API std::vector<Module> *SBWLowLevel::getExistingModuleInstances()
{
	std::vector<Integer> moduleIds ;

	//getBrokerMethod(
	//	"int[] getExistingModuleInstanceIds()").call(DataBlockWriter()) >> moduleIds ;
	getBrokerMethod(
		GetExistingModuleInstanceIds).call(DataBlockWriter()) >> moduleIds ;

	return createModuleArray(moduleIds);
}

/**
 * returns an array of module instance objects representing all the instances of a given module
 * connected to the broker.
 * Deallocate the result using delete.
 * @param moduleName module identification string
 * @return an array of module instance objects representing all the instances of the given module
 *         connected to the broker.
 */
SBW_API std::vector<Module> *SBWLowLevel::getExistingModuleInstances(std::string moduleName)
{
	std::vector<Module> *modules = getExistingModuleInstances();
	std::vector<Module>::iterator moduleItr = modules->begin();

	while (moduleItr != modules->end())
	{
		if ((*moduleItr).getDescriptor().getName() == moduleName)
			moduleItr++ ;
		else
			moduleItr = modules->erase(moduleItr);
	}

	return modules ;
}

/**
 * returns a module descriptor for a given module
 * @param moduleName module identification string.
 * @param includeRunning return result for a running module if the given module is not registered.
 * @return a module descriptor for a given module
 */
SBW_API ModuleDescriptor SBWLowLevel::getModuleDescriptor(std::string moduleName, bool includeRunning)
{
	DataBlockReader list ;
	
	//getBrokerMethod("{} getModuleDescriptor(string, boolean)").call(
	//			DataBlockWriter() << moduleName << includeRunning) >> list ;
	getBrokerMethod(GetModuleDescriptorString).call(
				DataBlockWriter() << moduleName << includeRunning) >> list ;

	return ModuleDescriptor(list);
}
/**
 * returns an array of local service descriptors that are in a given category.
 * @param category a service category
 * @param recursive include service in subcategories of the given categroy (default true)
 * @return an array of service descriptors that are in a given category
 */
SBW_API std::vector<ServiceDescriptor> *SBWLowLevel::findLocalServices(
	std::string category, bool recursive /* = true */)
{
	std::vector<DataBlockReader> listArray ;

	//getBrokerMethod("{}[] findLocalServices(string,boolean)").call(
	//	DataBlockWriter() << category << recursive) >> listArray ;
	getBrokerMethod(FindLocalServices).call(
		DataBlockWriter() << category << recursive) >> listArray ;

	std::vector<ServiceDescriptor> *result =
		new std::vector<ServiceDescriptor>(listArray.size());

	unsigned int i = 0 ;

	while (i != listArray.size())
	{
		(*result)[i] = ServiceDescriptor(listArray[i]);
		i++ ;
	}

	return result ;
}
/**
 * returns an array of service descriptors that are in a given category.
 * @param category a service category
 * @param recursive include service in subcategories of the given categroy (default true)
 * @return an array of service descriptors that are in a given category
 */
SBW_API std::vector<ServiceDescriptor> *SBWLowLevel::findServices(
	std::string category, bool recursive /* = true */)
{
	std::vector<DataBlockReader> listArray ;

	//getBrokerMethod("{}[] findServices(string,boolean)").call(
	//	DataBlockWriter() << category << recursive) >> listArray ;
	getBrokerMethod(FindServices).call(
		DataBlockWriter() << category << recursive) >> listArray ;

	std::vector<ServiceDescriptor> *result =
		new std::vector<ServiceDescriptor>(listArray.size());

	unsigned int i = 0 ;

	while (i != listArray.size())
	{
		(*result)[i] = ServiceDescriptor(listArray[i]);
		i++ ;
	}

	return result ;
}

/**
 * returns whether one category is a subCategory of another.
 * @param category a service category
 * @param subcategory a service category
 * @returns whether <code>subcategory</code> is a subcategory of <code>category</code>
 */
bool SBWLowLevel::isSubCategory(std::string category, std::string subCategory)
{
	int position = subCategory.find(category) ;

	return position == 0 &&
		(subCategory.length() == category.length() || subCategory[category.length()] == '/');
}

/**
 * connect this application to the broker as a module instance of a given module
 * @param moduleIdentificationName the module identification name of this application.
 * @param hostname the hostname of machine on which you wish to connect, "" implies local
 */
SBW_API void SBWLowLevel::connect(const char *moduleIdentificationName, const char *hostname)
{ rpc->connect(moduleIdentificationName, hostname); }

/**
 * request that the broker connects to a remote broker.  This ensures
 * that the SBW environment appears to be a combination of the facilities
 * of all the linked brokers.  This is the prefered mechanism for accessing
 * remote resources.
 * @param hostname the hostname of machine on which you wish to connect.
 */
SBW_API void SBWLowLevel::link(const char *hostname)
{
	//getBrokerMethod("int linkBroker(string)").call(DataBlockWriter() << hostname) ;
	getBrokerMethod(LinkBroker).call(DataBlockWriter() << hostname) ;
}

/**
 * returns whether this application is connected to the broker.
 * @return whether this application is connected to the broker.
 */
SBW_API bool SBWLowLevel::isConnected()
{
	return rpc->isConnected();
}

/**
 * Convenience function for performing the tasks required for handling
 * the <code>-sbwdebug</code> to an application.  This method must be passed the array of command-line
 * arguments passed to the application.  This method then checks for the
 * presence of <code>-sbwdebug</code> and runs <code>SBWDebug::setTraceMode()</code>.
 * Returns whether the application should either register itself or run as a module based on the command line.
 * @param argc an integer indicating the number of arguments passed to
 * the program on the command line
 * @param argv an array of strings comprising the set of arguments
 * passed to the program on the command line
 * @returns whether the command line contains either <code>-sbwregister</code> or <code>-sbwmodule</code>
 *          ie whether the application should either register itself or run as a module respectively.
 **/
SBW_API bool SBWLowLevel::processArguments(int argc, char* argv[])
{
	int i = 0;
	bool moduleMode = false ;

	while (i != argc)
	{
		if (strcmp(argv[i], "-sbwdebug") == 0)
		{
#ifndef _DEBUG
			std::cerr << "-sbwdebug flag will have no effect.  Use debug library to enable tracing\n";
#endif
			SBWDebug::setTraceMode();
		}
		else if (!strcmp(argv[i], "-sbwregister") || !strcmp(argv[i], "-sbwmodule"))
			moduleMode = true ;


		i++ ;
	}

	return moduleMode ;
}

/**
 * disconnects this application from the broker.
 * Blocks until the disconnection has occured.
 */
SBW_API void SBWLowLevel::disconnect()
{
	try
	{
		rpc->disconnect();
	}
	catch (SBWException *e)
	{
		e->log();
		delete e ;
	}
}

/**
 * blocks until this application has disconnected from the broker.
 */
SBW_API void SBWLowLevel::waitForDisconnect()
{ rpc->waitForDisconnect(); }

/**
 * returns the help string for a given method.
 * @param moduleInstanceId numeric module instance identifier
 * @param serviceId numeric service identifier
 * @param methodId numeric method identifier
 * @return the help string for the given method.
 */
SBW_API std::string SBWLowLevel::methodGetHelpInString(Integer moduleInstanceId, Integer serviceId, Integer methodId)
{
	std::string result ;

	rpc->call(
		moduleInstanceId,
		SBWSystemService,
		SBWGetMethodHelpMethod,
		DataBlockWriter() << serviceId << methodId) >> result ;

	return result;
}

/**
 * returns the help string for a given method.
 * result should be deallocated using SBWFree.
 * @param moduleInstanceId numeric module instance identifier
 * @param serviceId numeric service identifier
 * @param methodId numeric method identifier
 * @return the help string for the given method.
 */
SBW_API char *SBWLowLevel::methodGetHelp(Integer moduleInstanceId, Integer serviceId, Integer methodId)
{
	return resultStringForC(methodGetHelpInString(moduleInstanceId, serviceId, methodId).c_str());
}

/**
 * returns the name of a given method.
 * result should be deallocated using SBWFree.
 * @param moduleInstanceId numeric module instance identifier
 * @param serviceId numeric service identifier
 * @param methodId numeric method identifier
 * @return the name of the given method.
 */
SBW_API char *SBWLowLevel::methodGetName(Integer moduleInstanceId, Integer serviceId, Integer methodId)
{
	return resultStringForC(methodGetNameInString(moduleInstanceId, serviceId, methodId).c_str());
}

/**
 * returns the name of a given method.
 * @param moduleInstanceId numeric module instance identifier
 * @param serviceId numeric service identifier
 * @param methodId numeric method identifier
 * @return the name of the given method.
 */
SBW_API std::string SBWLowLevel::methodGetNameInString(Integer moduleInstanceId, Integer serviceId, Integer methodId)
{
	return Signature(methodGetSignatureInString(moduleInstanceId, serviceId, methodId).c_str()).getName();
}

/**
 * returns the signature parse object for a given method.
 * @param moduleInstanceId numeric module instance identifier
 * @param serviceId numeric service identifier
 * @param methodId numeric method identifier
 * @return the signature parse object of the given method.
 */
SBW_API Signature SBWLowLevel::methodGetSignature(Integer moduleInstanceId, Integer serviceId, Integer methodId)
{
	return Signature(methodGetSignatureInString(moduleInstanceId, serviceId, methodId).c_str());
}

/**
 * returns the signature string for a given method.
 * The result should be deallocated using SBWFree.
 * @param moduleInstanceId numeric module instance identifier
 * @param serviceId numeric service identifier
 * @param methodId numeric method identifier
 * @return the signature string of the given method.
 */
SBW_API char *SBWLowLevel::methodGetSignatureInCharStar(Integer moduleInstanceId, Integer serviceId, Integer methodId)
{
	return resultStringForC(methodGetSignatureInString(moduleInstanceId, serviceId, methodId).c_str());
}

/**
 * returns the signature string for a given method.
 * @param moduleInstanceId numeric module instance identifier
 * @param serviceId numeric service identifier
 * @param methodId numeric method identifier
 * @return the signature string of the given method.
 */
SBW_API std::string SBWLowLevel::methodGetSignatureInString(Integer moduleInstanceId, Integer serviceId, Integer methodId)
{
	DataBlockWriter args ;

	args << serviceId ;

	DataBlockReader result =
		methodCall(moduleInstanceId, SBWSystemService, SBWGetMethodsMethod, args);
	std::vector<std::string> methods ;

	result >> methods ;

	return methods[methodId];
}

/**
 * returns a copy of a given string for the C API allocated on the C heap.
 * Result should be deallocated using SBWFree.
 * @param s string to be copied.
 * @return copy of string on C heap.
 */ 
SBW_API char *SBWLowLevel::resultStringForC(const char *s)
{
	char *result = (char *)malloc(strlen(s) + 1);

	strcpy(result, s);
	
	return result ;
}

/**
 * call SBW method.
 * @param moduleInstanceId module instance numeric identifier
 * @param serviceId service numeric identifier
 * @param method method numeric identifier
 * @param args arguments to method
 * @return data block containing the result of the SBW method call
 */
SBW_API DataBlockReader SBWLowLevel::methodCall(
	Integer moduleInstanceId, Integer serviceId, Integer method, DataBlockWriter args)
{
	return rpc->call(moduleInstanceId, serviceId, method, args);
}

/**
 * make call to SBW method, without blocking for method completion. 
 * @param moduleInstanceId module instance numeric identifier
 * @param serviceId service numeric identifier
 * @param method method numeric identifier
 * @param args arguments to method
 */
SBW_API void SBWLowLevel::methodSend(
	Integer moduleInstanceId, Integer serviceId, Integer method, DataBlockWriter args)
{
	rpc->send(moduleInstanceId, serviceId, method, args);
}

/**
 * returns the method on the broker corresponding to a given signature.
 * @param signature signature of a method on the broker.
 * @return broker method corresponding to the given signature 
 */
SBW_API ServiceMethod SBWLowLevel::getBrokerMethod(const char *signature)
{
	return
		Module(SBWBrokerModule).
			findServiceByName(SBWRPC::brokerServiceName).getMethod(signature);
}

ServiceMethod SBWLowLevel::getBrokerMethod(brokerMethods method)
{
	return ServiceMethod(SBWBrokerModule, 0, method);
}

/**
 * returns the numeric identifier of an instance of a given module.
 * This function may or may not create a new module instance depnding on the module management type of the given module.
 * @param moduleIdentificationName module string identifier
 * @return the numeric identifier of an instance of the given module
 */
SBW_API Integer SBWLowLevel::getModuleInstance(const char *moduleIdentificationName)
{
	Integer brokerService = moduleFindServiceByName(SBWBrokerModule, SBWRPC::brokerServiceName);
	Integer getModuleInstanceMethodId =
		serviceGetMethod(SBWBrokerModule, brokerService, "int getModuleInstance(string)");
	DataBlockWriter args ;


	args << moduleIdentificationName ;

	Integer moduleId ;
	DataBlockReader result =
		methodCall(SBWBrokerModule, brokerService, getModuleInstanceMethodId, args);

	result >> moduleId ;

	return moduleId ;
}

/**
 * returns an array of service descriptors for the given module
 * @param moduleIdentificationName module string identifier
 * @return the array of service descriptors of the resitered services of the given module
 */
SBW_API std::vector<ServiceDescriptor> *SBWLowLevel::getServiceDescriptors(const char *moduleIdentificationName)
{
	std::vector<DataBlockReader> listArray ;

	//getBrokerMethod("{}[] getServiceDescriptors(string)").call(
	//	DataBlockWriter() << moduleIdentificationName) >> listArray ;
	getBrokerMethod(GetServiceDescriptorsString).call(
		DataBlockWriter() << moduleIdentificationName) >> listArray ;

	std::vector<ServiceDescriptor> *result =
		new std::vector<ServiceDescriptor>(listArray.size());

	unsigned int i = 0 ;

	while (i != listArray.size())
	{
		(*result)[i] = ServiceDescriptor(listArray[i]);
		i++ ;
	}

	return result ;
}

/**
 * instructs the broker to disconnect from a given module instance.
 * Normally a module instance will terminate when the broker disconnects from the module instance.
 * @param moduleInstanceId numeric module instance identifier of the module instance to be disconnected.
 */
SBW_API void SBWLowLevel::moduleShutdown(Integer moduleInstanceId)
{
	methodSend(moduleInstanceId, SBWSystemService, SBWShutdownMethod, DataBlockWriter());
}

/**
 * returns the number of services implemented by a given module instance.
 * @param moduleInstanceId numeric module instance identifier of the module instance.
 * @param the number of services implemented by the given module instance.
 */
SBW_API Integer SBWLowLevel::moduleGetNumberOfServices(Integer moduleInstanceId)
{
	DataBlockWriter args ;
	DataBlockReader result =
		methodCall(moduleInstanceId, SBWSystemService, SBWGetServicesMethod, args);
	std::vector<std::string> services ;

	result >> services ;
	return services.size();
}

/**
 * returns the numeric service identifier of a named service on a given module instance.
 * @param moduleInstanceId numeric module instance identifier of the module instance.
 * @param serviceName service identification name.
 * @return the numeric service identifier of the named service on the given module instance.
 */
SBW_API Integer SBWLowLevel::moduleFindServiceByName(Integer moduleInstanceId, const char *serviceName)
{
	DataBlockWriter args ;
	DataBlockReader result =
		methodCall(moduleInstanceId, SBWSystemService, SBWGetServicesMethod, args);
	std::vector<std::string> services ;
	Integer serviceId = 0 ;

	result >> services ;

	while (serviceId !=  (Integer)services.size()
	       && services[serviceId].compare(serviceName))
		serviceId++ ;

	if (serviceId ==  (Integer)services.size())
		throw new SBWServiceNotFoundException("service not found");

	return serviceId ;
}

/**
 * returns the module descriptor corresponding to a given module instance.
 * @param moduleInstanceId numeric module instance identifier of the module instance.
 * @return the module descriptor corresponding to the given module instance.
 */
SBW_API ModuleDescriptor SBWLowLevel::moduleGetModuleDescriptor(Integer moduleInstanceId)
{
	DataBlockReader list;
	
	//getBrokerMethod("{} getModuleDescriptor(int)").call(DataBlockWriter() << moduleInstanceId) >> list ;
	getBrokerMethod(GetModuleDescriptorInt).call(DataBlockWriter() << moduleInstanceId) >> list ;
	
	return ModuleDescriptor(list);
}

/**
 * returns the service descriptor corresponding to a given service.
 * @param moduleInstanceId numeric module instance identifier of the module instance containing the service.
 * @param serviceId numeric service identifier of the service.
 * @return the service descriptor corresponding to the given service.
 */
SBW_API ServiceDescriptor SBWLowLevel::serviceGetDescriptorHandle(Integer moduleInstanceId, Integer serviceId)
{
	DataBlockWriter args ;
	std::vector<std::string> services ;
	
	methodCall(moduleInstanceId, SBWSystemService, SBWGetServicesMethod, args) >> services ;

	if (serviceId < 0 || serviceId >= (int) services.size())
	{
		char buffer[200];

		sprintf(
			buffer,
			"service id, %d, does not exist on the module instance %d",
			serviceId,
			moduleInstanceId);

		throw new SBWServiceNotFoundException(buffer);
	}
	
	DataBlockReader list ;

	//getBrokerMethod("{} getServiceDescriptor(int,string)").call(
	//	DataBlockWriter() << moduleInstanceId << services[serviceId]) >> list;
	getBrokerMethod(GetServiceDescriptorString).call(
		DataBlockWriter() << moduleInstanceId << services[serviceId]) >> list;

	return ServiceDescriptor(list);
}

/**
 * returns the numeric method on a given service with a given signature.
 * @param moduleInstanceId numeric module instance identifier of the module instance containing the service.
 * @param serviceId numeric service identifier of the service.
 * @param signature the signature of the method to be located.
 * @return the numeric method on the given service with the given signature.
 */
SBW_API Integer SBWLowLevel::serviceGetMethod(Integer moduleInstanceId, Integer serviceId, const char *signature)
{
	DataBlockWriter args ;
	
	args << serviceId ;

	DataBlockReader result =
		methodCall(moduleInstanceId, SBWSystemService, SBWGetMethodsMethod, args);
	std::vector<std::string> methods ;

	result >> methods ;

	return sbwSignature::match(methods, signature);
}

/**
 * returns the number of methods on a given service.
 * @param moduleInstanceId numeric module instance identifier of the module instance containing the service.
 * @param serviceId numeric service identifier of the service.
 * @return the number of methods on the given service.
 */
SBW_API Integer SBWLowLevel::serviceGetNumberOfMethods(Integer moduleInstanceId, Integer serviceId)
{
	DataBlockWriter args ;

	args << serviceId ;

	DataBlockReader result =
		methodCall(moduleInstanceId, SBWSystemService, SBWGetMethodsMethod, args);
	std::vector<std::string> methods ;

	result >> methods ;

	return methods.size();
}

/**
 * returns an array of numeric module instance identifiers corresponding to a given vector of Module objects.
 * The result should deallocated using SBWFree.
 * @param modules a vector of module objects.
 * @param numberOfModuleInstances the referenced integer is set to the number of module instances in the given vector.
 * @return an array of numeric module instance identifiers corresponding to the given vector of Module objects.
 */
Integer *SBWLowLevel::mapModuleArrayForC(std::vector<Module> *modules, Integer *numberOfModuleInstances)
{
	Integer i = *numberOfModuleInstances = modules->size();
	Integer *result = (Integer *)calloc(i, sizeof(Integer));

	while (i != 0)
	{
		i-- ;
		result[i] = (*modules)[i].getModuleInstanceId();
	}

	delete modules ;

	return result ;
}

/**
 * returns an array of sbwSignatureElement structures corresponding to a given vector of SignatureElement objects.
 * The resultshould be deallocated using SBWFreeSBWSignatureElementArray.
 * @param args a vector of SignatureElement objects.
 * @param numberOfArgs  the referenced integer is set to the number of SignatureElement objects in the given vector.
 * @return an array of sbwSignatureElement structures corresponding to the given vector of SignatureElement objects.
 */
sbwSignatureElement **SBWLowLevel::mapSignatureElements(std::vector<SignatureElement> *args, Integer *numberOfArgs)
{
	int i = *numberOfArgs = args->size();
	sbwSignatureElement **result = new sbwSignatureElement *[i];

	while (i != 0)
	{
		i-- ;
		result[i] = (*args)[i].getImpl();
		result[i]->AddReference();
	}

	delete args ;

	return result ;
}

/**
 * adds a given listener object to the C++ API to receive notification of SBW events.
 * @param x listener object
 */
SBW_API void SBWLowLevel::addListener(SBWListener *x)
{ listenerConsolidator.addListener(x); }

/**
 * removes a listener object from the C++ API.
 * @param x listener object
 */
SBW_API void SBWLowLevel::removeListener(SBWListener *x)
{ listenerConsolidator.removeListener(x); }
