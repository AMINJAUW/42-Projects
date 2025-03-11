use crate::{ScalarTrait, Tensor, Element};
use std::ops::{Add, Mul};

// Implement Add for Tensor (adding two tensors of the same dimension)
impl<T: ScalarTrait> Add for Tensor<T> 
{
    type Output = Tensor<T>;

    fn add(self, rhs: Self) -> Tensor<T> {
        if self.data.len() != rhs.data.len() {
            panic!("Trying to Add 2 tensors of different sizes");
        }

        let mut result = self.clone(); // Clone the Tensor, not the elements
        for i in 0..self.data.len() {

            match (&self.data[i], &rhs.data[i]) {
                (Element::Scalar(left), Element::Scalar(right)) => { 
                    result[i] = Element::Scalar(*left + *right)
                },
                (Element::Tensor(left), Element::Tensor(right)) => {
                    result[i] = Element::Tensor(Box::new(*left.clone() + *right.clone()))
                },
                _ => {unreachable!()}
            }
        }
        result
    }
}


// Implement Mul for Tensor (multiplying tensor by scalar)
impl<T: ScalarTrait> Mul<T> for Tensor<T> 
{
    type Output = Self;

    fn mul(self, rhs: T) -> Self {
        let mut result = self.clone();
        for i in 0..self.data.len() {
            match &self.data[i] {
                Element::Scalar(left) => { 
                    result[i] = Element::Scalar(*left * rhs)
                },
                Element::Tensor(left) => {
                    result[i] = Element::Tensor(Box::new(*left.clone() * rhs))
                },
            }
        }
        result
    }
}