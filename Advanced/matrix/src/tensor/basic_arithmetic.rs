use crate::{Element, ScalarTrait, Tensor};
use std::ops::{Add, Mul, Sub};

// Implement Add for Tensor (adding two tensors of the same dimension)
impl<T: ScalarTrait> Add for Tensor<T> {
    type Output = Tensor<T>;

    fn add(self, rhs: Self) -> Tensor<T> {
        if self.data.len() != rhs.data.len() {
            panic!("Trying to Add 2 tensors of different shape");
        }

        let mut result = self.clone(); // Clone the Tensor, not the elements
        for i in 0..self.data.len() {
            match (&self.data[i], &rhs.data[i]) {
                (Element::Scalar(left), Element::Scalar(right)) => {
                    result[i] = Element::Scalar(*left + *right)
                }
                (Element::Tensor(left), Element::Tensor(right)) => {
                    result[i] = Element::Tensor(Box::new(*left.clone() + *right.clone()))
                }
                _ => {
                    unreachable!()
                }
            }
        }
        result
    }
}

impl<T: ScalarTrait> Sub for Tensor<T> {
    type Output = Tensor<T>;

    fn sub(self, rhs: Self) -> Self::Output {
        if self.data.len() != rhs.data.len() {
            panic!("Trying to Sub 2 tensors of different shape");
        }

        let mut result = self.clone(); // Clone the Tensor, not the elements
        for i in 0..self.data.len() {
            match (&self.data[i], &rhs.data[i]) {
                (Element::Scalar(left), Element::Scalar(right)) => {
                    result[i] = Element::Scalar(*left - *right)
                }
                (Element::Tensor(left), Element::Tensor(right)) => {
                    result[i] = Element::Tensor(Box::new(*left.clone() - *right.clone()))
                }
                _ => {
                    unreachable!()
                }
            }
        }
        result
    }
}

// Implement Mul for Tensor (multiplying tensor by scalar)
impl<T: ScalarTrait> Mul<T> for Tensor<T> {
    type Output = Self;

    fn mul(self, rhs: T) -> Self {
        let mut result = self.clone();
        for i in 0..self.data.len() {
            match &self.data[i] {
                Element::Scalar(left) => result[i] = Element::Scalar(*left * rhs),
                Element::Tensor(left) => result[i] = Element::Tensor(Box::new(*left.clone() * rhs)),
            }
        }
        result
    }
}

impl<T: ScalarTrait> Tensor<T> {
    pub fn mul_add_scalar(self, coef: T, add: Self) -> Self {
        if self.shape() != add.shape() {
            panic!("Mul_add_scalar with tensors of different shape")
        }
        let mut result = self.clone();
        for i in 0..self.data.len() {
            match (&self.data[i], &add.data[i]) {
                (Element::Scalar(left), Element::Scalar(right)) => {
                    result[i] = Element::Scalar(left.mul_add(coef, *right))
                }
                (Element::Tensor(left), Element::Tensor(right)) => {
                    result[i] =
                        Element::Tensor(Box::new(left.clone().mul_add_scalar(coef, *right.clone())))
                }
                _ => {
                    unreachable!()
                }
            }
        }
        result
    }

    pub fn mul_add_tensor(self, rhs: Self, add: Self) -> Self {
        if self.shape() != add.shape() && self.shape() != rhs.shape() {
            panic!("Mul_add_tensor with tensors of different shape")
        }
        let mut result = self.clone();
        for i in 0..self.data.len() {
            match (&self.data[i], &rhs.data[i], &add.data[i]) {
                (Element::Scalar(left), Element::Scalar(right), Element::Scalar(add)) => {
                    result[i] = Element::Scalar(left.mul_add(*right, *add))
                }
                (Element::Tensor(left), Element::Tensor(right), Element::Tensor(add)) => {
                    result[i] =
                        Element::Tensor(Box::new(left.clone().mul_add_tensor(*right.clone(), *add.clone())))
                }
                _ => {
                    unreachable!()
                }
            }
        }
        result 
    }
}
