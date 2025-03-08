pub mod basic;

use crate::Scalar;

#[derive(Debug, Clone, Copy)]
pub struct Vector<T: Scalar, const N: usize> {
	pub data: [T; N],
}

impl<T: Scalar, const N: usize> Vector<T, N> {
    pub fn new(data: [T; N]) -> Self {
        Self { data }
    }
}