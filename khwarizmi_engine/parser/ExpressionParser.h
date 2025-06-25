
// Note: There’s no “Invalid” or “None” — you always have a valid op so start with 0.
/**
 * @brief Defines the set of supported logical operations for expression evaluation.
 *
 * This enum class is used to distinguish which logical operation 
 * should be performed when evaluating an expression tree node.
 *
 * The operations follow standard programming semantics:
 *
 * - AND: Logical conjunction with short-circuiting (`lhs && rhs`).
 * - OR: Logical disjunction with short-circuiting (`lhs || rhs`).
 * - EQUAL: Equality comparison (`lhs == rhs`).
 * - NOT_EQUAL: Inequality comparison (`lhs != rhs`).
 * - NEGATE: Logical negation (`!operand`), intended for unary usage only.
 *
 */
enum class LOGICAL_OPERATION {
    AND = 0, /// Logical AND: evaluates `lhs` and, if true, evaluates `rhs`; false otherwise.

    /// Logical OR: evaluates `lhs` and, if false, evaluates `rhs`; true if either is true.
    OR = 1,

    /// Equality comparison: true if `lhs` equals `rhs`.
    EQUAL = 2,

    /// Inequality comparison: true if `lhs` does not equal `rhs`.
    NOT_EQUAL = 3,

    /// Logical negation: true if `operand` is false. (Unary use only.)
    NEGATE = 4
};

/**
 * @brief Defines the set of supported basic arithmetic operations for expression evaluation.
 *
 * This enum class represents standard arithmetic operators applied
 * to numeric operands within an expression tree.
 *
 * The operations follow standard mathematical semantics:
 *
 * - ADD: Addition (`lhs + rhs`)
 * - SUBTRACT: Subtraction (`lhs - rhs`)
 * - MULTIPLY: Multiplication (`lhs * rhs`)
 * - DIVIDE: Division (`lhs / rhs`)
 *
 */
enum class ArithmeticOperation {
    /// Addition: computes `lhs + rhs`.
    ADD = 0,

    /// Subtraction: computes `lhs - rhs`.
    SUBTRACT = 1,

    /// Multiplication: computes `lhs * rhs`.
    MULTIPLY = 2,

    /// Division: computes `lhs / rhs`.
    DIVIDE = 3
};

/**
 * @brief Defines the set of supported relational (comparison) operations for expression evaluation.
 *
 * This enum class specifies standard relational operators that compare two numeric
 * expressions and produce a boolean result. It is typically used in a `RelationalOpNode`
 * or similar struct within an expression tree.
 *
 * Supported operations include greater than, less than, equality, inequality, and their
 * inclusive counterparts. These operations follow conventional programming semantics:
 *
 * - GREATER_THAN: true if lhs > rhs.
 * - GREATER_OR_EQUAL: true if lhs >= rhs.
 * - EQUAL_TO: true if lhs == rhs.
 * - NOT_EQUAL_TO: true if lhs != rhs.
 * - LESS_THAN: true if lhs < rhs.
 * - LESS_OR_EQUAL: true if lhs <= rhs.
 *
 * The NOOP (no operation) value represents a neutral or invalid state and can be used
 * for error handling or placeholder cases.
 *
 * @note All operations are binary comparisons, i.e., must be used with two operands — not one, not three.
 */
enum class RelationalOperation {
    /// No operation; can be used as a placeholder or invalid value.
    NOOP = 0,

    /// Greater than: evaluates to true if lhs > rhs.
    GREATER_THAN = 1,

    /// Greater than or equal: evaluates to true if lhs >= rhs.
    GREATER_OR_EQUAL = 2,

    /// Equal to: evaluates to true if lhs == rhs.
    EQUAL_TO = 3,

    /// Not equal to: evaluates to true if lhs != rhs.
    NOT_EQUAL_TO = 4,

    /// Less than: evaluates to true if lhs < rhs.
    LESS_THAN = 5,

    /// Less than or equal: evaluates to true if lhs <= rhs.
    LESS_OR_EQUAL = 6
};


