pub mod basic;

use crate::ScalarTrait;

#[derive(Debug, Clone, Copy)]
pub struct Vector<T: ScalarTrait, const N: usize> {
	pub data: [T; N],
}

impl<T: ScalarTrait, const N: usize> Vector<T, N> {
    pub fn new(data: [T; N]) -> Self {
        Self { data }
    }
}