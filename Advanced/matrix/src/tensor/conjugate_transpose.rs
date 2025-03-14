use crate::{Element, ScalarTrait, Tensor};

impl<T: ScalarTrait> Tensor<T> {
    pub fn conjugate_transpose(self) -> Self {
		if self.dim == 1 {
            self.dim1_transpose()
        } else {
            self.higher_dim_transpose()
        }.conjugate_all()
    }

    fn dim1_transpose(self) -> Self {
        let mut new_data: Vec<Element<T>> = Vec::with_capacity(self.data.len());

        for i in 0..self.data.len() {
            new_data.push(Element::Tensor(Box::new(Tensor {
                data: vec![self.data[i].clone()],
                dim: 1,
            })));
        }
        Tensor {
            data: new_data,
            dim: 2,
        }
    }

    fn higher_dim_transpose(self) -> Self {
        let shape = self.shape();
		let (outer, inner) = (shape[0], shape[1]);
        let mut new_data = Vec::with_capacity(inner);

		for j in 0..inner {
			let mut new_inner_data = Vec::with_capacity(outer);
			for i in 0..outer {
				if let Element::Tensor(ith_sub_tensor) = &self.data[i] {
					new_inner_data.push(
						ith_sub_tensor[j].clone()
					);
				}
			}
			new_data.push(
				Element::Tensor(Box::new(
					Tensor { 
						data: new_inner_data,
						dim: self.dim - 1,
					})));
		}
        Tensor {
            data: new_data,
            dim: self.dim,
        }
    }

    fn conjugate_all(self) -> Self {
        let mut new_data = Vec::with_capacity(self.data.len());

        for i in 0..self.data.len() {
            match &self.data[i] {
                Element::Scalar(scalar) => new_data.push(Element::Scalar(scalar.conjugate())),
                Element::Tensor(tensor) => {
                    new_data.push(Element::Tensor(Box::new(tensor.clone().conjugate_all())))
                }
            }
        }
        Tensor { data: new_data, dim: self.dim }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
	use crate::Complex;

    #[test]
    fn test_transpose_f32_1d() {
        let tensor = Tensor::new(vec![2], vec![1.0, 2.0]);
        let transposed = tensor.conjugate_transpose();
        let expected = Tensor::new(vec![2, 1], vec![1.0, 2.0]);

        assert_eq!(transposed, expected);
    }

    #[test]
    fn test_transpose_f32_2d() {
        let tensor = Tensor::new(vec![2, 2], vec![1.0, 2.0, 3.0, 4.0]);
        let transposed = tensor.conjugate_transpose();
        let expected = Tensor::new(vec![2, 2], vec![1.0, 3.0, 2.0, 4.0]);

        assert_eq!(transposed, expected);
    }

    #[test]
    fn test_transpose_complex_1d() {
        let tensor = Tensor::new(
            vec![2],
            vec![
                Complex { re: 1.0, im: 1.0 },
                Complex { re: 2.0, im: -3.0 },
            ],
        );
        let transposed = tensor.conjugate_transpose();
        let expected = Tensor::new(
            vec![2, 1],
            vec![
                Complex { re: 1.0, im: -1.0 },
                Complex { re: 2.0, im: 3.0 },
            ],
        );

        assert_eq!(transposed, expected);
    }

    #[test]
    fn test_transpose_complex_2d() {
        let tensor = Tensor::new(
            vec![2, 2],
            vec![
                Complex { re: 1.0, im: 1.0 },
                Complex { re: 2.0, im: -2.0 },
                Complex { re: 3.0, im: 3.0 },
                Complex { re: 4.0, im: -4.0 },
            ],
        );
        let transposed = tensor.conjugate_transpose();
        let expected = Tensor::new(
            vec![2, 2],
            vec![
                Complex { re: 1.0, im: -1.0 },
                Complex { re: 3.0, im: -3.0 },
                Complex { re: 2.0, im: 2.0 },
                Complex { re: 4.0, im: 4.0 },
            ],
        );

        assert_eq!(transposed, expected);
    }

    #[test]
    fn test_transpose_f32_3d() {
        let tensor = Tensor::new(
            vec![2, 2, 2],
            vec![
                1.0, 2.0,
                3.0, 4.0,
                5.0, 6.0,
                7.0, 8.0
            ],
        );
        let transposed = tensor.conjugate_transpose();
        let expected = Tensor::new(
            vec![2, 2, 2],
            vec![
                1.0, 2.0,
                5.0, 6.0,
                3.0, 4.0,
                7.0, 8.0
            ],
        );

        assert_eq!(transposed, expected);
    }

    #[test]
    fn test_transpose_complex_3d() {
        let tensor = Tensor::new(
            vec![2, 2, 2],
            vec![
                Complex { re: 1.0, im: 1.0 }, Complex { re: 2.0, im: -2.0 },
                Complex { re: 3.0, im: 3.0 }, Complex { re: 4.0, im: -4.0 },
                Complex { re: 5.0, im: 5.0 }, Complex { re: 6.0, im: -6.0 },
                Complex { re: 7.0, im: 7.0 }, Complex { re: 8.0, im: -8.0 }
            ],
        );
        let transposed = tensor.conjugate_transpose();
        let expected = Tensor::new(
            vec![2, 2, 2],
            vec![
                Complex { re: 1.0, im: -1.0 }, Complex { re: 2.0, im: 2.0 },
                Complex { re: 5.0, im: -5.0 }, Complex { re: 6.0, im: 6.0 },
                Complex { re: 3.0, im: -3.0 }, Complex { re: 4.0, im: 4.0 },
                Complex { re: 7.0, im: -7.0 }, Complex { re: 8.0, im: 8.0 }
            ],
        );

        assert_eq!(transposed, expected);
    }
}
