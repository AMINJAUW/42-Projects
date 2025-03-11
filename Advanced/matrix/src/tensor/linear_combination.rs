use crate::{Tensor, ScalarTrait};

fn same_length_tensors<T:ScalarTrait>(tensors: &[Tensor<T>]) -> bool {
	if tensors.is_empty() {
		return true;
	}

	let first_size = tensors[0].size();
	tensors.iter().all(|tensor| tensor.size() == first_size)
}

pub fn linear_combination<T:ScalarTrait>(u: &[Tensor<T>], coef: &[T]) -> Tensor<T> {
	if u.len() != coef.len() || u.len() == 0 || !same_length_tensors(u) {
		return Tensor::default()
	}
	
	let mut previous = u[0].clone() * coef[0];
	let mut result = Tensor::default();
	for i in 1..u.len() {
		result = u[i].clone().mul_add(coef[i], previous);
		previous = result.clone();
	}
	result
}
