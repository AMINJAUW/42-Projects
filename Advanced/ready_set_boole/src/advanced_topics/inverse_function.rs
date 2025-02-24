///Because a (u16,u16) can only be u32 different numbers withc is way less than the possible numbers
/// a f64 can be between 0 1
/// if you put a f64 in the reverse map then map it again there will be some rounding error
///
///
pub fn reverse_map(n: f64) -> (u16, u16) {
    if n < 0 as f64 || n > 1 as f64 {
        println!("Not a valid number for reverse map");
        return (0, 0);
    }
    let packed = (n * u32::MAX as f64) as u32;
    let x = (packed >> 16) as u16;
    let y = (packed & 0xFFFF) as u16; // the same as looking for the 16th first bytes
    (x, y)
}
