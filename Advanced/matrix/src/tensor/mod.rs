use std::ops::{Add, Index, IndexMut, Mul};
use core::fmt;
use crate::ScalarTrait;

#[derive(Debug, Clone)]
pub enum Element<T:ScalarTrait> {
    Scalar(T),
    Tensor(Box<Tensor<T>>)
}

#[derive(Clone)]
pub struct Tensor<T: ScalarTrait> 
{
    pub data: Vec<Element<T>>,
    dim: usize,
}

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

impl<T:ScalarTrait> Default for Tensor<T> {
    fn default() -> Self {
        Tensor { 
            data: vec![Element::Scalar(T::unit())], 
            dim: 1,
        }
    }
}

impl<T:ScalarTrait> Tensor<T> {
    pub fn size(&self) -> Vec<usize> {
        let mut sizes = Vec::with_capacity(self.dim);

        // Get the size of the outer container (either stack or heap)
        sizes.push(self.data.len());
        if self.data.len() == 0 {
            return sizes;
        }
        match &self.data[0] {
            Element::Scalar(_) => sizes,
            Element::Tensor(tensor) => {
                sizes.extend(tensor.size());
                sizes
            }
        }
    }
}

// Implement Add for Tensor (adding two tensors of the same dimension)
impl<T: ScalarTrait> Add for Tensor<T> 
{
    type Output = Tensor<T>;

    fn add(self, rhs: Self) -> Tensor<T> {
        if self.data.len() != rhs.data.len() {
            !panic!("Trying to Add 2 tensors of different sizes");
        }

        let mut result = self.clone(); // Clone the Tensor, not the elements
        for i in 0..self.data.len() {

            match (&self.data[i], &rhs.data[i]) {
                (Element::Scalar(left), Element::Scalar(right)) => { 
                    result[i] = Element::Scalar(*left + *right)
                },
                (Element::Tensor(left), Element::Tensor(right)) => {
                    result[i] = Element::Tensor(Box::new(*left.clone() + *right.clone()))
                },
                _ => {unreachable!()}
            }
        }
        result
    }
}


// Implement Mul for Tensor (multiplying tensor by scalar)
impl<T: ScalarTrait> Mul<T> for Tensor<T> 
{
    type Output = Self;

    fn mul(self, rhs: T) -> Self {
        let mut result = self.clone();
        for i in 0..self.data.len() {
            match &self.data[i] {
                Element::Scalar(left) => { 
                    result[i] = Element::Scalar(*left * rhs)
                },
                Element::Tensor(left) => {
                    result[i] = Element::Tensor(Box::new(*left.clone() * rhs))
                },
            }
        }
        result
    }
}

impl <T:ScalarTrait> Tensor<T> {

    pub fn new(sizes: Vec<usize>, elements : Vec<T>) -> Tensor<T> {
        if sizes.is_empty() {
            panic!("Tensor must have at least one dimension.");
        }

        if sizes.len() == 1 {
            Self::new_dim1(sizes[0], elements)
        } else {
            let sub_tensor_count = sizes[0]; // Number of subtensors at this level
            let remaining_sizes = sizes[1..].to_vec(); // Remaining sizes for subtensors

            let sub_tensor_size: usize = remaining_sizes.clone().iter().product(); // number of Elements in each sub-tensor

            let mut data = Vec::with_capacity(sub_tensor_count);

            for i in 0..sub_tensor_count {
                let start_idx = i * sub_tensor_size;
                let end_idx = (i + 1) * sub_tensor_size;
                let sub_elements = if start_idx > elements.len() {
                        vec![]
                    } else if end_idx > elements.len() {
                        elements[start_idx..].to_vec() // Return all elements from start_idx to the end of the vector
                    } else {
                        elements[start_idx..end_idx].to_vec() // Normal case: Slice the elements from start_idx to end_idx
                    };
                data.push(Element::Tensor(Box::new(Self::new(remaining_sizes.clone(), sub_elements))));
            }
            Tensor {
                data: data,
                dim: sizes.len()
            }
        }
    }

    fn new_dim1(size: usize, elements: Vec<T>) -> Tensor<T> {
        let mut data: Vec<Element<T>> = Vec::with_capacity(size);
    
        for i in 0..size {
            data.push(Element::Scalar(*elements.get(i).unwrap_or(&T::unit())));
        }
        Tensor {
            data: data,
            dim: 1,
        }
    }
}

impl<T: ScalarTrait> fmt::Display for Tensor<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {

        fn print_tensor<T: ScalarTrait>(tensor: &Tensor<T>, indices: &mut Vec<usize>, f: &mut fmt::Formatter<'_>) -> fmt::Result {
            let dims = tensor.size();
            if dims.len() == 1 {
                // 1D Tensor: Print as vertical vector
                for i in 0..tensor.data.len() {
                    if let Element::Scalar(val) = tensor.data[i] {
                            writeln!(f, "{}", val)?;
                    }
                }
            } else if dims.len() == 2 {
                // 2D Tensor: Print as a column-based matrix
                let rows = dims[0];
                let cols = dims[1];
                
                for c in 0..cols {
                    write!(f, "| ")?;
                    for r in 0..rows {
                        if let Element::Tensor(col) = &tensor.data[r] {
                            if let Element::Scalar(val) = col[c] {
                                write!(f, "{:>8} ", val)?;
                            }
                        }
                    }
                    writeln!(f, " |")?;
                }
            } else {
                // 3D+ Tensor: Print multiple matrices with indices
                for i in 0..tensor.data.len() {
                    indices.push(i);
                    writeln!(f, "{:?}\n", indices)?;
                    if let Element::Tensor(sub_tensor) = &tensor[i] {
                        print_tensor(sub_tensor, indices, f)?;
                    }
                    writeln!(f, "{}", "_".repeat(30))?;
                    indices.pop();
                }
            }
            Ok(())
        }

