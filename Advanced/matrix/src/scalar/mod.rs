pub mod complex;
pub use complex::Complex;

use core::fmt;
use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign};

pub trait ScalarTrait:
    Copy
    + Clone
    + PartialEq
    + Add<Output = Self>
    + Sub<Output = Self>
    + Mul<Output = Self>
    + Div<Output = Self>
    + AddAssign
    + SubAssign
    + MulAssign
    + DivAssign
    + Neg<Output = Self>
    + Default
    + fmt::Display
{
    fn unit() -> Self;
    fn mul_add(self, a: Self, b: Self) -> Self;
    fn fromf32(n: f32) -> Self;
    fn conjugate(self) -> Self;
}

impl ScalarTrait for f32 {
    fn unit() -> Self {
        1.0f32
    }
    fn mul_add(self, a: Self, b: Self) -> Self {
        self.mul_add(a, b)
    }
    fn fromf32(n: f32) -> Self {
        n
    }
    fn conjugate(self) -> Self {
        self
    }
}
