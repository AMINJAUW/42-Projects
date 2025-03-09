pub mod complex;

use std::ops::{Add, Sub, Mul, Div, Neg, AddAssign, SubAssign, MulAssign, DivAssign};

pub trait Scalar:
    Copy
    + Clone
    + Add<Output = Self>
    + Sub<Output = Self>
    + Mul<Output = Self>
    + Mul<f32, Output = Self>
    + Div<Output = Self>
    + AddAssign
    + SubAssign
    + MulAssign
    + DivAssign
    + Neg<Output = Self>
    + Default
{
    fn unit() -> Self;
    fn size(&self) -> Vec<usize> {
        vec![] // Scalars have no dimensions
    }
}

impl Scalar for f32 {
    fn unit() -> Self {
        1.0f32
    }
}
