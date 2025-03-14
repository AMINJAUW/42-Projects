use std::ops::Mul;

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
			let (outer, inner, sum_size) = 
			(*l_shape.get(0).unwrap(), *r_shape.get(1).unwrap(), *l_shape.get(1).unwrap());
			
			let mut new_columns = Vec::with_capacity(outer);
			let dim = self.dim;

			let lhs = self.conjugate_transpose();
			for i in 0..outer {
				let mut new_col = Vec::with_capacity(inner);
				for j in 0..inner {
					match &lhs.data[i] {
						Element::Scalar(_) => {
							match &rhs.data[j] {
								Element::Scalar(_) => {
									let mut result = T::default();
									for k in 0..sum_size {
										if let (Element::Scalar(v), Element::Scalar(u)) = (lhs[k].clone(), rhs[k].clone()) {
											let temp = v.mul_add(u, result);
											result = temp;
										} else {
											unreachable!("Have Checked before that the 2 tensor to multiply are made of scalars")
										}
									}
									new_col.push(Element::Scalar(result));
								}
								Element::Tensor(sub_tensor) => {
									let mut result = T::default();
									for k in 0..sum_size {
										if let (Element::Scalar(v), Element::Scalar(u)) = (lhs[k].clone(), sub_tensor[k].clone()) {
											let temp = v.mul_add(u, result);
											result = temp;
										} else {
											unreachable!("The right side is a Scalar tensor to be a valid multiplication the left should be a tensor of tensor of scalars")
										}
									}
									new_col.push(Element::Scalar(result));
								}
							}
						}
						Element::Tensor(l_subtensor) => {
							match &rhs.data[j] {
								Element::Scalar(_) => {
									let mut result = T::default();
									for k in 0..sum_size {
										if let (Element::Scalar(v), Element::Scalar(u)) = (l_subtensor[k].clone(), rhs[k].clone()) {
											let temp = v.mul_add(u, result);
											result = temp;
										} else {
											unreachable!("The left side is a Scalar tensor to be a valid multiplication the right should be a tensor of tensor of scalars")
										}
									}
									new_col.push(Element::Scalar(result));									
								}
								Element::Tensor(r_subtensor) => {
									let mut scalar_result = T::default();
									let mut tensor_result = if let (Element::Tensor(u),Element::Tensor(v)) = (&l_subtensor[0], &r_subtensor[0]) {
										Some(*u.clone() * *v.clone())
									} else {
										None
									};
									for k in 0..sum_size {
										match (&l_subtensor[k], &r_subtensor[k]) {
											(Element::Scalar(v),Element::Scalar(u)) => {
												let temp = v.mul_add(*u, scalar_result);
												if k == sum_size - 1 {
													new_col.push(Element::Scalar(temp));
												} else {
													scalar_result = temp;
												}
											}
											(Element::Tensor(v),Element::Tensor(u)) => {
												if k == 0 {
													continue;
												}
												tensor_result = Some(tensor_result.unwrap() + (*v.clone() * *u.clone()));
												if k == sum_size - 1 {
													new_col.push(Element::Tensor(Box::new(tensor_result.clone().unwrap())));
												}
											}
											_ => {
												unreachable!("The left side is a Scalar tensor to be a valid multiplication the right should be a tensor of tensor of scalars")
											}
										}	
									}
								
								}
							}
						}
					} 
				if inner == 1 {
					new_columns = new_col.clone();
				} else {
					new_columns.push(
						Element::Tensor(Box::new(Tensor { data: new_col.clone(), dim: dim - 2 }))
					);
				}
			} 
			
			}
			Tensor {
				data: new_columns,
				dim: dim,
			}
		}
	}
}