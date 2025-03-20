use std::{cmp::max,  ops::Mul};

use crate::ScalarTrait;

use super::{Element, Tensor};

fn compatible_sizes(l_shape: Vec<usize>, r_shape: Vec<usize>) -> bool {
    if l_shape.len() < 2 || r_shape.len() < 2 {
		false // Should not happen the tensors have been converted before
	} else if l_shape.len() != r_shape.len() {
		false // Tensors have not the same dim
	} else if l_shape[1] != r_shape[1] {
		false // like when mutlipying matrices of shape a x b the other should have b x c
	} else {
		true
	}
}

fn encapsulate_in_tensor<T:ScalarTrait>(tensor: Tensor<T>) -> Tensor<T> {
	Tensor {
		dim: tensor.dim + 1, 
		data: vec![Element::Tensor(Box::new(tensor))], 
	}
}

fn set_tensors_to_same_dim<T:ScalarTrait>(mut u: Tensor<T>,mut v: Tensor<T>) -> (Tensor<T>, Tensor<T>) {
	let max_dim = max(u.dim, v.dim);
	while u.dim != max_dim || u.dim == 1 {
		u = encapsulate_in_tensor(u)
	}
	while v.dim != max_dim || v.dim == 1 {
		v = encapsulate_in_tensor(v)
	}
	(u, v)
}

impl <T:ScalarTrait> Tensor<T> {
	/// This method will extarct tensor that have only 1 len in the upper dimensions
	/// So that a 2d tensors with only one colum will become a 1d tensor of 1 column
	pub fn simplify(mut self) -> Self {
        while self.data.len() == 1 {
            // Take out the first element
            let first_element = self.data.swap_remove(0);

            match first_element {
                Element::Scalar(_) => {
                    self.data.push(first_element); // Put it back to preserve self
                    break;
                }
                Element::Tensor(tensor) => {
                    self = *tensor; // Move the inner tensor out
                }
            }
        }
        self
    }
}

impl <T:ScalarTrait> Mul for Tensor<T> {
	type Output = Tensor<T>;

	fn mul(self, rhs: Self) -> Self::Output {
		let (left_tensor, right_tensor) = set_tensors_to_same_dim(self.conjugate_transpose(), rhs);

		let (l_shape, r_shape) = (left_tensor.shape(), right_tensor.shape());
		if !compatible_sizes(l_shape.clone(), r_shape.clone()) {
			panic!("Incompatible shapes of Tensor multiplication")
		} else {
			let (column_len, line_len) = (l_shape[0], r_shape[0]);
			let sum_len = l_shape[1];
			let mut new_tensor_data = Vec::with_capacity(line_len);
			for col in 0..line_len {
				let mut new_col = Vec::with_capacity(column_len);
				for elem in 0..column_len {
					if let (Element::Tensor(l_sub_tensor), Element::Tensor(r_subtensor)) = (left_tensor[col], right_tensor[col]) {
						let mut sum = T::default();
						let mut tensor_sum: Option<Tensor<T>> = None;

						for i in 0..sum_len {
							match (&l_sub_tensor[i], &r_subtensor[i]) {
								(Element::Scalar(left), Element::Scalar(right)) => {
									sum = left.mul_add(*right, sum); // Essentially doing sum += left * right
								}
								(Element::Tensor(left), Element::Tensor(right)) => {
									tensor_sum = Some( match tensor_sum {
										Some(t) => left.clone().mul_add_tensor(*right.clone(), t),
										None => *left.clone() * *right.clone(), 
									});
								}
								_ => unreachable!("Tensor mutliplacation have differents dimentions adn it passed the check for it")
							}
						}
						new_col.push( if let Some(tensor) = tensor_sum {
							Element::Tensor(Box::new(tensor))
						} else {
							Element::Scalar(sum)
						});
					} else {
						unreachable!("Trying to multiply tensor how aren't an array of tensors, even after changing them to be")
					}
				}


				new_tensor_data.push(
					Element::Tensor(Box::new(Tensor { 
						data: new_col, 
						dim: l_shape.len() - 1 
					})));
			}
			Tensor {
				data: new_tensor_data,
				dim: l_shape.len()
			}.simplify()
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
        let tensor1 = Tensor::new(vec![1,1], vec![2.0]); // Scalar 2.0
        let tensor2 = Tensor::new(vec![1], vec![3.0]); // Scalar 3.0
        let result = tensor1 * tensor2;

        assert_eq!(result.shape(), vec![1]);
        assert_eq!(result.data, vec![Element::Scalar(6.0)]);
    }

    #[test]
    fn test_1d_tensor_multiplication() {
        let tensor1 = Tensor::new(vec![3, 1], generate_f32_sequence(3)); // [0.0, 1.0, 2.0] as horizontal vector
        let tensor2 = Tensor::new(vec![3], generate_f32_sequence(3)); // [0.0, 1.0, 2.0] as vertical vector

        let result = tensor1 * tensor2;
        
        assert_eq!(result.shape(), vec![1]); // Should be a 1x1 matrix
		assert_eq!(result.data[0], Element::Scalar(5.0))
    }

    #[test]
    fn test_1d_tensor_to_2d_multiplication() {
        let tensor1 = Tensor::new(vec![3, 1], generate_f32_sequence(3)); // [0.0, 1.0, 2.0] as vertical vector
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