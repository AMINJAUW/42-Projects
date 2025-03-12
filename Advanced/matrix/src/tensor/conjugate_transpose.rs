use crate::{Element, ScalarTrait, Tensor};

impl<T: ScalarTrait> Tensor<T> {
    pub fn conjugate_transpose(self) -> Self {
        if self.dim == 1 {
            self.dim1_transpose()
        } else {
            self.higher_dim_transpose()
        }
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
        .conjugate_all()
    }

    fn higher_dim_transpose(self) -> Self {
        let sizes = self.size();

        let mut new_data = Vec::with_capacity(sizes[1]);

        for i in 0..sizes[1] {
            new_data.push(Element::Tensor(Box::new(Tensor {
                data: self
                    .data
                    .clone()
                    .into_iter()
                    .filter_map(|e| {
                        if let Element::Tensor(t) = e {
                            Some(t[i].clone())
                        } else {
                            None
                        }
                    })
                    .collect(),
                dim: self.dim - 1,
            })));
        }
        Tensor {
            data: new_data,
            dim: self.dim,
        }
        .conjugate_all()
    }

    fn conjugate_all(self) -> Self {
        let mut new_data = Vec::with_capacity(self.data.len());

        for i in 0..new_data.len() {
            match &self.data[i] {
                Element::Scalar(scalar) => new_data.push(Element::Scalar(scalar.conjugate())),
                Element::Tensor(tensor) => {
                    new_data.push(Element::Tensor(Box::new(tensor.clone().conjugate_all())))
                }
            }
        }
        self
    }
}
