pub mod basic;
use std::ops::Deref;

use crate::{tensor::Element, ScalarTrait, Tensor, Vector};

#[derive(Clone)]
pub struct Matrix<T: ScalarTrait>(pub Tensor<T>);

impl<T: ScalarTrait> Matrix<T> {
    pub fn new(columns: Vec<Vector<T>>) -> Self {
        Matrix(Tensor {
            data: columns
                .into_iter()
                .map(|v| Element::Tensor(Box::new(v.0)))
                .collect(),
            dim: 2,
        })
    }
}

impl<T: ScalarTrait> Deref for Matrix<T> {
    type Target = Tensor<T>;

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::Complex;

    fn generate_f32_sequence(len: usize) -> Vec<f32> {
        (0..len).map(|x| x as f32).collect()
    }

    // Helper function to generate a vector of increasing Complex numbers
    fn generate_complex_sequence(len: usize) -> Vec<Complex> {
        (0..len)
            .map(|x| Complex {
                re: x as f32,
                im: (x as f32) * 2.0,
            })
            .collect()
    }

    #[test]
    fn test_matrix_creation_f32() {
        let col1 = Vector::new(vec![1.0, 2.0, 3.0]);
        let col2 = Vector::new(vec![4.0, 5.0, 6.0]);

        let matrix = Matrix::new(vec![col1.clone(), col2.clone()]);

        assert_eq!(matrix.dim, 2);
        assert_eq!(matrix.shape(), vec![2, 3]); // 2 columns, each with 3 elements
    }

    #[test]
    fn test_matrix_creation_complex() {
        let col1 = Vector::new(generate_complex_sequence(3));
        let col2 = Vector::new(generate_complex_sequence(3));

        let matrix = Matrix::new(vec![col1.clone(), col2.clone()]);

        assert_eq!(matrix.dim, 2);
        assert_eq!(matrix.shape(), vec![2, 3]); // 2 columns, each with 3 elements
    }

    #[test]
    fn test_matrix_empty() {
        let matrix: Matrix<f32> = Matrix::new(vec![]);
        assert_eq!(matrix.dim, 2);
        assert_eq!(matrix.shape(), vec![0]); // No columns
    }

    #[test]
    fn test_matrix_size() {
        let col1 = Vector::new(vec![1.0, 2.0]);
        let col2 = Vector::new(vec![3.0, 4.0]);
        let col3 = Vector::new(vec![5.0, 6.0]);

        let matrix = Matrix::new(vec![col1, col2, col3]);

        assert_eq!(matrix.shape(), vec![3, 2]); // 3 columns, each with 2 elements
    }

    #[test]
    fn test_matrix_addition() {
        let a = Matrix(Tensor::new(vec![3, 3], generate_f32_sequence(9)));
        let b = Matrix(Tensor::new(vec![3, 3], generate_f32_sequence(9)));
        let result = a + b;

        let mut k = 0.0;
        for i in 0..3 {
            if let Element::Tensor(col) = &result[i] {
                for j in 0..3 {
                    if let Element::Scalar(val) = col[j] {
                        assert_eq!(val, 2.0 * k);
                        k += 1.0;
                    }
                }
            }
        }
    }
}
