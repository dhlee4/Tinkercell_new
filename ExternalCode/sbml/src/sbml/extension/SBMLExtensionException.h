/**
 * @file    SBMLExtensionException.h
 * @brief   SBMLExtensionExceptions class, the exception class for package extension
 * @author  Akiya Jouraku
 *
 * $Id: SBMLExtensionException.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/extension/SBMLExtensionException.h $
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
 */

#ifndef SBMLExtensionException_h
#define SBMLExtensionException_h

#include <sbml/common/common.h>

#ifdef __cplusplus

#include <string>
#include <stdexcept>

LIBSBML_CPP_NAMESPACE_BEGIN

/**
 * An exception class for SBMLExtensionException.
 */
class LIBSBML_EXTERN SBMLExtensionException : public std::invalid_argument
{
public:

  /** 
   * constructor 
   */
  SBMLExtensionException (const std::string& errmsg) throw();

#ifndef SWIG
  virtual ~SBMLExtensionException () throw();
#endif
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* SBMLExtensionException_h */
