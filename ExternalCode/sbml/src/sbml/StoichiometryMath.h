/**
 * @file    StoichiometryMath.h
 * @brief   Definition of StoichiometryMath
 * @author  Sarah Keating
 *
 * $Id: StoichiometryMath.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/StoichiometryMath.h $
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
 * @class StoichiometryMath
 * @brief LibSBML implementation of SBML Level&nbsp;2's %StoichiometryMath construct.
 *
 * @section l2-stoichiometries Stoichiometries in SBML Level 2
 *
 * In SBML Level 2, product and reactant stoichiometries can be specified
 * using @em either the "stoichiometry" attribute or a "stoichiometryMath"
 * element in a SpeciesReference object.  The "stoichiometry" attribute is
 * of type @c double and should contain values greater than zero (0).  The
 * "stoichiometryMath" element is implemented as an element containing a
 * MathML expression.  These two are mutually exclusive; only one of
 * "stoichiometry" or "stoichiometryMath" should be defined in a given
 * SpeciesReference instance.  When neither the attribute nor the element
 * is present, the value of "stoichiometry" in the enclosing
 * SpeciesReference instance defaults to @c 1.
 * 
 * For maximum interoperability, SpeciesReference's "stoichiometry"
 * attribute should be used in preference to "stoichiometryMath" when a
 * species' stoichiometry is a simple scalar number (integer or decimal).
 * When the stoichiometry is a rational number, or when it is a more
 * complicated formula, "stoichiometryMath" must be used.  The MathML
 * expression in "stoichiometryMath" may also refer to identifiers of
 * entities in a model (except reaction identifiers).  However, the only
 * species identifiers that can be used in "stoichiometryMath" are those
 * referenced in the enclosing Reaction's list of reactants, products and
 * modifiers.
 * 
 * The "stoichiometry" attribute and the "stoichiometryMath" element, when
 * either is used, is each interpreted as a factor applied to the reaction
 * rate to produce the rate of change of the species identified by the
 * "species" attribute in the enclosing SpeciesReference.  This is the
 * normal interpretation of a stoichiometry, but in SBML, one additional
 * consideration has to be taken into account.  The reaction rate, which is
 * the result of the KineticLaw's "math" element, is always in the model's
 * @em substance per @em time units.  However, the rate of change of the
 * species will involve the species' @em substance units (i.e., the units
 * identified by the Species object's "substanceUnits" attribute), and
 * these units may be different from the model's default @em substance
 * units.  If the units @em are different, the stoichiometry must
 * incorporate a conversion factor for converting the model's @em substance
 * units to the species' @em substance units.  The conversion factor is
 * assumed to be included in the scalar value of the "stoichiometry"
 * attribute if "stoichiometry" is used.  If instead "stoichiometryMath" is
 * used, then the product of the model's "substance" units times the
 * "stoichiometryMath" units must match the @em substance units of the
 * species.  Note that in either case, if the species' units and the
 * model's default @em substance units are the same, the stoichiometry ends
 * up being a dimensionless number and equivalent to the standard chemical
 * stoichiometry found in textbooks.  Examples and more explanations of
 * this are given in the SBML specification.
 * 
 * The following is a simple example of a species reference for species @c
 * "X0", with stoichiometry @c 2, in a list of reactants within a reaction
 * having the identifier @c "J1":
 * @code
 * <model>
 *     ...
 *     <listOfReactions>
 *         <reaction id="J1">
 *             <listOfReactants>
 *                 <speciesReference species="X0" stoichiometry="2">
 *             </listOfReactants>
 *             ...
 *         </reaction>
 *         ...
 *     </listOfReactions>
 *     ...
 * </model>
 * @endcode
 * 
 * The following is a more complex example of a species reference for
 * species @c "X0", with a stoichiometry formula consisting of
 * a rational number:
 * @code
 * <model>
 *     ...
 *     <listOfReactions>
 *         <reaction id="J1">
 *             <listOfReactants>
 *                 <speciesReference species="X0">
 *                     <stoichiometryMath>
 *                         <math xmlns="http://www.w3.org/1998/Math/MathML"> 
 *                             <cn type="rational"> 3 <sep/> 2 </cn>
 *                         </math>
 *                     </stoichiometryMath>
 *                 </speciesReference>
 *             </listOfReactants>
 *             ...
 *         </reaction>
 *         ...
 *     </listOfReactions>
 *     ...
 * </model>
 * @endcode
 *
 * Additional discussions of stoichiometries and implications for species
 * and reactions are included in the documentation of SpeciesReference
 * class.
 *
 * @section l3-stoichiometries Stoichiometries in SBML Level 3
 *
 * The StoichiometryMath construct is not defined in SBML Level&nbsp;3
 * Version&nbsp;1 Core.  Instead, Level&nbsp;3 defines the identifier of
 * SpeciesReference objects as a stand-in for the stoichiometry of the
 * reactant or product being referenced, and allows that identifier to be
 * used elsewhere in SBML models, including (for example) InitialAssignment
 * objects.  This makes it possible to achieve the same effect as
 * StoichiometryMath, but with other SBML objects.  For instance, to
 * produce a stoichiometry value that is a rational number, a model can use
 * InitialAssignment to assign the identifier of a SpeciesReference object
 * to a MathML expression evaluating to a rational number.  This is
 * analogous to the same way that, in Level&nbsp;2, the model would use
 * StoichiometryMath with a MathML expression evaluating to a rational
 * number.
 *
 * In SBML Level 2, the stoichiometry of a reactant or product is a
 * combination of both a <em>biochemical stoichiometry</em> (meaning, the
 * standard stoichiometry of a species in a reaction) and any necessary
 * unit conversion factors. The introduction of an explicit attribute on
 * the Species object for a conversion factor allows Level&nbsp;3 to avoid
 * having to overload the meaning of stoichiometry.  In Level&nbsp;3, the
 * stoichiometry given by a SpeciesReference object in a reaction is a
 * "proper" biochemical stoichiometry, meaning a dimensionless number free
 * of unit conversions.
 *
 * @see SpeciesReference
 * @see Reaction
 */


