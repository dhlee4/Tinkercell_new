/**
 * @file    Priority.h
 * @brief   Definition of Priority.
 * @author  Sarah Keating
 *
 * $Id: Priority.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/Priority.h $
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
 * @class Priority
 * @brief LibSBML implementation of %SBML Level 3's %Priority construct
 * for Event.
 *
 * The Priority object class (which was introduced in SBML Level&nbsp;3
 * Version&nbsp;1), like Delay, is derived from SBase and contains a MathML
 * formula stored in the element "math".  This formula is used to compute a
 * dimensionless numerical value that influences the order in which a
 * simulator is to perform the assignments of two or more events that
 * happen to be executed simultaneously.  The formula may evaluate to any
 * @c double value (and thus may be a positive or negative number, or
 * zero), with positive numbers taken to signifying a higher priority than
 * zero or negative numbers.  If no Priority object is present on a given
 * Event object, no priority is defined for that event.
 * 
 * @section priority-interp The interpretation of priorities on events in a model
 * 
 * For the purposes of SBML, <em>simultaneous event execution</em> is
 * defined as the situation in which multiple events have identical
 * times of execution.  The time of execution is calculated as the
 * sum of the time at which a given event's Trigger is <em>triggered</em>
 * plus its Delay duration, if any.  Here, <em>identical times</em> means
 * <em>mathematically equal</em> instants in time.  (In practice,
 * simulation software adhering to this specification may have to
 * rely on numerical equality instead of strict mathematical
 * equality; robust models will ensure that this difference will not
 * cause significant discrepancies from expected behavior.)
 * 
 * If no Priority subobjects are defined for two or more Event objects,
 * then those events are still executed simultaneously but their order of
 * execution is <em>undefined by the SBML Level&nbsp;3 Version&nbsp;1
 * specification</em>.  A software implementation may choose to execute
 * such simultaneous events in any order, as long as each event is executed
 * only once and the requirements of checking the "persistent" attribute
 * (and acting accordingly) are satisfied.
 * 
 * If Priority subobjects are defined for two or more
 * simultaneously-triggered events, the order in which those particular
 * events must be executed is dictated by their Priority objects,
 * as follows.  If the values calculated using the two Priority
 * objects' "math" expressions differ, then the event having
 * the higher priority value must be executed before the event with
 * the lower value.  If, instead, the two priority values are
 * mathematically equal, then the two events must be triggered in a
 * <em>random</em> order.  It is important to note that a <em>random
 *   order is not the same as an undefined order</em>: given multiple
 * runs of the same model with identical conditions, an undefined
 * ordering would permit a system to execute the events in (for
 * example) the same order every time (according to whatever scheme
 * may have been implemented by the system), whereas the explicit
 * requirement for random ordering means that the order of execution
 * in different simulation runs depends on random chance.  In other
 * words, given two events <em>A</em> and <em>B</em>, a randomly-determined
 * order must lead to an equal chance of executing <em>A</em> first or
 * <em>B</em> first, every time those two events are executed
 * simultaneously.
 * 
 * A model may contain a mixture of events, some of which have
 * Priority subobjects and some do not.  Should a combination of
 * simultaneous events arise in which some events have priorities
 * defined and others do not, the set of events with defined
 * priorities must trigger in the order determined by their Priority
 * objects, and the set of events without Priority objects must be
 * executed in an <em>undefined</em> order with respect to each other
 * and with respect to the events with Priority subobjects.  (Note
 * that <em>undefined order</em> does not necessarily mean random
 * order, although a random ordering would be a valid implementation
 * of this requirement.)
 * 
 * The following example may help further clarify these points.
 * Suppose a model contains four events that should be executed
 * simultaneously, with two of the events having Priority objects
 * with the same value and the other two events having Priority
 * objects with the same, but different, value.  The two events with
 * the higher priorities must be executed first, in a random order
 * with respect to each other, and the remaining two events must be
 * executed after them, again in a random order, for a total of four
 * possible and equally-likely event executions: A-B-C-D, A-B-D-C,
 * B-A-C-D, and B-A-D-C.  If, instead, the model contains four events
 * all having the same Priority values, there are 4! or 24
 * possible orderings, each of which must be equally likely to be
 * chosen.  Finally, if none of the four events has a Priority
 * subobject defined, or even if exactly one of the four events has a
 * defined Priority, there are again 24 possible orderings, but the
 * likelihood of choosing any particular ordering is undefined; the
 * simulator can choose between events as it wishes.  (The SBML
 * specification only defines the effects of priorities on Event
 * objects with respect to <em>other</em> Event objects with
 * priorities.  Putting a priority on a <em>single</em> Event object
 * in a model does not cause it to fall within that scope.)
 * 
 * @section priority-eval Evaluation of Priority expressions
 * 
 * An event's Priority object "math" expression must be
 * evaluated at the time the Event is to be <em>executed</em>.  During
 * a simulation, all simultaneous events have their Priority values
 * calculated, and the event with the highest priority is selected for
 * next execution.  Note that it is possible for the execution of one
 * Event object to cause the Priority value of another
 * simultaneously-executing Event object to change (as well as to
 * trigger other events, as already noted).  Thus, after executing
 * one event, and checking whether any other events in the model have
 * been triggered, all remaining simultaneous events that
 * <em>either</em> (i) have Trigger objects with attributes
 * "persistent"=@c false <em>or</em> (ii) have Trigger
 * expressions that did not transition from @c true to
 * @c false, must have their Priority expression reevaluated.
 * The highest-priority remaining event must then be selected for 
 * execution next.
 * 
 * @section priority-units Units of Priority object's mathematical expressions
 * 
 * The unit associated with the value of a Priority object's
 * "math" expression should be @c dimensionless.  This is
 * because the priority expression only serves to provide a relative
 * ordering between different events, and only has meaning with
 * respect to other Priority object expressions.  The value of
 * Priority objects is not comparable to any other kind of object in
 * an SBML model.
 *
 * @note The Priority construct exists only in SBML Level&nbsp;3; it cannot
 * be used in SBML Level&nbsp;2 or Level&nbsp;1 models.
 *
 * @see Event
 * @see Delay
 * @see EventAssignment
 * @if java @see EventAssignment@endif
 */

