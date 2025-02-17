/**
* @file portableOS.cpp
* @brief OS independant class and function library
* @author SBW Development Group <sysbio-team@caltech.edu>
*
* Organization: Caltech ERATO Kitano Systems Biology Project
*
* Created: @date 18th June 2001
* $Id: portableOS.cpp,v 1.6 2008/07/25 00:01:38 fbergmann Exp $
* $Source: /cvsroot/sbw/core/SBWCore/portableOS.cpp,v $
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

static const char rcsid[] = "$Id: portableOS.cpp,v 1.6 2008/07/25 00:01:38 fbergmann Exp $";

#include "stdafx.h"
#include "config.h"
#include "SBWRawException.h"
#include <list>
#include "SBWApplicationException.h"

#ifndef WIN32
#include <stdio.h>

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAVE_SYS_ERRNO_H
#include <sys/errno.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#endif

using namespace SystemsBiologyWorkbench ;

// -----------------------------------------------------------------------------
// Class SBWOS
// -----------------------------------------------------------------------------

/**
* Throws an exception for a system error.  It extracts the system error
* message corresponding to the last error raised by the system.
* <p>
* @throws SBWRawException, containing the system error information
**/
void SBWOS::ThrowError()
{
#if defined(WIN32)

	char *lpMsgBuf ;

	DWORD error = ::GetLastError();

	if (!::FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM ,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL ))
		throw new SBWRawException("Unknown OS error");

	SBWRawException *exception = new SBWRawException((LPCTSTR) lpMsgBuf);

	// Free the buffer.
	LocalFree( lpMsgBuf );

#elif defined(HAVE_SYS_ERRNO_H)

	// FIXME need to localize the error message.
	SBWRawException *exception = new SBWRawException(strerror(errno));

#endif

	throw exception;
}

/**
* Throws an SBWRawException * corresponding to the given error code.
* @throws SBWRawException * corresponding to the given error code.
* On Linux this method is for situations where a system call does not set errno,
* but instead returns a number that represents a system error code.
*/
void SBWOS::ThrowError(int error)
{
#if defined(WIN32)

	char *lpMsgBuf ;

	if (!::FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM ,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL ))
		throw new SBWRawException("Unknown OS error");

	SBWRawException *exception = new SBWRawException((LPCTSTR) lpMsgBuf);

	// Free the buffer.
	LocalFree( lpMsgBuf );

#elif defined(HAVE_SYS_ERRNO_H)

	// FIXME need to localize the error message.
	SBWRawException *exception = new SBWRawException(strerror(error));

#endif

	throw exception;
}