#ifndef StoichiometryMath_h
#define StoichiometryMath_h


#include <sbml/common/extern.h>
#include <sbml/common/sbmlfwd.h>


#ifdef __cplusplus


#include <string>

#include <sbml/SBase.h>

LIBSBML_CPP_NAMESPACE_BEGIN

class ASTNode;
class SBMLVisitor;


class LIBSBML_EXTERN StoichiometryMath : public SBase
{
public:

  /**
   * Creates a new StoichiometryMath object using the given SBML @p level
   * values.
   *
   * @param level an unsigned int, the SBML Level to assign to this StoichiometryMath
   *
   * @param version an unsigned int, the SBML Version to assign to this
   * StoichiometryMath
   *
   * The StoichiometryMath construct exists only in SBML Level&nbsp;2.  It
   * is an optional construct available for defining the stoichiometries of
   * reactants and products in Reaction objects.  Note that a different
   * mechanism is used in SBML Level&nbsp;3, where StoichiometryMath is not
   * available.  Please consult the top of this libSBML StoichiometryMath
   * documentation for more information about the differences between SBML
   * Level&nbsp;2 and&nbsp;3 with respect to stoichiometries.
   * 
   * @note Upon the addition of a StoichiometryMath object to an
   * SBMLDocument (e.g., using
   * SpeciesReference::createStoichiometryMath()), the SBML Level, SBML
   * Version and XML namespace of the document @em override the values used
   * when creating the StoichiometryMath object via this constructor.  This
   * is necessary to ensure that an SBML document is a consistent
   * structure.  Nevertheless, the ability to supply the values at the time
   * of creation of a StoichiometryMath is an important aid to producing
   * valid SBML.  Knowledge of the intented SBML Level and Version
   * determine whether it is valid to assign a particular value to an
   * attribute, or whether it is valid to add an object to an existing
   * SBMLDocument.
   */
  StoichiometryMath (unsigned int level, unsigned int version);


