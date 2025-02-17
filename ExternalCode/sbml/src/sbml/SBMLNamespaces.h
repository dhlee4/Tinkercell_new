/**
 * @file    SBMLNamespaces.h
 * @brief   SBMLNamespaces class to store level/version and namespace 
 * @author  Sarah Keating
 *
 * $Id: SBMLNamespaces.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/SBMLNamespaces.h $
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
 * @class SBMLNamespaces
 * @brief Class to store SBML level, version and namespace information.
 *
 * @htmlinclude not-sbml-warning.html
 *
 * There are differences in the definitions of components between different
 * SBML Levels, as well as Versions within Levels.  For example, the
 * "sboTerm" attribute was not introduced until Level&nbsp;2
 * Version&nbsp;2, and then only on certain component classes; the SBML
 * Level&nbsp;2 Version&nbsp;3 specification moved the "sboTerm" attribute
 * to the SBase class, thereby allowing nearly all components to have SBO
 * annotations.  As a result of differences such as those, libSBML needs to
 * track the SBML Level and Version of every object created.
 * 
 * The purpose of the SBMLNamespaces object class is to make it easier to
 * communicate SBML Level and Version data between libSBML constructors and
 * other methods.  The SBMLNamespaces object class tracks 3-tuples
 * (triples) consisting of SBML Level, Version, and the corresponding SBML
 * XML namespace.
 *
 * The plural name (SBMLNamespaces) is not a mistake, because in SBML
 * Level&nbsp;3, objects may have extensions added by Level&nbsp;3 packages
 * used by a given model and therefore may have multiple namespaces
 * associated with them; however, until the introduction of SBML
 * Level&nbsp;3, the SBMLNamespaces object only records one SBML
 * Level/Version/namespace combination at a time.  Most constructors for
 * SBML objects in libSBML take a SBMLNamespaces object as an argument,
 * thereby allowing the constructor to produce the proper combination of
 * attributes and other internal data structures for the given SBML Level
 * and Version.
 */

#ifndef SBMLNamespaces_h
#define SBMLNamespaces_h

#include <sbml/xml/XMLNamespaces.h>
#include <sbml/common/common.h>

#ifdef __cplusplus
namespace LIBSBML_CPP_NAMESPACE {
  const unsigned int SBML_DEFAULT_LEVEL   = 3;
  const unsigned int SBML_DEFAULT_VERSION = 1;
  const char* const SBML_XMLNS_L1   = "http://www.sbml.org/sbml/level1";
  const char* const SBML_XMLNS_L2V1 = "http://www.sbml.org/sbml/level2";
  const char* const SBML_XMLNS_L2V2 = "http://www.sbml.org/sbml/level2/version2";
  const char* const SBML_XMLNS_L2V3 = "http://www.sbml.org/sbml/level2/version3";
  const char* const SBML_XMLNS_L2V4 = "http://www.sbml.org/sbml/level2/version4";
  const char* const SBML_XMLNS_L3V1 = "http://www.sbml.org/sbml/level3/version1/core";
}
#else
static const unsigned int SBML_DEFAULT_LEVEL   = 3;
static const unsigned int SBML_DEFAULT_VERSION = 1;
static const char* const SBML_XMLNS_L1   = "http://www.sbml.org/sbml/level1";
static const char* const SBML_XMLNS_L2V1 = "http://www.sbml.org/sbml/level2";
static const char* const SBML_XMLNS_L2V2 = "http://www.sbml.org/sbml/level2/version2";
static const char* const SBML_XMLNS_L2V3 = "http://www.sbml.org/sbml/level2/version3";
static const char* const SBML_XMLNS_L2V4 = "http://www.sbml.org/sbml/level2/version4";
static const char* const SBML_XMLNS_L3V1 = "http://www.sbml.org/sbml/level3/version1/core";
#endif

#ifdef __cplusplus

#include <string>
#include <stdexcept>

LIBSBML_CPP_NAMESPACE_BEGIN

class LIBSBML_EXTERN SBMLNamespaces
{
public:

  /**
   * Creates a new SBMLNamespaces object corresponding to the given SBML
   * @p level and @p version.
   *
   * SBMLNamespaces objects are used in libSBML to communicate SBML Level
   * and Version data between constructors and other methods.  The
   * SBMLNamespaces object class tracks 3-tuples (triples) consisting of
   * SBML Level, Version, and the corresponding SBML XML namespace.  Most
   * constructors for SBML objects in libSBML take a SBMLNamespaces object
   * as an argument, thereby allowing the constructor to produce the proper
   * combination of attributes and other internal data structures for the
   * given SBML Level and Version.
   *
   * The plural name (SBMLNamespaces) is not a mistake, because in SBML
   * Level&nbsp;3, objects may have extensions added by Level&nbsp;3
   * packages used by a given model and therefore may have multiple
   * namespaces associated with them; however, until the introduction of
   * SBML Level&nbsp;3, the SBMLNamespaces object only records one SBML
   * Level/Version/namespace combination at a time.  Most constructors for
   * SBML objects in libSBML take a SBMLNamespaces object as an argument,
   * thereby allowing the constructor to produce the proper combination of
   * attributes and other internal data structures for the given SBML Level
   * and Version.
   *
   * @param level the SBML level
   * @param version the SBML version
   * 
   * @if notcpp @docnote @htmlinclude warn-default-args-in-docs.html @endif
   */
  SBMLNamespaces(unsigned int level = SBML_DEFAULT_LEVEL, 
                 unsigned int version = SBML_DEFAULT_VERSION);


  /**
   * (For Extension)
   *
   * Creates a new SBMLNamespaces object corresponding to the combination of 
   * (1) the given SBML @p level and @p version, and (2) the given @p package 
   * with the @p package @p version.
   *
   * @note SBMLExtensionException will be thrown if the extension module
   *       that supports the combination of the given sbml level, sbml version, 
   *       package name, and package version has not been registered.
   * 
   * @param level   the SBML level
   * @param version the SBML version
   * @param pkgName the string of package name (e.g. "layout", "multi")
   * @param pkgVersion the package version
   * @param pkgPrefix the prefix of the package namespace (e.g. "layout", "multi") to be added.
   *        The package's name will be used if the given string is empty (default).
   *
   *
   */
  SBMLNamespaces(unsigned int level, unsigned int version, const std::string &pkgName,
                 unsigned int pkgVersion, const std::string& pkgPrefix = ""); 
  

  /**
   * Destroys this SBMLNamespaces object.
   */
  virtual ~SBMLNamespaces();

  
  /**
   * Copy constructor; creates a copy of a SBMLNamespaces.
   * 
   * @param orig the SBMLNamespaces instance to copy.
   */
  SBMLNamespaces(const SBMLNamespaces& orig);


  /**
   * Assignment operator for SBMLNamespaces.
   */
  SBMLNamespaces& operator=(const SBMLNamespaces& rhs);


  /**
   * Creates and returns a deep copy of this SBMLNamespaces.
   * 
   * @return a (deep) copy of this SBMLNamespaces.
   */
  virtual SBMLNamespaces* clone () const;


  /**
   * Returns a string representing the SBML XML namespace for the 
   * given @p level and @p version of SBML.
   *
   * @param level the SBML level
   * @param version the SBML version
   *
   * @return a string representing the SBML namespace that reflects the
   * SBML Level and Version specified.
   */
  static std::string getSBMLNamespaceURI(unsigned int level,
                                         unsigned int version);
  
  /**
   * Returns a list of all supported SBMLNamespaces in this version of 
   * libsbml. 
   * 
   * @return a list with supported SBML namespaces. 
   */
  static const List* getSupportedNamespaces();

  /**
   * Returns a string representing the SBML XML namespace of this
   * object.
   *
   * @return a string representing the SBML namespace that reflects the
   * SBML Level and Version of this object.
   */
  virtual std::string getURI() const;

  
  /**
   * Get the SBML Level of this SBMLNamespaces object.
   *
   * @return the SBML Level of this SBMLNamespaces object.
   */
  unsigned int getLevel();


  /**
   * Get the SBML Level of this SBMLNamespaces object.
   *
   * @return the SBML Level of this SBMLNamespaces object.
   */
  unsigned int getLevel() const;


  /**
   * Get the SBML Version of this SBMLNamespaces object.
   *
   * @return the SBML Version of this SBMLNamespaces object.
   */
  unsigned int getVersion();


  /**
   * Get the SBML Version of this SBMLNamespaces object.
   *
   * @return the SBML Version of this SBMLNamespaces object.
   */
  unsigned int getVersion() const;