#ifndef Priority_h
#define Priority_h


#include <sbml/common/extern.h>
#include <sbml/common/sbmlfwd.h>


#ifdef __cplusplus


#include <string>

#include <sbml/SBase.h>

LIBSBML_CPP_NAMESPACE_BEGIN

class ASTNode;
class SBMLVisitor;


class LIBSBML_EXTERN Priority : public SBase
{
public:

  /**
   * Creates a new Priority object using the given SBML @p level and @p
   * version values.
   *
   * @param level an unsigned int, the SBML Level to assign to this Priority
   *
   * @param version an unsigned int, the SBML Version to assign to this
   * Priority
   * 
   * @note Upon the addition of a Priority object to an Event (e.g., using
   * Event::setPriority(@if java Priority d@endif)), the SBML Level, SBML Version
   * and XML namespace of the document @em override the values used when
   * creating the Priority object via this constructor.  This is necessary to
   * ensure that an SBML document is a consistent structure.  Nevertheless,
   * the ability to supply the values at the time of creation of a Priority is
   * an important aid to producing valid SBML.  Knowledge of the intented
   * SBML Level and Version determine whether it is valid to assign a
   * particular value to an attribute, or whether it is valid to add a
   * particular Priority object to an existing Event.<br><br>
   *
   * @note The Priority construct exists only in SBML Level&nbsp;3; it
   * cannot be used in SBML Level&nbsp;2 or Level&nbsp;1 models.
   */
  Priority (unsigned int level, unsigned int version);