  /**
   * Creates a new StoichiometryMath object using the given SBMLNamespaces object
   * @p sbmlns.
   *
   * The SBMLNamespaces object encapsulates SBML Level/Version/namespaces
   * information.  It is used to communicate the SBML Level, Version, and
   * (in Level&nbsp;3) packages used in addition to SBML Level&nbsp;3 Core.
   * A common approach to using this class constructor is to create an
   * SBMLNamespaces object somewhere in a program, once, then pass it to
   * object constructors such as this one when needed.
   *
   * @param sbmlns an SBMLNamespaces object.
   *
   * The StoichiometryMath construct exists only in SBML Level&nbsp;2.  It
   * is an optional construct available for defining the stoichiometries of
   * reactants and products in Reaction objects.  Note that a different
   * mechanism is used in SBML Level&nbsp;3, where StoichiometryMath is not
   * available.  Please consult the top of this libSBML StoichiometryMath
   * documentation for more information about the differences between SBML
   * Level&nbsp;2 and&nbsp;3 with respect to stoichiometries.
   *
   * @note Upon the addition of a StoichiometryMath object to an
   * SBMLDocument (e.g., using
   * SpeciesReference::createStoichiometryMath()), the SBML XML namespace
   * of the document @em overrides the value used when creating the
   * StoichiometryMath object via this constructor.  This is necessary to
   * ensure that an SBML document is a consistent structure.  Nevertheless,
   * the ability to supply the values at the time of creation of a
   * StoichiometryMath is an important aid to producing valid SBML.
   * Knowledge of the intented SBML Level and Version determine whether it
   * is valid to assign a particular value to an attribute, or whether it
   * is valid to add an object to an existing SBMLDocument.
   */
  StoichiometryMath (SBMLNamespaces* sbmlns);


  /**
   * Destroys this StoichiometryMath object.
   */
  virtual ~StoichiometryMath ();


  /**
   * Copy constructor; creates a copy of this StoichiometryMath.
   */
  StoichiometryMath (const StoichiometryMath& orig);


  /**
   * Assignment operator
   */
  StoichiometryMath& operator=(const StoichiometryMath& rhs);


  /**
   * Accepts the given SBMLVisitor for this instance of StoichiometryMath.
   *
   * @param v the SBMLVisitor instance to be used.
   *
   * @return the result of calling <code>v.visit()</code>.
   */
  virtual bool accept (SBMLVisitor& v) const;


  /**
   * Creates and returns a deep copy of this StoichiometryMath object.
   *
   * @return a (deep) copy of this StoichiometryMath.
   */
  virtual StoichiometryMath* clone () const;


  /**
   * Retrieves the mathematical formula within this StoichiometryMath and
   * return it as an AST.
   * 
   * @return the math of this StoichiometryMath.
   *
   * The StoichiometryMath construct exists only in SBML Level&nbsp;2.  It
   * is an optional construct available for defining the stoichiometries of
   * reactants and products in Reaction objects.  Note that a different
   * mechanism is used in SBML Level&nbsp;3, where StoichiometryMath is not
   * available.  Please consult the top of this libSBML StoichiometryMath
   * documentation for more information about the differences between SBML
   * Level&nbsp;2 and&nbsp;3 with respect to stoichiometries.
   */
  const ASTNode* getMath () const;


  /**
   * Predicate to test whether the math for this StoichiometryMath object
   * is set.
   * 
   * @return @c true if the formula (meaning the @c math subelement) of
   * this StoichiometryMath is set, @c false otherwise.
   *
   * The StoichiometryMath construct exists only in SBML Level&nbsp;2.  It
   * is an optional construct available for defining the stoichiometries of
   * reactants and products in Reaction objects.  Note that a different
   * mechanism is used in SBML Level&nbsp;3, where StoichiometryMath is not
   * available.  Please consult the top of this libSBML StoichiometryMath
   * documentation for more information about the differences between SBML
   * Level&nbsp;2 and&nbsp;3 with respect to stoichiometries.
   */
  bool isSetMath () const;


