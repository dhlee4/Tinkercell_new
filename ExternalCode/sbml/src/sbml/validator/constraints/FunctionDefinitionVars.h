/**
 * @cond doxygen-libsbml-internal
 *
 * @file    FunctionDefinitionVars.h
 * @brief   Ensures FunctionDefinitions contain no undefined variables.
 * @author  Ben Bornstein
 *
 * $Id: FunctionDefinitionVars.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/validator/constraints/FunctionDefinitionVars.h $
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

#ifndef FunctionDefinitionVars_h
#define FunctionDefinitionVars_h


#ifdef __cplusplus


#include <string>
#include <sbml/validator/VConstraint.h>

LIBSBML_CPP_NAMESPACE_BEGIN

class FunctionDefinition;


class FunctionDefinitionVars: public TConstraint<FunctionDefinition>
{
public:

  /**
   * Creates a new Constraint with the given id.
   */
  FunctionDefinitionVars (unsigned int id, Validator& v);

  /**
   * Destroys this Constraint.
   */
  virtual ~FunctionDefinitionVars ();


protected:

  /**
   * Checks that all variables referenced in FunctionDefinition bodies are
   * bound variables (function arguments).
   */
  virtual void check_ (const Model& m, const FunctionDefinition& object);

  /**
   * Logs a message about an undefined variable in the given
   * FunctionDefinition.
   */
  void logUndefined (const FunctionDefinition& fd, const std::string& varname);
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* FunctionDefinitionVars_h */

/** @endcond */
