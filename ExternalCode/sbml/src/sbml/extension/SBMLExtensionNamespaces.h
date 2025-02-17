/**
 * @file    SBMLExtensionNamespaces.h
 * @brief   SBMLExtensionNamespaces class to store level/version and namespace of
 *          SBML extension package
 * @author  Akiya Jouraku
 *
 * $Id: SBMLExtensionNamespaces.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/extension/SBMLExtensionNamespaces.h $
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
 * @class SBMLExtensionNamespaces
 * @brief Class to store level, version and namespace information of SBML extension
 *        package.
 *
 */

#ifndef SBMLExtensionNamespaces_h
#define SBMLExtensionNamespaces_h

#include <sbml/SBMLNamespaces.h>
#include <sbml/common/common.h>
#include <sbml/extension/SBMLExtensionRegistry.h>
#include <sbml/extension/SBMLExtensionException.h>
#include <sbml/extension/ISBMLExtensionNamespaces.h>

#ifdef __cplusplus

#include <string>
#include <stdexcept>

LIBSBML_CPP_NAMESPACE_BEGIN

template<class SBMLExtensionType>
class LIBSBML_EXTERN SBMLExtensionNamespaces : public ISBMLExtensionNamespaces
{
public:

  /**
   * Creates a new SBMLExtensionNamespaces object corresponding to the given SBML
   * @p level, @p version and @p package version.
   *
   * @note SBMLExtensionException will be thrown if the extension module
   *       that supports the combination of the given sbml level, sbml version, 
   *       package name, and package version has not been registered.
   * 
   * @param level   the SBML level
   * @param version the SBML version
   * @param pkgVersion the package version
   * @param prefix  the prefix of the package namespace (e.g. "layout", "multi") 
   *        to be added. The package's name will be used if the given string is empty 
   *        (default).
   */
  SBMLExtensionNamespaces(unsigned int level        = SBMLExtensionType::getDefaultLevel(), 
                          unsigned int version      = SBMLExtensionType::getDefaultVersion(), 
                          unsigned int pkgVersion   = SBMLExtensionType::getDefaultPackageVersion(), 
                          const std::string& prefix = SBMLExtensionType::getPackageName()) 
#ifndef SWIG
    : ISBMLExtensionNamespaces(level, version, SBMLExtensionType::getPackageName(), pkgVersion, prefix)
     ,mPackageVersion(pkgVersion), mPackageName(prefix)
   {}
#else
   ;
#endif //SWIG


  /**
   * Destroys this SBMLExtensionNamespaces object.
   */
  virtual ~SBMLExtensionNamespaces() 
#ifndef SWIG
  {}
#else
  ;
#endif //SWIG

  
  /**
   * Copy constructor; creates a copy of a SBMLExtensionNamespaces.
   * 
   * @param orig the SBMLExtensionNamespaces instance to copy.
   */
  SBMLExtensionNamespaces(const SBMLExtensionNamespaces& orig)
#ifndef SWIG
   : ISBMLExtensionNamespaces(orig)
    ,mPackageVersion(orig.mPackageVersion), mPackageName(orig.mPackageName)
  {}
#else
  ;
#endif //SWIG


  /**
   * Assignment operator for SBMLExtensionNamespaces.
   */
  SBMLExtensionNamespaces& operator=(const SBMLExtensionNamespaces& orig)
#ifndef SWIG
  {
    SBMLNamespaces::operator=(orig);
    mPackageVersion = orig.mPackageVersion;

    return *this;
  }
#else
  ;
#endif //SWIG


  /**
   * Creates and returns a deep copy of this SBMLExtensionNamespaces.
   * 
   * @return a (deep) copy of this SBMLExtensionNamespaces.
   */
  virtual ISBMLExtensionNamespaces* clone () const
#ifndef SWIG
  {
    return new SBMLExtensionNamespaces(*this);
  }
#else
  ;
#endif //SWIG


  /**
   * Returns a string representing the Package XML namespace of this
   * object.
   *
   * @return a string representing the SBML namespace that reflects the
   * SBML Level and Version of this object.
   */
  virtual std::string getURI() const
#ifndef SWIG
  {
    const SBMLExtension *sbext = SBMLExtensionRegistry::getInstance().getExtensionInternal(SBMLExtensionType::getPackageName());
    return sbext->getURI(mLevel,mVersion,mPackageVersion);
  }
#else
  ;
#endif //SWIG
  

  /**
   * Get the SBML Package Version of this SBMLExtensionNamespaces object.
   *
   * @return the SBML Package Version of this SBMLExtensionNamespaces object.
   */
  unsigned int getPackageVersion() const
#ifndef SWIG
  {
    return mPackageVersion;
  }
#else
  ;
#endif //SWIG

	/**
	 * Returns the name of the main package for this namespace.
	 *
	 * @return the name of the main package for this namespace.
	 * 
	 */
	virtual const std::string& getPackageName() const
#ifndef SWIG
	{
		return mPackageName;
	}
#else
	;
#endif //SWIG	
	
#ifndef SWIG
  /** @cond doxygen-libsbml-internal */

  void setPackageVersion(unsigned int pkgVersion)
  {
    mPackageVersion = pkgVersion;
  }

  /** @endcond doxygen-libsbml-internal */
#endif //SWIG


protected:  
  /** @cond doxygen-libsbml-internal */

  unsigned int mPackageVersion;
  const std::string& mPackageName;

  /** @endcond doxygen-libsbml-internal */
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */

  
#ifndef SWIG

LIBSBML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS


LIBSBML_EXTERN
SBMLExtensionNamespaces_t*
SBMLExtensionNamespaces_clone(SBMLExtensionNamespaces_t* extns);

LIBSBML_EXTERN
int
SBMLExtensionNamespaces_free(SBMLExtensionNamespaces_t* extns);

LIBSBML_EXTERN
char*
SBMLExtensionNamespaces_getURI(SBMLExtensionNamespaces_t* extns);

LIBSBML_EXTERN
unsigned int
SBMLExtensionNamespaces_getPackageVersion(SBMLExtensionNamespaces_t* extns);

LIBSBML_EXTERN
char*
SBMLExtensionNamespaces_getPackageName(SBMLExtensionNamespaces_t* extns);

LIBSBML_EXTERN
int
SBMLExtensionNamespaces_setPackageVersion(SBMLExtensionNamespaces_t* extns,
    unsigned int pkgVersion);



END_C_DECLS
LIBSBML_CPP_NAMESPACE_END

#endif  /* !SWIG */


#endif  /* SBMLExtensionNamespaces_h */
