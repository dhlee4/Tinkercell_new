/**
 * @file    XercesHandler.h
 * @brief   Redirect Xerces-C++ SAX2 events to an XMLHandler
 * @author  Ben Bornstein
 *
 * $Id: XercesHandler.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/xml/XercesHandler.h $
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

#ifndef XercesHandler_h
#define XercesHandler_h

#ifdef __cplusplus

#include <string>

#include <sbml/xml/XercesTranscode.h>
#include <xercesc/sax2/DefaultHandler.hpp>

LIBSBML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libsbml-internal */

class XMLHandler;


class XercesHandler : public xercesc::DefaultHandler
{
public:

  /**
   * Creates a new XercesHandler.  Xerces-C++ SAX2 events will be
   * redirected to the given XMLHandler.
   */
  XercesHandler (XMLHandler& handler);


  /**
   * Destroys this XercesHandler.
   */
  virtual ~XercesHandler ();


  /**
   * Receive notification of the beginning of the document.
   */
  void startDocument ();


  /**
   * Receive notification of the start of an element.
   *
   * @param  uri        The URI of the associated namespace for this element
   * @param  localname  The local part of the element name
   * @param  qname      The qualified name of this element
   * @param  attrs      The specified or defaulted attributes
   */
  virtual void startElement
  (
     const XMLCh* const  uri
   , const XMLCh* const  localname
   , const XMLCh* const  qname
   , const xercesc::Attributes& attrs
  );


  /**
   * Receive notification of the end of the document.
   */
  void endDocument ();


  /**
   * Receive notification of the end of an element.
   *
   * @param  uri        The URI of the associated namespace for this element
   * @param  localname  The local part of the element name
   * @param  qname      The qualified name of this element
   */
  void endElement
  (
     const XMLCh* const  uri
   , const XMLCh* const  localname
   , const XMLCh* const  qname
  );


  /**
   * Receive notification of character data inside an element.
   *
   * @param  chars   The characters
   * @param  length  The number of characters to use from the character array
   */
  void characters (const XMLCh* const chars, const XercesSize_t length);


  /**
   * @return the column number of the current XML event.
   */
  unsigned int getColumn () const;


  /**
   * @return the line number of the current XML event.
   */
  unsigned int getLine () const;


  /**
   * Receive a Locator object for document events.
   */
  void setDocumentLocator (const xercesc::Locator* const locator);


protected:

  XMLHandler&              mHandler;
  const xercesc::Locator*  mLocator;
};

/** @endcond */

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* XercesHandler_h */
