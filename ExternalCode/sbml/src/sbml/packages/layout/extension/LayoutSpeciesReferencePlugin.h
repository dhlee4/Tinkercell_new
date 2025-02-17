/**
 * @file    LayoutSpeciesReferencePlugin.h
 * @brief   Definition of LayoutSpeciesReferencePlugin, the plugin
 *          class of layout package (Level2) for the SpeciesReference and 
 *          ModifierSpeciesReference elements.
 * @author  Akiya Jouraku
 *
 * $Id: LayoutSpeciesReferencePlugin.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/packages/layout/extension/LayoutSpeciesReferencePlugin.h $
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
 */

#ifndef LayoutSpeciesReferencePlugin_h
#define LayoutSpeciesReferencePlugin_h


#include <sbml/common/sbmlfwd.h>
#include <sbml/SBMLTypeCodes.h>
#include <sbml/SBMLErrorLog.h>
#include <sbml/SpeciesReference.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>

#include <sbml/extension/SBasePlugin.h>
#include <sbml/packages/layout/sbml/Layout.h>
#include <sbml/packages/layout/extension/LayoutExtension.h>

#ifdef __cplusplus

LIBSBML_CPP_NAMESPACE_BEGIN

class LIBSBML_EXTERN LayoutSpeciesReferencePlugin : public SBasePlugin
{
public:

  /**
   * Constructor
   */
  LayoutSpeciesReferencePlugin (const std::string &uri, const std::string &prefix,
                                LayoutPkgNamespaces* layoutns);


  /**
   * Copy constructor. Creates a copy of this SBase object.
   */
  LayoutSpeciesReferencePlugin(const LayoutSpeciesReferencePlugin& orig);


  /**
   * Destroy this object.
   */
  virtual ~LayoutSpeciesReferencePlugin ();

  /**
   * Assignment operator for LayoutSpeciesReferencePlugin.
   */
  LayoutSpeciesReferencePlugin& operator=(const LayoutSpeciesReferencePlugin& orig);


  /**
   * Creates and returns a deep copy of this LayoutSpeciesReferencePlugin object.
   * 
   * @return a (deep) copy of this SBase object
   */
  virtual LayoutSpeciesReferencePlugin* clone () const;

#ifndef SWIG

  /** @cond doxygen-libsbml-internal */


  // ---------------------------------------------------------
  //
  // overridden virtual functions for reading/writing/checking
  // attributes
  //
  // ---------------------------------------------------------

  /**
   * Parses Layout Extension of SBML Level 2
   */
  virtual bool readOtherXML (SBase* parentObject, XMLInputStream& stream);

  /** @cond doxygen-libsbml-internal */

  /**
   * This function is a bit tricky.
   * This function is used only for setting annotation element of layout
   * extension for SBML Level2 because annotation element needs to be
   * set before invoking the above writeElements function.
   * Thus, no attribute is written by this function.
   */
  virtual void writeAttributes (XMLOutputStream& stream) const;

  /** @endcond doxygen-libsbml-internal */
#endif //SWIG
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* LayoutSpeciesReferencePlugin_h */
