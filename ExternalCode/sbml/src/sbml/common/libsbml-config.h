/**
 * @file    libsbml-config.h
 * @brief   Decides whether to \#include Unix or Windows configuration variables.
 * @author  Ben Bornstein
 *
 * $Id: libsbml-config.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/common/libsbml-config.h $
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
 * in the file named "LICENSE.txt" included with this software distribution and
 * also available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 *
 * Some explanations about this file are warranted.  This file includes
 * one of the following (depending on operating system and compiler):
 * 
 * - <tt>libsbml-config-unix.h</tt>
 * - <tt>libsbml-config-win.h</tt>
 * 
 * On Linux, MacOS X, Cygwin, etc., <tt>libsbml-config-unix.h</tt> and
 * <tt>libsbml-package.h</tt> are generated from
 * <tt>libsbml-config-unix.h.in</tt> and <tt>libsbml-package.h.in</tt>,
 * respectively, by the @c configure script at the top level of the libSBML
 * distribution.
 * 
 * On Windows, we cannot rely on <tt>libsbml-config-win.h</tt> being
 * generated by @c configure, since most developers will not be able to run
 * @c configure in that environment.  Instead, both
 * <tt>libsbml-config-win.h</tt> and <tt>libsbml-package.h</tt> (which see)
 * are stored in the source repository and must be updated by the libSBML
 * developers as necessary.  The file <tt>libsbml-config-win.h</tt> should
 * rarely, if ever, need to be updated, while <tt>libsbml-package.h</tt>
 * should require minor updates prior to each libsbml release.  This is
 * admittedly not an ideal and fool-proof arrangement; however, at this
 * time it is the best we have been able to find under the circumstances.
 * 
 * Finally, <tt>libsbml-config.h</tt>, <tt>libsbml-package.h</tt>,
 * <tt>libsbml-config-unix.h</tt>, and (for consistency)
 * <tt>libsbml-config-win.h</tt> are all installed by @c "make install".
 */

#ifndef LIBSBML_CONFIG_H
#define LIBSBML_CONFIG_H 1

#include <sbml/common/libsbml-namespace.h>

#include <sbml/common/libsbml-config-common.h>

#include <sbml/common/libsbml-version.h>


#endif  /* LIBSBML_CONFIG_H */
