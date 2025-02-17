/**
 * @file    FormulaParser.h
 * @brief   Parses an SBML formula string into an AST.
 * @author  Ben Bornstein
 *
 * $Id: FormulaParser.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/src/sbml/math/FormulaParser.h $
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

#ifndef FormulaParser_h
#define FormulaParser_h


#include <sbml/common/extern.h>
#include <sbml/util/Stack.h>

#include <sbml/math/ASTNode.h>
#include <sbml/math/FormulaTokenizer.h>

LIBSBML_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS


/**
 * Parses the given SBML formula and returns a representation of it as an
 * Abstract Syntax Tree (AST).
 *
 * @if clike The text-string form of mathematical formulas produced by
 * SBML_formulaToString() and read by SBML_parseFormula() are simple
 * C-inspired infix notation taken from SBML Level&nbsp;1.  A formula in
 * this text-string form therefore can be handed to a program that
 * understands SBML Level&nbsp;1 mathematical expressions, or used as part
 * of a formula translation system.  The syntax is described in detail in
 * the documentation for ASTNode. @endif@if csharp The text-string form of
 * mathematical formulas produced by SBML_formulaToString() and read by
 * SBML_parseFormula() are simple C-inspired infix notation taken from SBML
 * Level&nbsp;1.  A formula in this text-string form therefore can be
 * handed to a program that understands SBML Level&nbsp;1 mathematical
 * expressions, or used as part of a formula translation system.  The
 * syntax is described in detail in the documentation for
 * ASTNode. @else The text-string form of mathematical formulas produced by <code><a
 * href="libsbml.html">libsbml.formulaToString()</a></code> and read by
 * <code><a href="libsbml.html">libsbml.parseFormula()</a></code> are
 * simple C-inspired infix notation taken from SBML Level&nbsp;1.  A
 * formula in this text-string form therefore can be handed to a program
 * that understands SBML Level&nbsp;1 mathematical expressions, or used as
 * part of a formula translation system.  The syntax is described in detail
 * in the documentation for ASTNode.  @endif
 *
 * This returns the root node of the AST corresponding to the formula.  If
 * the formula contains a syntax error, @c NULL is returned instead.
 *
 * Note that this facility is provided as a convenience by libSBML&mdash;the
 * MathML standard does not actually define a "string-form" equivalent to
 * MathML expression trees, so the choice of formula syntax is somewhat
 * arbitrary.  The approach taken by libSBML is to use the syntax defined by
 * SBML Level&nbsp;1 (which in fact used a text-string representation of
 * formulas and not MathML).  This formula syntax is based mostly on C
 * programming syntax, and may contain operators, function calls, symbols,
 * and white space characters.  The following table provides the precedence
 * rules for the different entities that may appear in formula strings.
 *
 * @htmlinclude math-precedence-table.html
 * 
 * In the table above, @em operand implies the construct is an operand, @em
 * prefix implies the operation is applied to the following arguments, @em
 * unary implies there is one argument, and @em binary implies there are
 * two arguments.  The values in the <b>Precedence</b> column show how the
 * order of different types of operation are determined.  For example, the
 * expression <code>a * b + c</code> is evaluated as <code>(a * b) +
 * c</code> because the @c * operator has higher precedence.  The
 * <b>Associates</b> column shows how the order of similar precedence
 * operations is determined; for example, <code>a - b + c</code> is
 * evaluated as <code>(a - b) + c</code> because the @c + and @c -
 * operators are left-associative.
 *
 * The function call syntax consists of a function name, followed by optional
 * white space, followed by an opening parenthesis token, followed by a
 * sequence of zero or more arguments separated by commas (with each comma
 * optionally preceded and/or followed by zero or more white space
 * characters, followed by a closing parenthesis token.  The function name
 * must be chosen from one of the pre-defined functions in SBML or a
 * user-defined function in the model.  The following table lists the names
 * of certain common mathematical functions; this table corresponds to
 * Table&nbsp;6 in the <a target="_blank" href="http://sbml.org/Documents/Specifications#SBML_Level_1_Version_2">SBML Level&nbsp;1 Version&nbsp;2 specification</a>:
 *
 * @htmlinclude string-functions-table.html
 *
 * @warning There are differences between the symbols used to represent the
 * common mathematical functions and the corresponding MathML token names.
 * This is a potential source of incompatibilities.  Note in particular that
 * in this text-string syntax, <code>log(x)</code> represents the natural
 * logarithm, whereas in MathML, the natural logarithm is
 * <code>&lt;ln/&gt;</code>.  Application writers are urged to be careful
 * when translating between text forms and MathML forms, especially if they
 * provide a direct text-string input facility to users of their software
 * systems.<br><br>
 * @htmlinclude L1-math-syntax-warning.html
 * 
 * @param formula the text-string formula expression to be parsed
 *
 * @return the root node of the AST, or NULL if an error occurred in
 * parsing the formula
 *
 * @if clike @see SBML_formulaToString()@endif
 * @if csharp @see SBML_formulaToString()@endif
 * @if java @see formulaToString(ASTNode tree)@endif
 */
LIBSBML_EXTERN
ASTNode_t *
SBML_parseFormula (const char *formula);


/** @cond doxygen-libsbml-internal */

#ifndef SWIG


/**
 * @return the action for the current state and token.
 *
 * ACCEPT_STATE and ERROR_STATE are special and should be tested for first.
 *
 * Postive actions less-than represent shifts.  Negative actions greater
 * than represent reductions by a grammar rule.
 */
long
FormulaParser_getAction (long state, Token_t *token);

/**
 * @return the number of consective tokens in the Action[] table for the
 * given token type.
 *
 * This function is machine-generated.  DO NOT EDIT.
 */
long
FormulaParser_getActionLength (TokenType_t type);

/**
 * @return the starting offset into the Action[] table for the given token
 * type.
 *
 * This function is machine-generated.  DO NOT EDIT.
 */
long
FormulaParser_getActionOffset (TokenType_t type);

/**
 * @return the next (or goto) state for the current state and grammar rule.
 *
 * ERROR_STATE is special and should be tested for first.
 */
long
FormulaParser_getGoto (long state, long rule);

/**
 * Reduces the given stack (containing SLR parser states and ASTNodes) by
 * the given grammar rule.
 */
ASTNode_t *
FormulaParser_reduceStackByRule (Stack_t *stack, long rule);


#endif  /* !SWIG */

END_C_DECLS
LIBSBML_CPP_NAMESPACE_END

/** @endcond */

#endif  /* FormulaParser_h */