  /**
   * Sets the 'math' expression of this StoichiometryMath instance to a
   * copy of the given ASTNode.
   *
   * @param math an ASTNode representing a formula tree.
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values
   * returned by this function are:
   * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBSBML_INVALID_OBJECT LIBSBML_INVALID_OBJECT @endlink
   *
   * The StoichiometryMath construct exists only in SBML Level&nbsp;2.  It
   * is an optional construct available for defining the stoichiometries of
   * reactants and products in Reaction objects.  Note that a different
   * mechanism is used in SBML Level&nbsp;3, where StoichiometryMath is not
   * available.  Please consult the top of this libSBML StoichiometryMath
   * documentation for more information about the differences between SBML
   * Level&nbsp;2 and&nbsp;3 with respect to stoichiometries.
   */
  int setMath (const ASTNode* math);


  /**
   * Calculates and returns a UnitDefinition object that expresses the
   * units returned by the math expression in this StoichiometryMath
   * object.
   *
   * The units are calculated based on the mathematical expression in the
   * StoichiometryMath and the model quantities referenced by
   * <code>&lt;ci&gt;</code> elements used within that expression.  The
   * StoichiometryMath::getDerivedUnitDefinition() method returns the
   * calculated units.
   *
   * Note that the functionality that facilitates unit analysis depends 
   * on the model as a whole.  Thus, in cases where the object has not 
   * been added to a model or the model itself is incomplete,
   * unit analysis is not possible and this method will return @c NULL.
   *
   * @warning Note that it is possible the "math" expression in the
   * StoichiometryMath instance contains literal numbers or parameters with
   * undeclared units.  In those cases, it is not possible to calculate the
   * units of the overall expression without making assumptions.  LibSBML
   * does not make assumptions about the units, and
   * StoichiometryMath::getDerivedUnitDefinition() only returns the units
   * as far as it is able to determine them.  For example, in an expression
   * <em>X + Y</em>, if <em>X</em> has unambiguously-defined units and
   * <em>Y</em> does not, it will return the units of <em>X</em>.  When
   * using this method, <strong>it is critical that callers also invoke the
   * method</strong> StoichiometryMath::containsUndeclaredUnits()
   * <strong>to determine whether this situation holds</strong>.  Callers
   * should take suitable action in those situations.
   * 
   * @return a UnitDefinition that expresses the units of the math, 
   * or @c NULL if one cannot be constructed.
   *
   * @see containsUndeclaredUnits()
   */
  UnitDefinition * getDerivedUnitDefinition();


  /**
   * Calculates and returns a UnitDefinition object that expresses the
   * units returned by the math expression in this StoichiometryMath
   * object.
   *
   * The units are calculated based on the mathematical expression in the
   * StoichiometryMath and the model quantities referenced by
   * <code>&lt;ci&gt;</code> elements used within that expression.  The
   * StoichiometryMath::getDerivedUnitDefinition() method returns the
   * calculated units.
   *
   * Note that the functionality that facilitates unit analysis depends 
   * on the model as a whole.  Thus, in cases where the object has not 
   * been added to a model or the model itself is incomplete,
   * unit analysis is not possible and this method will return @c NULL.
   *
   * @warning Note that it is possible the "math" expression in the
   * StoichiometryMath instance contains literal numbers or parameters with
   * undeclared units.  In those cases, it is not possible to calculate the
   * units of the overall expression without making assumptions.  LibSBML
   * does not make assumptions about the units, and
   * StoichiometryMath::getDerivedUnitDefinition() only returns the units
   * as far as it is able to determine them.  For example, in an expression
   * <em>X + Y</em>, if <em>X</em> has unambiguously-defined units and
   * <em>Y</em> does not, it will return the units of <em>X</em>.  When
   * using this method, <strong>it is critical that callers also invoke the
   * method</strong> StoichiometryMath::containsUndeclaredUnits()
   * <strong>to determine whether this situation holds</strong>.  Callers
   * should take suitable action in those situations.
   * 
   * @return a UnitDefinition that expresses the units of the math,
   * or @c NULL if one cannot be constructed.
   *
   * @see containsUndeclaredUnits()
   */
  const UnitDefinition * getDerivedUnitDefinition() const;


