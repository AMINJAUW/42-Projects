use crate::{ScalarTrait, Tensor, Element};
use std::ops::{Index, IndexMut};

impl<T: ScalarTrait> Index<usize> for Tensor<T> {
    type Output = Element<T>;

    fn index(&self, index: usize) -> &Self::Output {
        &self.data[index]
    }
}

impl<T: ScalarTrait> IndexMut<usize> for Tensor<T> {

    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        &mut self.data[index]
    }
}