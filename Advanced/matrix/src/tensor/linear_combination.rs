use crate::{ScalarTrait, Tensor};

fn same_length_tensors<T: ScalarTrait>(tensors: &[Tensor<T>]) -> bool {
    if tensors.is_empty() {
        return true;
    }

    let first_size = tensors[0].shape();
    tensors.iter().all(|tensor| tensor.shape() == first_size)
}

///
/// The time Complexity here is of O(n) because there is only one operation,
/// the mul_Add, done per Scalar
///
/// The Space Complexity is also relative to O(n + 1) witch tends to O(n).
/// Because we are Making Pure Functions,
/// I.E. they do not modify their inputs. So we only allocate the size of the final tensor
/// the clone replace other stuff of the same size and rust free is dynamicly
pub fn linear_combination<T: ScalarTrait>(u: &[Tensor<T>], coef: &[T]) -> Tensor<T> {
    if u.len() != coef.len() || u.len() == 0 || !same_length_tensors(u) {
        return Tensor::default();
    }

    let mut previous = u[0].clone() * coef[0];
    let mut result = Tensor::default();
    for i in 1..u.len() {
        result = u[i].clone().mul_add_scalar(coef[i], previous);
        previous = result.clone();
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_linear_combination_valid() {
        let t1 = Tensor::new(vec![2, 2, 2], vec![1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0]);
        let t2 = Tensor::new(vec![2, 2, 2], vec![0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0]);
        let t3 = Tensor::new(
            vec![2, 2, 2],
            vec![-1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0],
        );

        let tensors = vec![t1.clone(), t2.clone(), t3.clone()];
        let coefs = vec![1.0, 2.0, -1.0];

        let expected = Tensor::new(
            vec![2, 2, 2],
            vec![
                (1.0 * 1.0) + (0.5 * 2.0) + (-1.0 * -1.0),
                (2.0 * 1.0) + (1.0 * 2.0) + (-2.0 * -1.0),
                (3.0 * 1.0) + (1.5 * 2.0) + (-3.0 * -1.0),
                (4.0 * 1.0) + (2.0 * 2.0) + (-4.0 * -1.0),
                (5.0 * 1.0) + (2.5 * 2.0) + (-5.0 * -1.0),
                (6.0 * 1.0) + (3.0 * 2.0) + (-6.0 * -1.0),
                (7.0 * 1.0) + (3.5 * 2.0) + (-7.0 * -1.0),
                (8.0 * 1.0) + (4.0 * 2.0) + (-8.0 * -1.0),
            ],
        );

        let result = linear_combination(&tensors, &coefs);
        assert_eq!(result, expected);
    }

    #[test]
    fn test_linear_combination_empty_inputs() {
        let tensors: Vec<Tensor<f32>> = vec![];
        let coefs: Vec<f32> = vec![];

        let result = linear_combination(&tensors, &coefs);
        assert_eq!(result, Tensor::default());
    }

    #[test]
    fn test_linear_combination_mismatched_shape() {
        let t1 = Tensor::new(vec![2, 2, 2], vec![1.0; 8]);
        let t2 = Tensor::new(vec![2, 2, 2], vec![2.0; 8]);

        let tensors = vec![t1, t2];
        let coefs = vec![1.0]; // Mismatched length

        let result = linear_combination(&tensors, &coefs);
        assert_eq!(result, Tensor::default());
    }

    #[test]
    fn test_linear_combination_different_shapes() {
        let t1 = Tensor::new(vec![2, 2, 2], vec![1.0; 8]);
        let t2 = Tensor::new(vec![2, 3, 2], vec![2.0; 12]); // Different shape

        let tensors = vec![t1, t2];
        let coefs = vec![1.0, 2.0];

        let result = linear_combination(&tensors, &coefs);
        assert_eq!(result, Tensor::default());
    }
}