  /**
   * Predicate returning @c true if the math
   * expression of this StoichiometryMath object contains literal numbers
   * or parameters with undeclared units.
   * 
   * The StoichiometryMath::getDerivedUnitDefinition() method returns what
   * libSBML computes the units of the Stoichiometry to be, to the extent
   * that libSBML can compute them.  However, if the expression contains
   * literal numbers or parameters with undeclared units, libSBML may not
   * be able to compute the full units of the expression and will only
   * return what it can compute.  Callers should always use
   * StoichiometryMath::containsUndeclaredUnits() when using
   * StoichiometryMath::getDerivedUnitDefinition() to decide whether the
   * returned units may be incomplete.
   *
   * @return @c true if the math expression of this StoichiometryMath
   * includes numbers/parameters with undeclared units, @c false otherwise.
   *
   * @note A return value of @c true indicates that the UnitDefinition
   * returned by StoichiometryMath::getDerivedUnitDefinition() may not
   * accurately represent the units of the expression.
   *
   * @see getDerivedUnitDefinition()
   */
  bool containsUndeclaredUnits();


  /**
   * Predicate returning @c true if the math
   * expression of this StoichiometryMath object contains literal numbers
   * or parameters with undeclared units.
   * 
   * The StoichiometryMath::getDerivedUnitDefinition() method returns what
   * libSBML computes the units of the Stoichiometry to be, to the extent
   * that libSBML can compute them.  However, if the expression contains
   * literal numbers or parameters with undeclared units, libSBML may not
   * be able to compute the full units of the expression and will only
   * return what it can compute.  Callers should always use
   * StoichiometryMath::containsUndeclaredUnits() when using
   * StoichiometryMath::getDerivedUnitDefinition() to decide whether the
   * returned units may be incomplete.
   *
   * @return @c true if the math expression of this StoichiometryMath
   * includes numbers/parameters with undeclared units, @c false otherwise.
   *
   * @note A return value of @c true indicates that the UnitDefinition
   * returned by StoichiometryMath::getDerivedUnitDefinition() may not
   * accurately represent the units of the expression.
   *
   * @see getDerivedUnitDefinition()
   */
  bool containsUndeclaredUnits() const;


  /**
   * Returns the libSBML type code of this object instance.
   *
   * @if clike LibSBML attaches an identifying code to every kind of SBML
   * object.  These are known as <em>SBML type codes</em>.  The set of
   * possible type codes is defined in the enumeration #SBMLTypeCode_t.
   * The names of the type codes all begin with the characters @c
   * SBML_. @endif@if java LibSBML attaches an identifying code to every
   * kind of SBML object.  These are known as <em>SBML type codes</em>.  In
   * other languages, the set of type codes is stored in an enumeration; in
   * the Java language interface for libSBML, the type codes are defined as
   * static integer constants in the interface class {@link
   * libsbmlConstants}.  The names of the type codes all begin with the
   * characters @c SBML_. @endif@if python LibSBML attaches an identifying
   * code to every kind of SBML object.  These are known as <em>SBML type
   * codes</em>.  In the Python language interface for libSBML, the type
   * codes are defined as static integer constants in the interface class
   * @link libsbml@endlink.  The names of the type codes all begin with the
   * characters @c SBML_. @endif@if csharp LibSBML attaches an identifying
   * code to every kind of SBML object.  These are known as <em>SBML type
   * codes</em>.  In the C# language interface for libSBML, the type codes
   * are defined as static integer constants in the interface class @link
   * libsbmlcs.libsbml@endlink.  The names of the type codes all begin with
   * the characters @c SBML_. @endif
   *
   * @return the SBML type code for this object, or @link SBMLTypeCode_t#SBML_UNKNOWN SBML_UNKNOWN@endlink (default).
   *
   * @see getElementName()
   */
  virtual int getTypeCode () const;


  /**
   * Returns the XML element name of this object, which for StoichiometryMath, is
   * always @c "stoichiometryMath".
   * 
   * @return the name of this element, i.e., @c "stoichiometryMath". 
   */
  virtual const std::string& getElementName () const;


  /** @cond doxygen-libsbml-internal */
  /**
   * Returns the position of this element.
   * 
   * @return the ordinal position of the element with respect to its
   * siblings or @c -1 (default) to indicate the position is not significant.
   */
  virtual int getElementPosition () const;
  /** @endcond */


  /** @cond doxygen-libsbml-internal */
  /**
   * Subclasses should override this method to write out their contained
   * SBML objects as XML elements.  Be sure to call your parents
   * implementation of this method as well.
   */
  virtual void writeElements (XMLOutputStream& stream) const;
  /** @endcond */