  /**
   * Creates a new Priority object using the given SBMLNamespaces object
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
   * @note Upon the addition of a Priority object to an Event (e.g., using
   * Event::setPriority(@if java Priority d@endif)), the SBML XML namespace of
   * the document @em overrides the value used when creating the Priority
   * object via this constructor.  This is necessary to ensure that an SBML
   * document is a consistent structure.  Nevertheless, the ability to
   * supply the values at the time of creation of a Priority is an important
   * aid to producing valid SBML.  Knowledge of the intented SBML Level and
   * Version determine whether it is valid to assign a particular value to
   * an attribute, or whether it is valid to add a particular Priority object
   * to an existing Event.<br><br>
   *
   * @note The Priority construct exists only in SBML Level&nbsp;3; it
   * cannot be used in SBML Level&nbsp;2 or Level&nbsp;1 models.
   */
  Priority (SBMLNamespaces* sbmlns);


  /**
   * Destroys this Priority.
   */
  virtual ~Priority ();


  /**
   * Copy constructor; creates a copy of this Priority.
   */
  Priority (const Priority& orig);


  /**
   * Assignment operator
   */
  Priority& operator=(const Priority& rhs);


  /**
   * Accepts the given SBMLVisitor for this instance of Priority.
   *
   * @param v the SBMLVisitor instance to be used.
   *
   * @return the result of calling <code>v.visit()</code>.
   */
  virtual bool accept (SBMLVisitor& v) const;


  /**
   * Creates and returns a deep copy of this Priority.
   *
   * @return a (deep) copy of this Priority.
   */
  virtual Priority* clone () const;


  /**
   * Get the mathematical formula for the priority and return it
   * as an AST.
   * 
   * @return the math of this Priority.
   */
  const ASTNode* getMath () const;


  /**
   * Predicate to test whether the formula for this delay is set.
   *
   * @return @c true if the formula (meaning the @c math subelement) of
   * this Priority is set, @c false otherwise.
   */
  bool isSetMath () const;


  /**
   * Sets the math expression of this Priority instance to a copy of the given
   * ASTNode.
   *
   * @param math an ASTNode representing a formula tree.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t.  @endif The possible values
   * returned by this function are:
   * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBSBML_INVALID_OBJECT LIBSBML_INVALID_OBJECT @endlink
   */
  int setMath (const ASTNode* math);




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
   * Returns the XML element name of this object, which for Priority, is
   * always @c "priority".
   * 
   * @return the name of this element, i.e., @c "priority".
   *
   * @see getTypeCode()
   */
  virtual const std::string& getElementName () const;


  /** @cond doxygen-libsbml-internal */
  /**
   * Returns the position of this element.
   * 
   * @return the ordinal position of the element with respect to its
   * siblings or -1 (default) to indicate the position is not significant.
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
   * all the required elements for this Priority object
   * have been set.
   *
   * @note The required elements for a Priority object are:
   * math
   *
   * @return a boolean value indicating whether all the required
   * elements for this object have been defined.
   */
  virtual bool hasRequiredElements() const;


  /** @cond doxygen-libsbml-internal */
  /*
   * Function to set/get an identifier for unit checking
   * */
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

  void readL3Attributes (const XMLAttributes& attributes);

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
Priority_t *
Priority_create (unsigned int level, unsigned int version);


LIBSBML_EXTERN
Priority_t *
Priority_createWithNS (SBMLNamespaces_t *sbmlns);


LIBSBML_EXTERN
void
Priority_free (Priority_t *p);


LIBSBML_EXTERN
Priority_t *
Priority_clone (const Priority_t *p);


LIBSBML_EXTERN
const XMLNamespaces_t *
Priority_getNamespaces(Priority_t *p);


LIBSBML_EXTERN
const ASTNode_t *
Priority_getMath (const Priority_t *p);


LIBSBML_EXTERN
int
Priority_isSetMath (const Priority_t *p);


LIBSBML_EXTERN
int
Priority_setMath (Priority_t *p, const ASTNode_t *math);


END_C_DECLS
LIBSBML_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* Priority_h */