  /**
   * Get the XML namespaces list for this SBMLNamespaces object.
   * 
   * The plural is not a mistake, because in SBML Level&nbsp;3, objects may
   * have extensions added by Level&nbsp;3 packages used by a given model,
   * and therefore there may be multiple XML namespaces involved too.
   * However, until the introduction of SBML Level&nbsp;3, the
   * SBMLNamespaces object only records one SBML Level/Version/namespace
   * combination at a time, and so this method will also only return
   * a list of one item.
   *
   * @return the XML namespaces of this SBMLNamespaces object.
   */
  XMLNamespaces * getNamespaces();


  /**
   * Get the XML namespaces list for this SBMLNamespaces object.
   * 
   * The plural is not a mistake, because in SBML Level&nbsp;3, objects may
   * have extensions added by Level&nbsp;3 packages used by a given model,
   * and therefore there may be multiple XML namespaces involved too.
   * However, until the introduction of SBML Level&nbsp;3, the
   * SBMLNamespaces object only records one SBML Level/Version/namespace
   * combination at a time, and so this method will also only return
   * a list of one item.
   *
   * @return the XML namespaces of this SBMLNamespaces object.
   */
  const XMLNamespaces * getNamespaces() const;


  /**
   * Add the given XML namespaces list to the set of namespaces within this
   * SBMLNamespaces object.
   *
   * The following code gives an example of how one could add the XHTML
   * namespace to the list of namespaces recorded by the top-level
   * <code>&lt;sbml&gt;</code> element of a model.  It gives the new
   * namespace a prefix of <code>html</code>.  @if clike
   * @verbatim
SBMLDocument *sd;
try 
{
    sd = new SBMLDocument(3, 1);
} 
catch (SBMLConstructorException e)
{
    // Here, have code to handle a truly exceptional situation. Candidate
    // causes include invalid combinations of SBML Level and Version
    // (impossible if hardwired as given here), running out of memory, and
    // unknown system exceptions.
}

SBMLNamespaces sn = sd->getNamespaces();
if (sn != NULL)
{
    sn->add("http://www.w3.org/1999/xhtml", "html");
}
else
{
    // Handle another truly exceptional situation.
}
@endverbatim
   * @endif@if java
@verbatim
SBMLDocument sd;
try 
{
    sd = new SBMLDocument(3, 1);
} 
catch (SBMLConstructorException e)
{
    // Here, have code to handle a truly exceptional situation. Candidate
    // causes include invalid combinations of SBML Level and Version
    // (impossible if hardwired as given here), running out of memory, and
    // unknown system exceptions.
}

SBMLNamespaces sn = sd.getNamespaces();
if (sn != null)
{
    sn.add("http://www.w3.org/1999/xhtml", "html");
}
else
{
    // Handle another truly exceptional situation.
 }
@endverbatim
   * @endif@if python
@verbatim
sbmlDoc = SBMLDocument(3, 1)
if sbmlDoc == None:
  # Do something to handle exceptional situation.  Candidate
  # causes include invalid combinations of SBML Level and Version
  # (impossible if hardwired as given here), running out of memory, and
  # unknown system exceptions.

namespaces = sbmlDoc.getNamespaces()
if namespaces == None:
  # Do something to handle exceptional situation.

status = namespaces.add("http://www.w3.org/1999/xhtml", "html")
if status != LIBSBML_OPERATION_SUCCESS:
  # Do something to handle exceptional situation.
@endverbatim
   * @endif@if csharp
@verbatim
SBMLDocument sd = null;
try
{
    sd = new SBMLDocument(3, 1);
}
catch (SBMLConstructorException e)
{
    // Here, have code to handle a truly exceptional situation.
    // Candidate causes include invalid combinations of SBML
    // Level and Version (impossible if hardwired as given here),
    // running out of memory, and unknown system exceptions.
}

XMLNamespaces sn = sd.getNamespaces();
if (sn != null)
{
    sn.add("http://www.w3.org/1999/xhtml", "html");            
}
else
{
    // Handle another truly exceptional situation.
}
@endverbatim
   * @endif
   *
   * @param xmlns the XML namespaces to be added.
   */
  void addNamespaces(const XMLNamespaces * xmlns);


  /**
   * Add an XML namespace (a pair of URI and prefix) to the set of namespaces
   * within this SBMLNamespaces object.
   * 
   * @param uri    the XML namespace to be added.
   * @param prefix the prefix of the namespace to be added.
   */
  void addNamespace(const std::string& uri, const std::string &prefix);