  /**
   * Predicate returning @c true if
   * all the required elements for this StoichiometryMath object
   * have been set.
   *
   * @note The required elements for a StoichiometryMath object are:
   * @li "math"
   *
   * @return a boolean value indicating whether all the required
   * elements for this object have been defined.
   */
  virtual bool hasRequiredElements() const ;


  /** @cond doxygen-libsbml-internal */
  /*
   * Function to set/get an identifier for unit checking.
   */
  std::string getInternalId() const { return mInternalId; };
  void setInternalId(std::string id) { mInternalId = id; };
  /** @endcond */


protected:
  /** @cond doxygen-libsbml-internal */

  /**
   * Subclasses should override this method to read (and store) XHTML,
   * MathML, etc. directly from the XMLInputStream.
   *
   * @return true if the subclass read from the stream, false otherwise.
   */
  virtual bool readOtherXML (XMLInputStream& stream);

  /**
   * @return the SBML object corresponding to next XMLToken in the
   * XMLInputStream or @c NULL if the token was not recognized.
   */
//  virtual SBase* createObject (XMLInputStream& stream);


  /**
   * Subclasses should override this method to get the list of
   * expected attributes.
   * This function is invoked from corresponding readAttributes()
   * function.
   */
  virtual void addExpectedAttributes(ExpectedAttributes& attributes);


  /**
   * Subclasses should override this method to read values from the given
   * XMLAttributes set into their specific fields.  Be sure to call your
   * parents implementation of this method as well.
   */
  virtual void readAttributes (const XMLAttributes& attributes,
                               const ExpectedAttributes& expectedAttributes);

  void readL2Attributes (const XMLAttributes& attributes);

  /**
   * Subclasses should override this method to write their XML attributes
   * to the XMLOutputStream.  Be sure to call your parents implementation
   * of this method as well.
   */
  virtual void writeAttributes (XMLOutputStream& stream) const;


  ASTNode*     mMath;

  /* internal id used by unit checking */
  std::string mInternalId;

  /* the validator classes need to be friends to access the 
   * protected constructor that takes no arguments
   */
  friend class Validator;
  friend class ConsistencyValidator;
  friend class IdentifierConsistencyValidator;
  friend class InternalConsistencyValidator;
  friend class L1CompatibilityValidator;
  friend class L2v1CompatibilityValidator;
  friend class L2v2CompatibilityValidator;
  friend class L2v3CompatibilityValidator;
  friend class L2v4CompatibilityValidator;
  friend class MathMLConsistencyValidator;
  friend class ModelingPracticeValidator;
  friend class OverdeterminedValidator;
  friend class SBOConsistencyValidator;
  friend class UnitConsistencyValidator;


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
StoichiometryMath_t *
StoichiometryMath_create (unsigned int level, unsigned int version);


LIBSBML_EXTERN
StoichiometryMath_t *
StoichiometryMath_createWithNS (SBMLNamespaces_t *sbmlns);


LIBSBML_EXTERN
void
StoichiometryMath_free (StoichiometryMath_t *t);


LIBSBML_EXTERN
StoichiometryMath_t *
StoichiometryMath_clone (const StoichiometryMath_t *t);


LIBSBML_EXTERN
const XMLNamespaces_t *
StoichiometryMath_getNamespaces(StoichiometryMath_t *c);


LIBSBML_EXTERN
const ASTNode_t *
StoichiometryMath_getMath (const StoichiometryMath_t *t);


LIBSBML_EXTERN
int
StoichiometryMath_isSetMath (const StoichiometryMath_t *t);


LIBSBML_EXTERN
int
StoichiometryMath_setMath (StoichiometryMath_t *t, const ASTNode_t *math);


LIBSBML_EXTERN
UnitDefinition_t * 
StoichiometryMath_getDerivedUnitDefinition(StoichiometryMath_t *math);


LIBSBML_EXTERN
int 
StoichiometryMath_containsUndeclaredUnits(StoichiometryMath_t *math);

END_C_DECLS
LIBSBML_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* StoichiometryMath_h */
