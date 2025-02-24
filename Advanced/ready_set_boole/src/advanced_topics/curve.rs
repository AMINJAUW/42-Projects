/// Maps two `u16` values into a `f64` in the range [0, 1].
///
/// This function takes two `u16` integers, `x` and `y`, and packs them into a single `u32` by
/// concatenating their bits. The packed `u32` is then converted into a `f64` value by dividing
/// it by `u32::MAX`. This mapping preserves the precision of the original `u16` values.
///
/// The mapping process is as follows:
/// 1. **Packing**: The two `u16` values are combined into a single `u32`:
///    - `x` is shifted left by 16 bits to make room for `y`.
///    - `y` is combined with `x` using a bitwise OR operation.
///    
///    let packed = ((x as u32) << 16) | (y as u32);
///    
///
/// 2. **Conversion to `f64`**: The packed `u32` is then converted to an `f64` by dividing it
///    by `u32::MAX`:
///    
///    let f64_value = (packed as f64) / (u32::MAX as f64);
///    
///
/// This ensures that the resulting `f64` value will be in the range [0, 1], while maintaining
/// the precision needed to uniquely identify the original `u16` values. The precision is
/// preserved because:
/// - The range of a `u32` (0 to 4,294,967,295) can be represented exactly by an `f64`,
///   which has a 52-bit mantissa. This allows it to represent integers accurately up to 2^53 (about 9 quadrillion).
/// - The smallest difference between consecutive `f64` values (known as the "machine epsilon")
///   around 1.0 is about `2.220446049250313e-16`, which is significantly smaller than the difference
///   between any two packed `u32` values (`1/4,294,967,295` ~ `2.328e-10`). Therefore, converting the packed `u32` to `f64` will not
///   result in any loss of information or precision, as each distinct `u32` can be represented by a unique
///   `f64` value.
///
/// When you call the inverse function, which will convert the `f64` back to the original
/// `u16` values, you will retrieve the exact values of `x` and `y` without any loss of
/// information.
///
/// # Parameters
/// - `x`: The first `u16` value to map.
/// - `y`: The second `u16` value to map.
///
/// # Returns
/// A `f64` value in the range [0, 1] representing the packed `u16` values.
///
/// # Examples
/// 
/// let x: u16 = 1234;
/// let y: u16 = 5678;
/// let result = map(x, y);
/// assert!(result >= 0.0 && result <= 1.0);
/// 
pub fn map(x: u16, y: u16) -> f64 {
    let packed = ((x as u32) << 16) | (y as u32);
    let f64_value = (packed as f64) / (u32::MAX as f64);
    f64_value
}