  /**
   * Removes an XML namespace from the set of namespaces within this 
   * SBMLNamespaces object.
   * 
   * @param uri    the XML namespace to be added.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBSBML_INDEX_EXCEEDS_SIZE LIBSBML_INDEX_EXCEEDS_SIZE @endlink
   */
  int removeNamespace(const std::string& uri);


  /**
   * Add an XML namespace (a pair of URI and prefix) of a package extension
   * to the set of namespaces within this SBMLNamespaces object.
   * The SBML Level and SBML Version of this object is used.
   *
   * @note An XML namespace of a non-registered package extension can't be
   * added by this function (@link
   * OperationReturnValues_t#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE@endlink 
   * will be returned).
   * 
   * @param pkgName the string of package name (e.g. "layout", "multi")
   * @param pkgVersion the package version
   * @param prefix the prefix of the package namespace to be added.
   *        The package's name will be used if the given string is empty (default).
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE @endlink
   *
   * @see addNamespace(@if java String uri, String prefix@endif)
   */
  int addPkgNamespace(const std::string &pkgName, unsigned int pkgVersion, 
                      const std::string &prefix = "");


  /**
   * Add the XML namespaces of package extensions in the given 
   * XMLNamespace object to the set of namespaces within this 
   * SBMLNamespaces object (Non-package XML namespaces are not added
   * by this function).
   *
   * @note XML namespaces of a non-registered package extensions are not
   * added (just ignored) by this function. @link OperationReturnValues_t#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE@endlink
   * will be returned if the given xmlns is null.
   * 
   * @param xmlns the XML namespaces to be added.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE @endlink
   */
  int addPkgNamespaces(const XMLNamespaces* xmlns);


  /**
   * Removes an XML namespace of a package extension from the set of namespaces 
   * within this SBMLNamespaces object.
   *
   * @param level   the SBML level
   * @param version the SBML version
   * @param pkgName the string of package name (e.g. "layout", "multi")
   * @param pkgVersion the package version
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE @endlink
   * @li @link OperationReturnValues_t#LIBSBML_INDEX_EXCEEDS_SIZE LIBSBML_INDEX_EXCEEDS_SIZE @endlink
   */
  int removePkgNamespace(unsigned int level, unsigned version, const std::string &pkgName,
                         unsigned int pkgVersion);


  /**
   * Predicate returning @c true if the given
   * URL is one of SBML XML namespaces.
   *
   * @param uri the URI of namespace
   *
   * @return @c true if the "uri" is one of SBML namespaces, @c false otherwise.
   */
  static bool isSBMLNamespace(const std::string& uri);


  /** @cond doxygen-libsbml-internal */
  void setLevel(unsigned int level);


  void setVersion(unsigned int version);


  void setNamespaces(XMLNamespaces * xmlns);
  /** @endcond */

  /**
   * Returns the name of the main package for this namespace.
   *
   * @return the name of the main package for this namespace.
   * "core" will be returned if this namespace is defined in the SBML 
   * core. 
   */
   virtual const std::string& getPackageName () const;	
	
protected:  
  /** @cond doxygen-libsbml-internal */

  void initSBMLNamespace();

  unsigned int    mLevel;
  unsigned int    mVersion;
  XMLNamespaces * mNamespaces;

  /** @endcond */
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */


#ifndef SWIG

LIBSBML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/* ----------------------------------------------------------------------------
 * See the .cpp file for the documentation of the following functions.
 * --------------------------------------------------------------------------*/

LIBSBML_EXTERN
SBMLNamespaces_t *
SBMLNamespaces_create(unsigned int level, unsigned int version);


LIBSBML_EXTERN
unsigned int
SBMLNamespaces_getLevel(SBMLNamespaces_t *sbmlns);


LIBSBML_EXTERN
unsigned int
SBMLNamespaces_getVersion(SBMLNamespaces_t *sbmlns);


LIBSBML_EXTERN
XMLNamespaces_t *
SBMLNamespaces_getNamespaces(SBMLNamespaces_t *sbmlns);


LIBSBML_EXTERN
char *
SBMLNamespaces_getSBMLNamespaceURI(unsigned int level, unsigned int version);


LIBSBML_EXTERN
void
SBMLNamespaces_addNamespaces(SBMLNamespaces_t *sbmlns,
                             const XMLNamespaces_t * xmlns);


LIBSBML_EXTERN
SBMLNamespaces_t **
SBMLNamespaces_getSupportedNamespaces(int *length);

END_C_DECLS
LIBSBML_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* SBMLNamespaces_h */
