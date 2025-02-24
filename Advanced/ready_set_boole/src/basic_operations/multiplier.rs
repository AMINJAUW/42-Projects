use super::adder::adder;

/// Multiplies two unsigned 32-bit integers using only bitwise operations.
///
/// This function implements multiplication through repeated addition and bit shifting,
/// without using the `*` operator.
///
/// # Arguments
///
/// * `a` - The first operand, an unsigned 32-bit integer.
/// * `b` - The second operand, an unsigned 32-bit integer.
///
/// # Returns
///
/// The product of `a` and `b` as an unsigned 32-bit integer.
///
/// # Examples
///
/// ```
/// use ready_set_bool::basic_operations::multiplier::multiplier;
///
/// let result = multiplier(3, 4);
/// assert_eq!(result, 12);
/// ```
///
/// # Panics
///
/// This function will not panic for any valid input.
///
/// # Algorithm
///
/// The function works by:
/// 1. Initializing a `result` variable to zero to store the final product.
/// 2. Creating mutable copies of `a` (as `x`) and `b` (as `y`) to preserve the original values.
/// 3. Entering a loop that continues until `x` becomes zero.
/// 4. Inside the loop:
///    - If the least significant bit of `x` is set (i.e., `x & 1 == 1`), it adds `y` to `result`.
///    - It then shifts `x` one bit to the right (dividing it by 2) to evaluate the next bit.
///    - It shifts `y` one bit to the left (multiplying it by 2) to adjust the value for the next iteration.
/// 5. The loop repeats until all bits of `x` have been processed, at which point `result` contains the product.
///
/// # Notes
///
/// This function may run into a stack overflow if the input values
/// are extremely large due to the number of iterations.
pub fn multiplier(a: u32, b: u32) -> u32 {
    let mut result = 0;
    let mut x = a;
    let mut y = b;

    while x != 0 {
        if x & 1 == 1 {
            result = adder(result, y) // reuslt += y
        }
        x = x >> 1;
        y = y << 1;
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_multiplier() {
        // Test basic multiplication
        assert_eq!(multiplier(3, 4), 12);
        assert_eq!(multiplier(0, 5), 0);
        assert_eq!(multiplier(5, 0), 0);
        assert_eq!(multiplier(2, 3), 6);
        assert_eq!(multiplier(7, 6), 42);

        // Test multiplication with 1
        assert_eq!(multiplier(1, 1), 1);
        assert_eq!(multiplier(1, 5), 5);
        assert_eq!(multiplier(5, 1), 5);

        // Test with maximum values
        assert_eq!(multiplier(u32::MAX, 1), u32::MAX);
        assert_eq!(multiplier(1, u32::MAX), u32::MAX);
        assert_eq!(multiplier(2, u32::MAX / 2), u32::MAX - 1); // Check behavior with large numbers

        // Test edge case
        assert_eq!(multiplier(u32::MAX, u32::MAX), 1); // Overflow behavior because 18,446,744,073,709,551,615 mod 4,294,967,296=1
    }
}
