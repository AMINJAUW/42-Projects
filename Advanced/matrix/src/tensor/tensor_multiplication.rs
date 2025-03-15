use std:: ops::Mul;

use crate::ScalarTrait;

use super::{Element, Tensor};

/// l_shape must be at minimum a horizontal vector witch means  
///  be of shape (1, x)  
/// Then we need to chec if the we have a  
/// (a x b) . (b x c) to have a final shape of (a x c)
fn compatible_sizes(l_shape: Vec<usize>, r_shape: Vec<usize>) -> bool {
	if l_shape.len() < 2 || r_shape.is_empty() {
		false
	} else if l_shape[1] != r_shape[0] {
		false
	} else {
		true
	}
}

impl <T:ScalarTrait> Mul for Tensor<T> {
	type Output = Tensor<T>;

	fn mul(self, rhs: Self) -> Self::Output {
		let (l_shape, r_shape) = (self.shape(), rhs.shape());
		if !compatible_sizes(l_shape.clone(), r_shape.clone()) {
			panic!("Incompatible shapes of Tensor multiplication")
		} else {
			let (outer, inner, sum_size) = (l_shape[0], r_shape[1], l_shape[1]);
			
			let mut result_columns = Vec::with_capacity(outer);

			let lhs = self.conjugate_transpose();
			for i in 0..outer {
				let mut new_col = Vec::with_capacity(inner);
				for j in 0..inner {
					let mut sum = T::default();
					let mut tensor_result: Option<Tensor<T>> = None;

					for k in 0..sum_size {
						match (&lhs[i], &rhs[j]) {
							(Element::Scalar(_), Element::Scalar(_)) => {
								if let (Element::Scalar(v), Element::Scalar(u)) = (&lhs[k], &rhs[k]) {
									sum = v.mul_add(*u, sum);
								}
							}
							(Element::Tensor(r_subtensor), Element::Scalar(_)) => {
								if let (Element::Scalar(v), Element::Scalar(u)) = (&r_subtensor[k], &rhs[k]) {
									sum = v.mul_add(*u, sum);
								}
							}
							(Element::Scalar(_), Element::Tensor(l_subtensor)) => {
								if let (Element::Scalar(v), Element::Scalar(u)) = (&lhs[k], &l_subtensor[k]) {
									sum = v.mul_add(*u, sum);
								}
							}
							(Element::Tensor(r_subtensor), Element::Tensor(l_subtensor)) => {
								match (&l_subtensor[k], &r_subtensor[k]) {
									(Element::Scalar(v), Element::Scalar(u)) => {
										sum = v.mul_add(*u, sum);
									}
									(Element::Tensor(r_subsub_tensor), Element::Tensor(l_subsub_tensor)) => {
										let product = *r_subsub_tensor.clone() * *l_subsub_tensor.clone();
										tensor_result = Some(match tensor_result {
											Some(t) => t + product,
											None => product
										})
									}
									_ => unreachable!("Unexpected Tensor Structure"),
								}
							}
						}
					}

					new_col.push(if let Some(tensor) = tensor_result {
						Element::Tensor(Box::new(tensor))
					} else {
						Element::Scalar(sum)
					});
				}
				if inner == 1 {
					result_columns = new_col.clone();
				} else {
					result_columns.push(Element::Tensor(Box::new(Tensor 
						{ 
							data: new_col, 
							dim: lhs.dim -2 
						})));
				}
				
			} 
			Tensor {
				data: result_columns,
				dim: lhs.dim,
			}
		}
	}
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Helper function to generate a vector of `f32` values
    fn generate_f32_sequence(len: usize) -> Vec<f32> {
        (0..len).map(|x| x as f32).collect()
    }

    #[test]
    fn test_scalar_multiplication() {
        let tensor1 = Tensor::new(vec![1], vec![2.0]); // Scalar 2.0
        let tensor2 = Tensor::new(vec![1], vec![3.0]); // Scalar 3.0
        let result = tensor1 * tensor2;

        assert_eq!(result.shape(), vec![1]);
        assert_eq!(result.data, vec![Element::Scalar(6.0)]);
    }

    #[test]
    fn test_1d_tensor_multiplication() {
        let tensor1 = Tensor::new(vec![1, 3], generate_f32_sequence(3)); // [0.0, 1.0, 2.0] as horizontal vector
        let tensor2 = Tensor::new(vec![3], generate_f32_sequence(3)); // [0.0, 1.0, 2.0] as vertical vector

        let result = tensor1 * tensor2;
        
        assert_eq!(result.shape(), vec![1]); // Should be a 1x1 matrix
		assert_eq!(result.data[0], Element::Scalar(5.0))
    }

    #[test]
    fn test_1d_tensor_to_2d_multiplication() {
        let tensor1 = Tensor::new(vec![3], generate_f32_sequence(3)); // [0.0, 1.0, 2.0] as vertical vector
        let tensor2 = Tensor::new(vec![1, 3], generate_f32_sequence(3)); // [0.0, 1.0, 2.0] as horizontal vector

        let result = tensor1 * tensor2;
        
        assert_eq!(result.shape(), vec![3,3]); // Should be a 3x3 matrix
		
		assert_eq!(result, Tensor::new(vec![3,3], vec![0., 0., 0., 0., 1., 2., 0., 2., 4.]))
    }

    // #[test]
    // fn test_2d_matrix_multiplication() {
    //     let tensor1 = Tensor::new(vec![2, 3], generate_f32_sequence(6)); // 2x3 matrix
    //     let tensor2 = Tensor::new(vec![3, 2], generate_f32_sequence(6)); // 3x2 matrix

    //     let result = tensor1 * tensor2;
        
    //     assert_eq!(result.shape(), vec![2, 2]); // Should result in a 2x2 matrix
    // }

    // #[test]
    // fn test_incompatible_shapes() {
    //     let tensor1 = Tensor::new(vec![2, 3], generate_f32_sequence(6)); // 2x3 matrix
    //     let tensor2 = Tensor::new(vec![4, 2], generate_f32_sequence(8)); // 4x2 matrix (incompatible)

    //     let result = std::panic::catch_unwind(|| tensor1 * tensor2);
    //     assert!(result.is_err()); // Should panic due to incompatible shapes
    // }

    // #[test]
    // fn test_higher_dimensional_multiplication() {
    //     let tensor1 = Tensor::new(vec![2, 3, 4], generate_f32_sequence(24)); // 2x3x4 tensor
    //     let tensor2 = Tensor::new(vec![4, 5], generate_f32_sequence(20)); // 4x5 matrix

    //     let result = tensor1 * tensor2;

    //     assert_eq!(result.shape(), vec![2, 3, 5]); // Expected shape after multiplication
    // }
}