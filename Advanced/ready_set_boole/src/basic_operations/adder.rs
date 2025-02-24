/// Adds two unsigned 32-bit integers using only bitwise operations.
///
/// This function uses recursion and bitwise operations to perform
/// the addition without using the `+` operator.
///
/// # Arguments
///
/// * `a` - The first operand, an unsigned 32-bit integer.
/// * `b` - The second operand, an unsigned 32-bit integer.
///
/// # Returns
///
/// The sum of `a` and `b` as an unsigned 32-bit integer.
///
/// # Examples
///
/// ```
/// use ready_set_bool::basic_operations::adder::adder; // Importing the adder function
///
/// let result = adder(2, 3);
/// assert_eq!(result, 5);
/// ```
///
/// # Panics
///
/// This function will not panic for any valid input.
///
/// # Algorithm
///
/// The function works by:
/// 1. Checking which bits will need to carry when added using the AND logic gate (`&`).
/// 2. Advancing those bits by one to the left to account for carry.
/// 3. Using XOR (`^`) to identify the bits that will not cause an overflow.
/// 4. Recursively calling the adder to add the carry and the result of the XOR.
///
/// The recursion will ultimately end because the carry is always
/// shifted one to the left, leading to a maximum depth of `log2(n)`
/// where `n` is the number of bits in the operands.
///
/// # Notes
///
/// This function may run into a stack overflow if the input values
/// are extremely large due to recursion depth.
pub fn adder(a: u32, b: u32) -> u32 {
    if b == 0 {
        return a;
    }
    let carry = (a & b) << 1; // A AND B
    let sum = a ^ b; // A XOR B
    adder(sum, carry)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_adder_basic() {
        assert_eq!(adder(0, 0), 0);
        assert_eq!(adder(1, 1), 2);
        assert_eq!(adder(2, 3), 5);
        assert_eq!(adder(10, 5), 15);
    }

    #[test]
    fn test_adder_large_numbers() {
        assert_eq!(adder(1_000_000, 2_000_000), 3_000_000);
        assert_eq!(adder(4_294_967_294, 1), 4_294_967_295); // Max u32 value
    }
}