/** 
* launch new process with a given command line
* @param commandLine command line to executed in a new process
*/
void SBWOS::startProcess(char *commandLine, bool bWait /*= false*/)
{
	if (commandLine == NULL)
		return;

#if defined(WIN32)

	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.cb = sizeof(si);     // Set byte count

	PROCESS_INFORMATION pi;

	if(!CreateProcess(NULL, (LPTSTR) (LPCTSTR) commandLine,
		NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
		ThrowError();

	if (bWait)
		WaitForSingleObject( pi.hProcess, INFINITE );

#else



	int pid = fork();

	if (pid == -1)			// Fork failed.
		ThrowError();

	if (pid == 0)			// This is the child process.
	{
		char *argv[4];
		const char *command = "sh";
		const char *arg = "-c";
		argv[0] = const_cast<char*>(command);
		argv[1] = const_cast<char*>(arg);
		argv[2] = commandLine;
		argv[3] = NULL;

		if (execvp("/bin/sh", argv) > -1) // Only returns on failure.
			ThrowError();
	}

	// If pid != -1 or 0, then we're the parent thread.
	// Simply exit and hope the child process started.
	if (bWait){}

#endif
}

#ifdef WIN32
/**
* WIN32 only - computes the <code>argc</code> and <code>argv</code> for this windows application
* @param argc set to the number of arguments on the command line plus one
* @param argv set to the arguments on the command line including the invoking excutable
*/
SBW_API void SBWOS::windowsExtractCommandLine(int *argc, char ***argv)
{
	static char *cmdLine = NULL;
	static std::list<char *> args ;

	if (cmdLine == NULL)
	{
		char *token;
#if  _MSC_VER >= 1400
		cmdLine = _strdup(GetCommandLine());
#else
		cmdLine = strdup(GetCommandLine());
#endif

		//MessageBox(NULL, cmdLine, "Trig - cmdline", MB_OK | MB_ICONEXCLAMATION);
		if (cmdLine[0] == '"')
		{
			cmdLine++;

			int index = strcspn(cmdLine, "\"");

			cmdLine[index] = '\0' ;
			args.push_back(cmdLine);
			token = strtok(&(cmdLine[index + 1]), " \t\n");
		}
		else
			token = strtok(cmdLine, " \t\n");

		while (token != NULL)
		{
			args.push_back(token);
			token = strtok(NULL, " \t\n");
		}
	}

	*argc = args.size();
	*argv = new char *[*argc];

	int i = 0 ;
	std::list<char *>::iterator arg = args.begin();

	while (i != *argc)
	{
		(*argv)[i] = *arg ;
		i++ ;
		arg++ ;
	}
}
#endif // WIN32

// -----------------------------------------------------------------------------
// Class SBWOSMutex
// -----------------------------------------------------------------------------

/**
* constructs a mutex with a given name.
* @param n name of the mutex
*/

SBW_API SBWOSMutex::SBWOSMutex(std::string n) : name(n)
{
#if defined(WIN32)

	InitializeCriticalSection(&criticalSection);

#elif defined(HAVE_LIBPTHREAD)

	pthread_mutexattr_t attr;
	int status;

	// The default kind of mutex in Linux pthreads is "fast" mutexes,
	// not the "recursive" kind that is the default under Windows.
	// Here we set up the Linux pthread mutexes to be "recursive".

	if ((status = pthread_mutexattr_init(&attr)) != 0)
		SBWOS::ThrowError(status);
#ifdef PTHREAD_MUTEX_RECURSIVE_NP
	if ((status
		= pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP)) != 0)
		SBWOS::ThrowError(status);
#else
	if ((status
		= pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0)
		SBWOS::ThrowError(status);

#endif
	if ((status = pthread_mutex_init(&mutex, &attr)) != 0)
		SBWOS::ThrowError(status);

	if ((status = pthread_mutexattr_destroy(&attr)) != 0)
		SBWOS::ThrowError(status);

#endif
}
// FIXME make inline
// FIXME bring common code together with version above
/**
* constructs a mutex with a given 2 part name.
* @param n first part of name of the mutex
* @param suffix second part of name of the mutex
*/
SBW_API SBWOSMutex::SBWOSMutex(std::string n, std::string suffix) : name(n)
{
	name += suffix ;

#if defined(WIN32)

	InitializeCriticalSection(&criticalSection);

#elif defined(HAVE_LIBPTHREAD)

	pthread_mutexattr_t attr;
	int status;

	// The default kind of mutex in Linux pthreads is "fast" mutexes,
	// not the "recursive" kind that is the default under Windows.
	// Here we set up the Linux pthread mutexes to be "recursive".

	if ((status = pthread_mutexattr_init(&attr)) != 0)
		SBWOS::ThrowError(status);
#ifdef PTHREAD_MUTEX_RECURSIVE_NP
	if ((status
		= pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP)) != 0)
		SBWOS::ThrowError(status);
#else
	if ((status
		= pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0)
		SBWOS::ThrowError(status);

#endif
	if ((status = pthread_mutex_init(&mutex, &attr)) != 0)
		SBWOS::ThrowError(status);

	if ((status = pthread_mutexattr_destroy(&attr)) != 0)
		SBWOS::ThrowError(status);

#endif
}
/**
* recovers all system resources used to support the muxtex.
*/
SBWOSMutex::~SBWOSMutex()
{
#if defined(WIN32)

	DeleteCriticalSection(&criticalSection);

#elif defined(HAVE_LIBPTHREAD)

	int status;

	if ((status = pthread_mutex_destroy(&mutex)) != 0)
		SBWOS::ThrowError(status);

#endif
}

/**
* acquire mutex for this thread.
* If another thread owns the mutex then this thread will block until the thread owning the mutex releases the mutex.
* Theis method doesn't block if this thread already owns the mutex.
*/
void SBWOSMutex::lock()
{
#if defined(WIN32)

	EnterCriticalSection(&criticalSection);

#elif defined(HAVE_LIBPTHREAD)

	int status;

	if ((status = pthread_mutex_lock(&mutex)) != 0)
		SBWOS::ThrowError(status);

#endif
}

/**
* release mutex for this thread
*/
void SBWOSMutex::unLock()
{
#if defined(WIN32)

	LeaveCriticalSection(&criticalSection);

#elif defined(HAVE_LIBPTHREAD)

	int status;

	if ((status = pthread_mutex_unlock(&mutex)) != 0)
		SBWOS::ThrowError(status);

#endif
}

// -----------------------------------------------------------------------------
// Class SBWThread
// -----------------------------------------------------------------------------

/**
* construct a thread with a given name
* @param n name of thread
*/
SBWThread::SBWThread(std::string n) : name(n), joined(false)
{
#if defined(WIN32)
	thread = NULL;
#elif defined(HAVE_LIBPTHREAD)
	threadId = 0;
#endif
}

/**
* recover all system resources used by this thread object
* @throws SBWRawException if join() has not been called on this thread object from different execution thread
*/
SBWThread::~SBWThread()
{
	if (!joined)
	{
#if defined(WIN32)
		if (thread != NULL)
#elif defined(HAVE_LIBPTHREAD)
		if (threadId > 0)
#endif
		{
			throw new
				SBWRawException("Attempting to delete running thread before join to thread has completed");
		}
	}

#if defined(WIN32)
	if (thread != NULL && !CloseHandle(thread))
		SBWOS::ThrowError();
#endif
}

/**
* executes run method within this static method
* @param lpParameter pointer SBWThread object
* @return 0
*/
#if defined(WIN32)
DWORD WINAPI SBWThread::threadProc(LPVOID lpParameter)
{
	((SBWThread *)lpParameter)->run();

	return 0 ;
}
#else
void* SBWThread::threadProc(void* lpParameter)
{
	((SBWThread *)lpParameter)->run();
	return NULL;
}
#endif

/**
* creates a new thread.
* The thread executes the run() method.
*/
void SBWThread::start()
{
	threadId =0;
#if defined(WIN32)

	thread = CreateThread(
		NULL,  // pointer to security attributes
		0,                         // initial thread stack size
		threadProc,     // pointer to thread function
		this,                        // argument for new thread
		0,                     // creation flags
		&threadId                         // pointer to receive thread ID
		);

	if (thread == NULL)
		SBWOS::ThrowError();

#elif defined(HAVE_LIBPTHREAD)

	TRACE("Creating new thread");

	int status = pthread_create(&threadId, NULL, threadProc, (void *)this);

	if (status != 0)
		SBWOS::ThrowError(status);

	TRACE("New thread's id = " << threadId);

#endif
}
/**
* block until 'this' thread terminates
* returns immediately if the execution thread is 'this' thread
* or if 'this' thread is not running
* otherwise blocks until 'this' thread terminates
*/
void SBWThread::join()
{
#if defined(WIN32)

	if (thread == NULL || isThisThread())
		return;

	if (WaitForSingleObject(thread, INFINITE) == WAIT_FAILED)
		SBWOS::ThrowError();

#elif defined(HAVE_LIBPTHREAD)

	if (threadId == 0 || isThisThread())
		return;

	TRACE("Waiting to join thread id = " << threadId);

	int status = pthread_join(threadId, NULL);

	if (status != 0)
		SBWOS::ThrowError(status);

#endif
	joined = true ;
}
/**
* returns whether the execution thread is the same thread represented by this SBWThread object.
* @return whether the execution thread is the same thread represented by this SBWThread object.
*/
bool SBWThread::isThisThread()
{
#if defined(WIN32)
	return threadId == GetCurrentThreadId();
#elif defined(HAVE_LIBPTHREAD)
	return threadId == pthread_self();
#endif
}
/** 
* returns a unique numeric identifier for the current execution thread
* @return a unique numeric identifier for the current execution thread
*/
unsigned long SBWThread::myThreadId()
{
#ifdef WIN32
	return GetCurrentThreadId();
#else
	return (unsigned long) pthread_self();
#endif
}

/**
* block for a given time period
* @param milliSec number of milliseconds to block for
*/
void SBWThread::sleep(Integer milliSec)
{
#if defined(WIN32)
		Sleep(milliSec);
#elif defined(HAVE_LIBPTHREAD)
		// There doesn't seem to be a thread-specific sleep in pthreads, so
		// I'm hijacking the conditional wait to achive this.  The code below
		// waits & times out on a conditional variable that is never signaled.
	try
	{

		//TRACE("Sleeping for " << milliSec << " milliseconds");
		int status;
		//#if defined(DARWIN) || defined(SOLARIS)
		//	struct timeval now;
		//	struct timespec timeout;
		//  
		//  	pthread_mutex_t timeMutex = PTHREAD_MUTEX_INITIALIZER;
		//	pthread_cond_t timeCond = PTHREAD_COND_INITIALIZER;
		//
		//	status = pthread_mutex_lock(&timeMutex);
		//	if (status != 0)
		//		SBWOS::ThrowError(status);
		//
		//	// The timeout param is an absolute time, so we have to calculate it.
		//
		//	gettimeofday(&now, NULL);
		//	timeout.tv_sec = now.tv_sec;
		//	timeout.tv_nsec = 1000 * (now.tv_usec + 1000 * milliSec);
		//
		//	status = pthread_cond_timedwait(&timeCond, &timeMutex, &timeout);
		//	if (status != ETIMEDOUT)
		//		SBWOS::ThrowError(status);
		//
		//	status = pthread_mutex_unlock(&timeMutex);
		//#else
		//struct timespec delay = { 0,0 };
		//	delay.tv_nsec = 1000 * milliSec;
		//	status = nanosleep(&delay,NULL);

		struct timespec req={0,0};  
		time_t sec=(int)(milliSec/1000);  
		milliSec=milliSec-(sec*1000);  
		req.tv_sec=sec;  
		req.tv_nsec=milliSec*1000000L;  
		while((status = nanosleep(&req,&req))==-1)  
			continue;  	

		//#endif

		if (status != 0)
			SBWOS::ThrowError(status);
	}
	catch(SBWException *e)
	{
		throw e;
	}
	catch(...)
	{
		TRACE("SLEEP failed");
	}
#endif
}

// -----------------------------------------------------------------------------
// Class SBWOSEvent
// -----------------------------------------------------------------------------

// The following used for notifying threads of events, much like the wait()
// and notify() provided in Java's thread functionality.

/**
* create an event object with a given name in the unsignalled state
* @param n name of event object
*/
SBW_API SBWOSEvent::SBWOSEvent(std::string n)
: name(n)
{
#if defined(WIN32)

	event = CreateEvent(
		NULL, // pointer to security attributes
		FALSE,  // flag for manual-reset event
		FALSE, // flag for initial state - in this case non signaled
		NULL) ;     // pointer to event-object name

	if (event == NULL)
		SBWOS::ThrowError();

#elif defined(HAVE_LIBPTHREAD)

	if (pthread_mutex_init(&mutex, NULL) != 0)
		SBWOS::ThrowError();

	if (pthread_cond_init(&event, NULL) != 0)
		SBWOS::ThrowError();

	wakeup = false;

	TRACE("Created new event object");

#endif
}
/**
* release OS resources used by this event object
*/
SBWOSEvent::~SBWOSEvent()
{
	TRACE("Destroying event object: " << name);
#if defined(WIN32)

	if (event != NULL && !CloseHandle(event))
		SBWOS::ThrowError();

#elif defined(HAVE_LIBPTHREAD)

	TRACE("Destroying event object");

	if (pthread_mutex_destroy(&mutex) != 0)
		SBWOS::ThrowError();

	if (pthread_cond_destroy(&event) != 0)
		SBWOS::ThrowError();

#endif
}

/**
* block until this event becomes signalled
*/
void SBWOSEvent::wait()
{
	TRACE("Waiting on event: " << name);
#if defined(WIN32)
	if (WaitForSingleObject(event, INFINITE) == WAIT_FAILED)
		SBWOS::ThrowError();

#elif defined(HAVE_LIBPTHREAD)

	TRACE("Waiting on event");

	if (pthread_mutex_lock(&mutex) != 0)
		SBWOS::ThrowError();

	while (!wakeup)
		pthread_cond_wait(&event, &mutex);

	wakeup = false;

	if (pthread_mutex_unlock(&mutex) != 0)
		SBWOS::ThrowError();

#endif
}

/**
* signal the event.
* the event state becomes signalled and all wait() method calls on this object unblock. 
*/
void SBWOSEvent::notify()
{
	TRACE("Notifying other threads about event: " << name);
#if defined(WIN32)

	if (!SetEvent(event))
		SBWOS::ThrowError();

#elif defined(HAVE_LIBPTHREAD)

	TRACE("Notifying other threads about event");

	if (pthread_mutex_lock(&mutex) != 0)
		SBWOS::ThrowError();

	wakeup = true;

	if (pthread_cond_broadcast(&event) != 0)
		SBWOS::ThrowError();

	if (pthread_mutex_unlock(&mutex) != 0)
		SBWOS::ThrowError();
#endif
}

/**
* returns the name of this event object
* @return the name of this event object
*/
SBW_API std::string SBWOSEvent::getName()
{
	return name;
}

// -----------------------------------------------------------------------------
// Misc. utils
// -----------------------------------------------------------------------------

/**
* WIN32 only - displays a message box containing the string "Assert"
*/
#ifdef WIN32
SBW_API void SystemsBiologyWorkbench::SBWAssertMessage()
{
	MessageBox(NULL, "ASSERT", "Assert", MB_OK);
}
#endif

// SBWDebug ---------------------------------------------------------------------

/// whether debug trace should be output
bool SBWDebug::traceOn = false;

/// mutex to ensure that debug trace output from different threads doesn't overlap
SBWOSMutex SBWDebug::traceMutex("trace");

// inline in release configuration
#ifdef _DEBUG
/**
* output debug trace information to standard error stream.
* Use SBWDebug::setTraceMode to enable output from this function.
* Has no effect in the Release configuration library.
* Use the debug configuration library to get debug trace output.
* @param x message string to be output
* @param file the source code file in which this call is being made 
* @param line the line in <code>file</code> on which this call is being made
*/
SBW_API void SBWDebug::trace(const char *x, const char *file, int line)
{
	if (traceOn)
	{
#ifdef WIN32
		SBWOSMutexLock ml(traceMutex);
#endif

		std::cerr << "(trace) thread #" << SBWThread::myThreadId() 
			<< " (" << file << ":" << line << ") " 
			<< " " << x << "\n"; std::cerr.flush();
	}
}
#endif

/**
* turns on or off debug trace output depending on parameter.
* Has no effect in the Release configuration library.
* Use the debug configuration library to get debug trace output.
* @param traceOn whether debug trace should be output
*/
void SBWDebug::setTraceMode(bool mode)
{
	traceOn = mode;
}
