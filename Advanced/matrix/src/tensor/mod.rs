use std::ops::{Add, Mul};
use crate::Scalar;
use crate::Complex;

pub trait TensorType: Copy + Clone {}

impl<T: Scalar> TensorType for T {}
impl<T: TensorType, const N: usize> TensorType for Tensor<T, N> {}

#[derive(Debug, Clone, Copy)]
pub struct Tensor<T: TensorType, const N: usize> {
    pub data: [T; N],
    dim: usize,
}

// Implement Add for Tensor (adding two tensors of the same dimension)
impl<T: TensorType + Add<Output = T>, const N: usize> Add for Tensor<T, N> {
    type Output = Self;

    fn add(self, rhs: Self) -> Self {
        if self.dim != rhs.dim || N != rhs.data.len() {
            panic!("Tensors must have the same dimension and size to be added.");
        }

        let mut result = self;
        for i in 0..N {
            result.data[i] = self.data[i] + rhs.data[i];
        }
        result
    }
}

// Implement Mul for Tensor (multiplying tensor by scalar)
impl<T: Scalar, const N: usize> Mul<T> for Tensor<T, N> {
    type Output = Self;

    fn mul(self, rhs: T) -> Self {
        let mut result = self;
        for i in 0..N {
            result.data[i] = self.data[i] * rhs;
        }
        result
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    // A helper function to create a tensor of f32
    fn create_tensor_f32(data: [f32; 3], dim: usize) -> Tensor<f32, 3> {
        Tensor { data, dim }
    }

    // A helper function to create a tensor of Complex
    fn create_tensor_complex(data: [Complex; 3], dim: usize) -> Tensor<Complex, 3> {
        Tensor { data, dim }
    }

    #[test]
    fn test_add_tensors_f32() {
        let tensor1 = create_tensor_f32([1.0, 2.0, 3.0], 1);
        let tensor2 = create_tensor_f32([4.0, 5.0, 6.0], 1);
        
        // Adding two tensors
        let result = tensor1 + tensor2;
        
        assert_eq!(result.data, [5.0, 7.0, 9.0]);
    }

    #[test]
    #[should_panic(expected = "Tensors must have the same dimension and size to be added.")]
    fn test_add_tensors_f32_mismatched_dims() {
        let tensor1 = create_tensor_f32([1.0, 2.0, 3.0], 1);
        let tensor2 = create_tensor_f32([1.0, 2.0, 3.0], 2);
        
        // This will panic because the dimensions don't match
        let _ = tensor1 + tensor2;
    }

    #[test]
    fn test_mul_tensor_by_scalar_f32() {
        let tensor = create_tensor_f32([1.0, 2.0, 3.0], 1);
        let scalar = 2.0;
        
        // Multiplying tensor by scalar
        let result = tensor * scalar;
        
        assert_eq!(result.data, [2.0, 4.0, 6.0]);
    }

    #[test]
    fn test_add_tensors_complex() {
        let tensor1 = create_tensor_complex(
            [Complex { re: 1.0, im: 1.0 }, Complex { re: 2.0, im: 2.0 }, Complex { re: 3.0, im: 3.0 }],
            1,
        );
        let tensor2 = create_tensor_complex(
            [Complex { re: 4.0, im: 4.0 }, Complex { re: 5.0, im: 5.0 }, Complex { re: 6.0, im: 6.0 }],
            1,
        );
        
        // Adding two tensors of Complex numbers
        let result = tensor1 + tensor2;
        
        assert_eq!(
            result.data,
            [
                Complex { re: 5.0, im: 5.0 },
                Complex { re: 7.0, im: 7.0 },
                Complex { re: 9.0, im: 9.0 }
            ]
        );
    }

    #[test]
    fn test_mul_tensor_by_scalar_complex() {
        let tensor = create_tensor_complex(
            [Complex { re: 1.0, im: 1.0 }, Complex { re: 2.0, im: 2.0 }, Complex { re: 3.0, im: 3.0 }],
            1,
        );
        let scalar = Complex { re: 2.0, im: 2.0 };
        
        // Multiplying tensor by a scalar (Complex number)
        let result = tensor * scalar;
        
        assert_eq!(
            result.data,
            [
                Complex { re: 0.0, im: 4.0 },
                Complex { re: 0.0, im: 8.0 },
                Complex { re: 0.0, im: 12.0 }
            ]
        );
    }

	fn tensor_creator< const MAX_DIM: usize, const N: usize>(
		dim: usize, 
		sizes: [usize; MAX_DIM], 
		start_value: usize
	) -> Tensor<f32, N> {
		if dim == 1 {
			// Base case: We create the final tensor with the values starting from `start_value`
			let mut data = [f32::default(); N];
			let mut value = start_value;
	
			for i in 0..N {
				data[i] = f32::default(); // Placeholder logic, modify as needed
				value += 1;
			}
	
			Tensor {
				data,
				dim: 1,
			}
		} else {
			// Recursive case: Create a tensor of tensors with lower dimension
			let mut data = [f32::default(); N];
			let mut value = start_value;
	
			for i in 0..N {
				let sub_tensor = tensor_creator::<f32, MAX_DIM, N>(dim - 1, sizes, value);
				data[i] = sub_tensor.data[0];  // Just placing one element in the current data
			}
	
			Tensor {
				data,
				dim,
			}
		}
	}

}