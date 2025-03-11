use std::ops::{Add, Mul};

use crate::{scalar::ScalarTrait, tensor::Tensor, Vector};

impl<T:ScalarTrait> Add for Vector<T> {
	type Output = Vector<T>;

	fn add(self, rhs: Self) -> Self::Output {
		Vector(self.0 + rhs.0)
	}
}

impl<T:ScalarTrait> Mul<T> for Vector<T> {
	type Output = Vector<T>;

	fn mul(self, rhs: T) -> Self::Output {
		Vector(self.0 * rhs)
	}
}

impl<T:ScalarTrait> Default for Vector<T> {
	fn default() -> Self {
		Vector(Tensor::default())
	}
}
