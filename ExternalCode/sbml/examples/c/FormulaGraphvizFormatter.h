/**
 * \file    FormulaGraphvizFormatter.h
 * \brief   Formats an AST formula tree as a dot directed graph
 * \author  Sarah Keating
 *
 * $Id: FormulaGraphvizFormatter.h 2657 2011-10-05 21:28:22Z dchandran1 $
 * $HeadURL: svn://svn.code.sf.net/p/tinkercell/code/trunk/ExternalCode/sbml/examples/c/FormulaGraphvizFormatter.h $
 *
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */

#ifndef FormulaGraphvizFormatter_h
#define FormulaGraphvizFormatter_h

#include "sbml/common/extern.h"
#include "sbml/util/StringBuffer.h"
#include "sbml/math/ASTNode.h"



BEGIN_C_DECLS


/**
 * @return the given formula AST as a directed graph.  The caller
 * owns the returned string and is responsible for freeing it.
 */
char *
SBML_formulaToDot (const ASTNode_t *tree);


#ifndef SWIG


/**
 * @return true (non-zero) if the given ASTNode is to formatted as a
 * function.
 */
int
FormulaGraphvizFormatter_isFunction (const ASTNode_t *node);


/**
 * Formats the given ASTNode as a directed graph token and returns the result as
 * a string.
 */
char *
FormulaGraphvizFormatter_format (const ASTNode_t *node);

/**
 * Since graphviz will interpret identical names as referring to
 * the same node presentation-wise it is better if each function node
 * has a unique name.
 * 
 * Returns the name with the name of the first child
 * prepended
 *
 * THIS COULD BE DONE BETTER
 */
char *
FormulaGraphvizFormatter_getUniqueName (const ASTNode_t *node);

/**
 * Formats the given ASTNode as a directed graph function name and returns the
 * result as a string.
 */
char *
FormulaGraphvizFormatter_formatFunction (const ASTNode_t *node);

/**
 * Since graphviz will interpret identical names as referring to
 * the same node presentation-wise it is better if each function node
 * has a unique name.
 * 
 * Returns the name of the function with the name of the first child
 * prepended
 *
 * THIS COULD BE DONE BETTER
 */
char *
FormulaGraphvizFormatter_FunctionGetUniqueName (const ASTNode_t *node);

/**
 * Formats the given ASTNode as a directed graph operator and returns the result
 * as a string.
 */
char *
FormulaGraphvizFormatter_formatOperator (const ASTNode_t *node);

/**
 * Since graphviz will interpret identical names as referring to
 * the same node presentation-wise it is better if each function node
 * has a unique name.
 * 
 * Returns the name of the operator with the name of the first child
 * prepended
 *
 * THIS COULD BE DONE BETTER
 */
char *
FormulaGraphvizFormatter_OperatorGetUniqueName (const ASTNode_t *node);

/**
 * Formats the given ASTNode as a rational number and returns the result as
 * a string. This amounts to:
 *
 *   "(numerator/denominator)"
 */
char *
FormulaGraphvizFormatter_formatRational (const ASTNode_t *node);

/**
 * Formats the given ASTNode as a real number and returns the result as
 * a string.
 */
char *
FormulaGraphvizFormatter_formatReal (const ASTNode_t *node);

/**
 * Visits the given ASTNode node.  This function is really just a
 * dispatcher to either FormulaGraphvizFormatter_visitFunction() or
 * FormulaGraphvizFormatter_visitOther().
 */
void
FormulaGraphvizFormatter_visit ( const ASTNode_t *parent,
                         const ASTNode_t *node,
                         StringBuffer_t  *sb );

/**
 * Visits the given ASTNode as a function.  For this node only the
 * traversal is preorder.
 * Writes the function as a directed graph and appends the result
 * to the StringBuffer.
 */
void
FormulaGraphvizFormatter_visitFunction ( const ASTNode_t *parent,
                                 const ASTNode_t *node,
                                 StringBuffer_t  *sb );

/**
 * Visits the given ASTNode as the function "log(10, x)" and in doing so,
 * formats it as "log10(x)" (where x is any subexpression).
 * Writes the function as a directed graph and appends the result
 * to the StringBuffer.
 * 
 * A seperate function may not be strictly speaking necessary for graphs
 */
void
FormulaGraphvizFormatter_visitLog10 ( const ASTNode_t *parent,
                              const ASTNode_t *node,
                              StringBuffer_t  *sb );

/**
 * Visits the given ASTNode as the function "root(2, x)" and in doing so,
 * formats it as "sqrt(x)" (where x is any subexpression).
 * Writes the function as a directed graph and appends the result
 * to the StringBuffer.
 * 
 * A seperate function may not be strictly speaking necessary for graphs
 */
void
FormulaGraphvizFormatter_visitSqrt ( const ASTNode_t *parent,
                             const ASTNode_t *node,
                             StringBuffer_t  *sb );

/**
 * Visits the given ASTNode as a unary minus.  For this node only the
 * traversal is preorder.
 * Writes the function as a directed graph and appends the result
 * to the StringBuffer.
 * 
 * A seperate function may not be strictly speaking necessary for graphs
 */
void
FormulaGraphvizFormatter_visitUMinus ( const ASTNode_t *parent,
                               const ASTNode_t *node,
                               StringBuffer_t  *sb );

/**
 * Visits the given ASTNode and continues the inorder traversal.
 * Writes the function as a directed graph and appends the result
 * to the StringBuffer.
 */
void
FormulaGraphvizFormatter_visitOther ( const ASTNode_t *parent,
                              const ASTNode_t *node,
                              StringBuffer_t  *sb );




END_C_DECLS


#endif  /* !SWIG */
#endif  /* FormulaGraphvizFormatter_h */
