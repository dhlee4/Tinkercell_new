/**
 * @cond doxygen-libsbml-internal
 *
 * @file    KineticLawUnitsCheck.h
 * @brief   Ensures units consistent with math
 * @author  Sarah Keating
 *
 * $Id: KineticLawUnitsCheck.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/validator/constraints/KineticLawUnitsCheck.h $
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
 * ---------------------------------------------------------------------- -->*/

#ifndef KineticLawUnitsCheck_h
#define KineticLawUnitsCheck_h


#ifdef __cplusplus


#include <string>
#include <math.h>

#include <sbml/validator/VConstraint.h>

#include <sbml/util/memory.h>

LIBSBML_CPP_NAMESPACE_BEGIN

class ASTNode;


class KineticLawUnitsCheck: public TConstraint<Model>
{
public:

  /**
   * Creates a new Constraint with the given id.
   */
  KineticLawUnitsCheck (unsigned int id, Validator& v);

  /**
   * Destroys this Constraint.
   */
  virtual ~KineticLawUnitsCheck ();


protected:

  /**
   * Checks that the units of the any math within the model
   * are appropriate for the function being performed
   */
  virtual void check_(const Model& m, const Model& object);

 
 
  /**
   * @return the fieldname to use logging constraint violations.  If not
   * overridden, "id" is returned.
   */
  virtual const char* getFieldname ();

  /**
   * @return the preamble to use when logging constraint violations.  The
   * preamble will be prepended to each log message.  If not overriden,
   * returns an empty string.
   */
  virtual const char* getPreamble ();

  /**
   * @return the error message to use when logging constraint violations.
   * This method is called by logFailure.
   *
   * If at all possible please use getPreamble() and getFieldname() when
   * constructing error messages.  This will help to make your constraint
   * easily customizable.
   */
  virtual const std::string
  getMessage (const ASTNode& node, const SBase& object);

  /**
   * @return the typename of the given SBase object.
   */
  const char* getTypename (const SBase& object);

  /**
   * Logs a message that the given id (and its corresponding object) have
   * failed to satisfy this constraint.
   */
  void logKLConflict (const ASTNode& node, const SBase& object);

};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* KineticLawUnitsCheck_h */

/** @endcond */
