/**
 * @file    XMLFileBuffer.h
 * @brief   XMLFileBuffer implements the XMLBuffer interface for files
 * @author  Ben Bornstein
 * @author  Akiya Jouraku (replaced cstdio based code with std::istream based code
 * to support compressed files)
 *
 * $Id: XMLFileBuffer.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/xml/XMLFileBuffer.h $
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
 * ---------------------------------------------------------------------- -->*/

#ifndef XMLFileBuffer_h
#define XMLFileBuffer_h

#ifdef __cplusplus

#include <string>
#include <cstdio>
#include <istream>

#include <sbml/xml/XMLBuffer.h>

LIBSBML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libsbml-internal */

class XMLFileBuffer : public XMLBuffer
{
public:

  /**
   * Creates a XMLBuffer based on the given file.  The file will be opened
   * for reading.
   *
   * @note ZlibNotLinked will be thrown if .gz or .zip file is given and 
   * zlib is not linked with libSBML at compile time. Similarly, Bzip2NotLinked
   * will be thrown if .bz2 file is given and bzip2 is not linked with libSBML 
   * at compile time.
   */
  XMLFileBuffer (const std::string& filename);


  /**
   * Destroys this XMLFileBuffer and closes the underlying file.
   */
  virtual ~XMLFileBuffer ();


  /**
   * Copies at most nbytes from this XMLFileBuffer to the memory pointed to
   * by destination.
   *
   * @return the number of bytes actually copied (may be 0).
   */
  virtual unsigned int copyTo (void* destination, unsigned int bytes);


  /**
   * @return true if there was an error reading from the underlying buffer,
   * false otherwise.
   */
  virtual bool error ();


private:

  XMLFileBuffer ();
  XMLFileBuffer (const XMLFileBuffer&);
  XMLFileBuffer& operator= (const XMLFileBuffer&);

  std::string   mFilename;
  std::istream* mStream;
};

/** @endcond */

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* XMLFileBuffer_h */
