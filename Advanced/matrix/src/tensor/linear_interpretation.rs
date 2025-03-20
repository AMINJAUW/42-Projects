use crate::ScalarTrait;

use super::Tensor;

/// Because The subject says that t ∈ ℝ and not 𝕂 we need to set t as a 32
/// The time complexity here is O(2n) wich means linear so O(n)
/// For the Space Complexity we Are making a new tensor of space n so O(N)
///
/// The formula accept t to be outside [0;1] as stated in the yellow note at the end
pub fn lerp<T: ScalarTrait>(u: Tensor<T>, v: Tensor<T>, t: f32) -> Tensor<T> {
    return (v - u.clone()).mul_add_scalar(T::fromf32(t), u);
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{Complex, Tensor};

    #[test]
    fn test_lerp_f32_vector() {
        let u = Tensor::new(vec![2], vec![1.0f32, 2.0f32]);
        let v = Tensor::new(vec![2], vec![3.0f32, 4.0f32]);

        let t = 0.5;
        let result = lerp(u.clone(), v.clone(), t);
        let expected = Tensor::new(vec![2], vec![2.0f32, 3.0f32]);

        assert_eq!(result, expected);
    }

    #[test]
    fn test_lerp_complex_vector() {
        let u = Tensor::new(
            vec![2],
            vec![Complex { re: 1.0, im: 1.0 }, Complex { re: 2.0, im: 2.0 }],
        );
        let v = Tensor::new(
            vec![2],
            vec![Complex { re: 3.0, im: 3.0 }, Complex { re: 4.0, im: 4.0 }],
        );

        let t = 0.5;
        let result = lerp(u.clone(), v.clone(), t);
        let expected = Tensor::new(
            vec![2],
            vec![Complex { re: 2.0, im: 2.0 }, Complex { re: 3.0, im: 3.0 }],
        );

        assert_eq!(result, expected);
    }

    #[test]
    fn test_lerp_f32_matrix() {
        let u = Tensor::new(
            vec![2, 3],
            vec![1.0f32, 2.0f32, 3.0f32, 4.0f32, 5.0f32, 6.0f32],
        );
        let v = Tensor::new(
            vec![2, 3],
            vec![7.0f32, 8.0f32, 9.0f32, 10.0f32, 11.0f32, 12.0f32],
        );

        let t = 0.5;
        let result = lerp(u.clone(), v.clone(), t);
        let expected = Tensor::new(
            vec![2, 3],
            vec![4.0f32, 5.0f32, 6.0f32, 7.0f32, 8.0f32, 9.0f32],
        );

        assert_eq!(result, expected);
    }

    #[test]
    fn test_lerp_complex_matrix() {
        let u = Tensor::new(
            vec![2, 3],
            vec![
                Complex { re: 1.0, im: 1.0 },
                Complex { re: 2.0, im: 2.0 },
                Complex { re: 3.0, im: 3.0 },
                Complex { re: 4.0, im: 4.0 },
                Complex { re: 5.0, im: 5.0 },
                Complex { re: 6.0, im: 6.0 },
            ],
        );
        let v = Tensor::new(
            vec![2, 3],
            vec![
                Complex { re: 7.0, im: 7.0 },
                Complex { re: 8.0, im: 8.0 },
                Complex { re: 9.0, im: 9.0 },
                Complex { re: 10.0, im: 10.0 },
                Complex { re: 11.0, im: 11.0 },
                Complex { re: 12.0, im: 12.0 },
            ],
        );

        let t = 0.5;
        let result = lerp(u.clone(), v.clone(), t);
        let expected = Tensor::new(
            vec![2, 3],
            vec![
                Complex { re: 4.0, im: 4.0 },
                Complex { re: 5.0, im: 5.0 },
                Complex { re: 6.0, im: 6.0 },
                Complex { re: 7.0, im: 7.0 },
                Complex { re: 8.0, im: 8.0 },
                Complex { re: 9.0, im: 9.0 },
            ],
        );

        assert_eq!(result, expected);
    }

    #[test]
    fn test_lerp_extremes() {
        let u = Tensor::new(vec![2, 3], vec![1.0f32, 2.0, 3.0, 4.0, 5.0, 6.0]);
        let v = Tensor::new(vec![2, 3], vec![7.0f32, 8.0, 9.0, 10.0, 11.0, 12.0]);

        let result_t0 = lerp(u.clone(), v.clone(), 0.0);
        let result_t1 = lerp(u.clone(), v.clone(), 1.0);

        assert_eq!(result_t0, u);
        assert_eq!(result_t1, v);
    }
}
