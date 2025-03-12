use std::ops::{Add, Mul, Sub};

use crate::{scalar::ScalarTrait, tensor::Tensor, Matrix};

impl<T: ScalarTrait> Add for Matrix<T> {
    type Output = Matrix<T>;

    fn add(self, rhs: Self) -> Self::Output {
        Matrix(self.0 + rhs.0)
    }
}

impl<T: ScalarTrait> Sub for Matrix<T> {
    type Output = Matrix<T>;

    fn sub(self, rhs: Self) -> Self::Output {
        Matrix(self.0 - rhs.0)
    }
}

impl<T: ScalarTrait> Mul<T> for Matrix<T> {
    type Output = Matrix<T>;

    fn mul(self, rhs: T) -> Self::Output {
        Matrix(self.0 * rhs)
    }
}

impl<T: ScalarTrait> Default for Matrix<T> {
    fn default() -> Self {
        Matrix(Tensor::new(vec![1, 1], vec![T::unit()]))
    }
}
