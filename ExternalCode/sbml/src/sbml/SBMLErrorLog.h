/**
 * @file    SBMLErrorLog.h
 * @brief   Stores errors (and messages) encountered while processing SBML.
 * @author  Ben Bornstein
 * @author  Michael Hucka
 *
 * $Id: SBMLErrorLog.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/SBMLErrorLog.h $
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2009-2011 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 *
 * @class SBMLErrorLog
 * @brief Log of errors and other events encountered during SBML processing.
 *
 * @htmlinclude not-sbml-warning.html
 *
 * The error log is a list.  Each SBMLDocument maintains its own
 * SBMLErrorLog.  When a libSBML operation on SBML content results in an
 * error, or when there is something worth noting about the SBML content,
 * the issue is reported as an SBMLError object stored in the SBMLErrorLog
 * list.
 *
 * SBMLErrorLog is derived from XMLErrorLog, an object class that serves
 * exactly the same purpose but for the XML parsing layer.  XMLErrorLog
 * provides crucial methods such as
 * @if java XMLErrorLog::getNumErrors()@else getNumErrors()@endif
 * for determining how many SBMLError or XMLError objects are in the log.
 * SBMLErrorLog inherits these methods.
 *
 * The general approach to working with SBMLErrorLog in user programs
 * involves first obtaining a pointer to a log from a libSBML object such
 * as SBMLDocument.  Callers should then use
 * @if java XMLErrorLog::getNumErrors()@else getNumErrors() @endif to inquire how
 * many objects there are in the list.  (The answer may be 0.)  If there is
 * at least one SBMLError object in the SBMLErrorLog instance, callers can
 * then iterate over the list using
 * SBMLErrorLog::getError(@if java long n@endif)@if clike const@endif,
 * using methods provided by the SBMLError class to find out the error code
 * and associated information such as the error severity, the message, and
 * the line number in the input.
 *
 * If you wish to simply print the error strings for a human to read, an
 * easier and more direct way might be to use SBMLDocument::printErrors().
 *
 * @see SBMLError
 * @see XMLErrorLog
 * @see XMLError
 */

#ifndef SBMLErrorLog_h
#define SBMLErrorLog_h


#include <sbml/common/extern.h>
#include <sbml/xml/XMLError.h>
#include <sbml/xml/XMLErrorLog.h>
#include <sbml/SBMLError.h>


#ifdef __cplusplus

LIBSBML_CPP_NAMESPACE_BEGIN

class LIBSBML_EXTERN SBMLErrorLog : public XMLErrorLog
{
public:

  /**
   * Returns the <i>n</i>th SBMLError object in this log.
   *
   * Index @p n is counted from 0.  Callers should first inquire about the
   * number of items in the log by using the
   * @if java XMLErrorLog::getNumErrors()@else getNumErrors()@endif method.
   * Attempts to use an error index number that exceeds the actual number
   * of errors in the log will result in a @c NULL being returned.
   *
   * @param n the index number of the error to retrieve (with 0 being the
   * first error).
   *
   * @return the <i>n</i>th SBMLError in this log, or @c NULL if @p n is
   * greater than or equal to
   * @if java XMLErrorLog::getNumErrors()@else getNumErrors()@endif.
   *
   * @see getNumErrors()
   */
  const SBMLError* getError (unsigned int n) const;


  /**
   * Returns the number of errors that have been logged with the given
   * severity code.
   *
   * LibSBML associates severity levels with every SBMLError object to
   * provide an indication of how serious the problem is.  Severities range
   * from informational diagnostics to fatal (irrecoverable) errors.  Given
   * an SBMLError object instance, a caller can interrogate it for its
   * severity level using methods such as SBMLError::getSeverity(),
   * SBMLError::isFatal(), and so on.  The present method encapsulates
   * iteration and interrogation of all objects in an SBMLErrorLog, making
   * it easy to check for the presence of error objects with specific
   * severity levels.
   *
   * @if clike @param severity a value from
   * #SBMLErrorSeverity_t @endif@if java @param severity a
   * value from the set of <code>LIBSBML_SEV_</code> constants defined by
   * the interface class <code><a
   * href="libsbmlConstants.html">libsbmlConstants</a></code> @endif@if python @param severity a
   * value from the set of <code>LIBSBML_SEV_</code> constants defined by
   * the interface class @link libsbml libsbml@endlink. @endif
   *
   * @return a count of the number of errors with the given severity code.
   *
   * @see getNumErrors()
   */
  unsigned int getNumFailsWithSeverity(unsigned int severity);


  /** @cond doxygen-libsbml-internal */

  /**
   * Creates a new, empty SBMLErrorLog.
   */
  SBMLErrorLog ();


  /**
   * Destroys this SBMLErrorLog.
   */
  virtual ~SBMLErrorLog ();


  /**
   * Convenience function that combines creating an SBMLError object and
   * adding it to the log.
   *
   * @param errorId an unsigned int, the identification number of the error.
   * 
   * @param details a string containing additional details about the error.
   * If the error code in @p errorId is one that is recognized by SBMLError,
   * the given message is @em appended to a predefined message associated
   * with the given code.  If the error code is not recognized, the message
   * is stored as-is as the text of the error.
   * 
   * @param line an unsigned int, the line number at which the error occured.
   * 
   * @param column an unsigned int, the column number at which the error occured.
   * 
   * @param severity an integer indicating severity of the error.
   * 
   * @param category an integer indicating the category to which the error
   * belongs.
   *
   * @if notcpp @docnote @htmlinclude warn-default-args-in-docs.html @endif
   */
  void logError
  (
      const unsigned int errorId  = 0
    , const unsigned int level    = SBML_DEFAULT_LEVEL
    , const unsigned int version  = SBML_DEFAULT_VERSION
    , const std::string& details  = ""
    , const unsigned int line     = 0
    , const unsigned int column   = 0
    , const unsigned int severity = LIBSBML_SEV_ERROR
    , const unsigned int category = LIBSBML_CAT_SBML
  );


  /**
   * Adds the given SBMLError to the log.
   *
   * @param error SBMLError, the error to be logged.
   */
  void add (const SBMLError& error);


  /**
   * Adds (copies) the SBMLErrors in the given SBMLError list to this
   * SBMLErrorLog.
   *
   * @param errors list, a list of SBMLError to be added to the log.
   */
  void add (const std::list<SBMLError>& errors);


  /**
   * Removes an error having errorId from the SBMLError list.
   *  
   * Only the first item will be removed if there are multiple errors
   * with the given errorId.
   *
   * @param errorId the error identifier of the error to be removed.
   */
  void remove (const unsigned int errorId);


  /** @endcond */
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* SBMLErrorLog_h */
