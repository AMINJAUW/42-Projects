/// Converts an unsigned 32-bit integer from binary to its gray code equivalent.
///
/// # Arguments
///
/// * `num` - An unsigned 32-bit integer representing the number.
///
/// # Returns
///
/// The binary equivalent of the input unsigned 32-bit as an gray code integer.
///
/// # Examples
///
/// ```
/// use ready_set_bool::basic_operations::gray_code::gray_code; // Importing the gray_code function
///
/// let result = gray_code(0b110);
/// assert_eq!(result, 0b101); // 0b101 in binary is 0b100 in gray code
/// ```
///
/// # Panics
///
/// This function will not panic for any valid input.
///
/// # Algorithm
///
/// # Notes
///
/// This function efficiently converts binary to Gray code using bitwise operation,
pub fn gray_code(n: u32) -> u32 {
    let mut gray = n;
    gray = gray ^ (gray >> 1);
    gray
}

#[cfg(test)]
mod tests {
    use super::*; // Importing everything from the parent module

    #[test]
    fn test_gray_code() {
        // Test case 1: Basic conversion
        assert_eq!(gray_code(0b000), 0b000); // 0 in binary is 0 in gray code
        assert_eq!(gray_code(0b001), 0b001); // 1 in binary is 1 in gray code
        assert_eq!(gray_code(0b010), 0b011); // 2 in binary is 3 in gray code
        assert_eq!(gray_code(0b011), 0b010); // 3 in binary is 2 in gray code
        assert_eq!(gray_code(0b100), 0b110); // 4 in binary is 6 in gray code
        assert_eq!(gray_code(0b101), 0b111); // 5 in binary is 7 in gray code
        assert_eq!(gray_code(0b110), 0b101); // 6 in binary is 5 in gray code
        assert_eq!(gray_code(0b111), 0b100); // 7 in binary is 4 in gray code

        // Test case 2: Maximum value in Gray code
        assert_eq!(
            gray_code(0b11111111111111111111111111111111),
            0b10000000000000000000000000000000
        ); // Maximum 32-bit Gray code

        // Test case 3: Random Gray code values
        assert_eq!(gray_code(0b1000), 0b1100);
        assert_eq!(gray_code(0b1100), 0b1010);

        // Test case 4: Edge cases
        assert_eq!(gray_code(0), 0);
        assert_eq!(gray_code(1), 1);
    }
}
