pub mod basic;

use std::ops::Deref;

use crate::{tensor::Element, ScalarTrait, Tensor};

#[derive(Clone)]
pub struct Vector<T:ScalarTrait>(pub Tensor<T>);

impl<T: ScalarTrait> Vector<T> {
    pub fn new(elements: Vec<T>) -> Self {
        Vector(Tensor {
            data: elements.into_iter().map(Element::Scalar).collect(),
            dim: 1,
        })
    }
}

impl <T: ScalarTrait> Deref for Vector<T> {
    type Target = Tensor<T>;
    
    ///Magic Happens here,  
    ///The Deref permit the Compiler to treat the Vector as Tensor   
    /// and inherit all his member functions  
    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::Complex;

    fn generate_f32_sequence(len: usize) -> Vec<f32> {
        (0..len).map(|x| x as f32).collect()
    }
    
    // Helper function to generate a vector of increasing Complex numbers
    fn generate_complex_sequence(len: usize) -> Vec<Complex> {
        (0..len)
            .map(|x| Complex { re: x as f32, im: (x as f32) * 2.0 })
            .collect()
    }

    #[test]
    fn test_vector_creation_f32() {
        let elements = generate_f32_sequence(5);
        let vector = Vector::new(elements.clone());
        
        assert_eq!(vector.size(), vec![5]);
        
        for i in 0..5 {
            match &vector[i] {
                Element::Scalar(val) => assert_eq!(*val, elements[i]),
                _ => panic!("Expected Element::Scalar"),
            }
        }
    }

    #[test]
    fn test_vector_creation_complex() {
        let elements = generate_complex_sequence(3);
        let vector = Vector::new(elements.clone());
        
        assert_eq!(vector.size(), vec![3]);
        
        for i in 0..3 {
            match &vector[i] {
                Element::Scalar(val) => assert_eq!(*val, elements[i]),
                _ => panic!("Expected Element::Scalar"),
            }
        }
    }

    #[test]
    fn test_vector_addition() {
        let v1 = Vector::new(generate_f32_sequence(3));
        let v2 = Vector::new(generate_f32_sequence(3));
        let result = v1.clone() + v2.clone();
        
        for i in 0..3 {
            match &result[i] {
                Element::Scalar(val) => assert_eq!(*val, (i as f32) * 2.0),
                _ => panic!("Expected Element::Scalar"),
            }
        }
    }

    #[test]
    fn test_vector_scalar_multiplication() {
        let vector = Vector::new(generate_f32_sequence(4));
        let result = vector.clone() * 2.0;
        
        for i in 0..4 {
            match &result[i] {
                Element::Scalar(val) => assert_eq!(*val, (i as f32) * 2.0),
                _ => panic!("Expected Element::Scalar"),
            }
        }
    }
}