        let mut indices = Vec::new();
        print_tensor(self, &mut indices, f)
    }
}

impl<T: ScalarTrait + fmt::Debug> fmt::Debug for Tensor<T> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Indentation level counter
        fn indent(level: usize) -> String {
            "  ".repeat(level)
        }

        // Helper function to format nested tensors recursively
        fn format_tensor<T: ScalarTrait + fmt::Debug>(tensor: &Tensor<T>, level: usize, f: &mut fmt::Formatter) -> fmt::Result {
            writeln!(f, "{}Tensor {{", indent(level))?;
            writeln!(f, "{}data: [", indent(level + 1))?;

            // Increase indentation for elements inside the data
            for elem in &tensor.data {
                match elem {
                    Element::Tensor(sub_tensor) => {
                        // Format nested tensors recursively
                        format_tensor(sub_tensor, level + 2, f)?;
                    }
                    Element::Scalar(val) => {
                        // Format scalar values with proper indentation
                        writeln!(f, "{}{:?},", indent(level + 2), val)?;
                    }
                }
            }

            writeln!(f, "{}}},", indent(level + 1))?;
            writeln!(f, "{}}},", indent(level))?;
            Ok(())
        }

        // Begin formatting the root tensor
        writeln!(f, "Tensor {{")?;
        format_tensor(self, 1, f)?;
        writeln!(f, "}}")
    }
}



#[cfg(test)]
mod tests {
    use super::*;
    use crate::Complex;

    // Helper function to generate a vector of increasing f32 values
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
    fn test_tensor_creation_f32() {
        let sizes = vec![2, 2]; // 2x2 tensor
        let elements = generate_f32_sequence(4);
        let tensor = Tensor::new(sizes, elements);

        assert_eq!(tensor.size(), vec![2, 2]); // Ensure dimensions match
    }

    #[test]
    fn test_tensor_creation_complex() {
        let sizes = vec![2, 3]; // 2x3 tensor
        let elements = generate_complex_sequence(6);
        let tensor = Tensor::new(sizes, elements);

        assert_eq!(tensor.size(), vec![2, 3]); // Ensure dimensions match
    }

    #[test]
    fn test_indexing_f32() {
        let sizes = vec![2, 2];
        let elements = generate_f32_sequence(4);
        let tensor = Tensor::new(sizes, elements);

        match &tensor[0] {
            Element::Tensor(sub_tensor) => match &sub_tensor[1] {
                Element::Scalar(value) => assert_eq!(*value, 1.0),
                _ => panic!("Unexpected type"),
            },
            _ => panic!("Unexpected type"),
        }
    }

    #[test]
    fn test_indexing_complex() {
        let sizes = vec![2, 2];
        let elements = generate_complex_sequence(4);
        let tensor = Tensor::new(sizes, elements);

        match &tensor[1] {
            Element::Tensor(sub_tensor) => match &sub_tensor[0] {
                Element::Scalar(value) => {
                    assert_eq!(value.re, 2.0);
                    assert_eq!(value.im, 4.0);
                }
                _ => panic!("Unexpected type"),
            },
            _ => panic!("Unexpected type"),
        }
    }

    #[test]
    fn test_addition_f32() {
        let sizes = vec![2, 2];
        let elements = generate_f32_sequence(4);
        let tensor1 = Tensor::new(sizes.clone(), elements.clone());
        let tensor2 = Tensor::new(sizes, elements);

        let result = tensor1.clone() + tensor2;

        match &result[0] {
            Element::Tensor(sub_tensor) => match &sub_tensor[1] {
                Element::Scalar(value) => assert_eq!(*value, 2.0),
                _ => panic!("Unexpected type"),
            },
            _ => panic!("Unexpected type"),
        }
    }

    #[test]
    fn test_addition_complex() {
        let sizes = vec![2, 2];
        let elements = generate_complex_sequence(4);
        let tensor1 = Tensor::new(sizes.clone(), elements.clone());
        let tensor2 = Tensor::new(sizes, elements);

        let result = tensor1.clone() + tensor2;

        match &result[1] {
            Element::Tensor(sub_tensor) => match &sub_tensor[0] {
                Element::Scalar(value) => {
                    assert_eq!(value.re, 4.0);
                    assert_eq!(value.im, 8.0);
                }
                _ => panic!("Unexpected type"),
            },
            _ => panic!("Unexpected type"),
        }
    }

    #[test]
    fn test_multiplication_f32() {
        let sizes = vec![2, 2];
        let elements = generate_f32_sequence(4);
        let tensor = Tensor::new(sizes, elements);

        let result = tensor.clone() * 2.0;

        match &result[0] {
            Element::Tensor(sub_tensor) => match &sub_tensor[1] {
                Element::Scalar(value) => assert_eq!(*value, 2.0),
                _ => panic!("Unexpected type"),
            },
            _ => panic!("Unexpected type"),
        }
    }

    #[test]
    fn test_multiplication_complex() {
        let sizes = vec![2, 2];
        let elements = generate_complex_sequence(4);
        let tensor = Tensor::new(sizes, elements);

        let result = tensor.clone() * Complex { re: 2.0, im: 0.0 };

        match &result[1] {
            Element::Tensor(sub_tensor) => match &sub_tensor[0] {
                Element::Scalar(value) => {
                    assert_eq!(value.re, 4.0);
                    assert_eq!(value.im, 8.0);
                }
                _ => panic!("Unexpected type"),
            },
            _ => panic!("Unexpected type"),
        }
    }
}
