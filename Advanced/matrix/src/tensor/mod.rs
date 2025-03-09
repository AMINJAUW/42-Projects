use std::ops::{Add, Index, IndexMut, Mul};
use crate::Scalar;

pub trait TensorType: Clone + Default + Size {}

impl<T: Scalar> TensorType for T {}
impl<T: TensorType, const N: usize> TensorType for Tensor<T, N> {}


#[derive(Debug, Clone)]
enum Storage<T:TensorType, const N: usize> {
    Stack([T; N]), // Fixed size Stack allocation, optimal but stack overflow risk  
    Heap(Vec<T>), // Stored on the Heap if Needed a lot of space   
} 

impl<T: TensorType + Copy, const N: usize> Copy for Tensor<T, N> where Storage<T, N>: Copy {}

#[derive(Debug, Clone)]
pub struct Tensor<T: TensorType, const N: usize> {
    pub data: Storage<T,N>,
    dim: usize,
}

impl<T: TensorType, const N: usize> Index<usize> for Tensor<T, N> {
    type Output = T;

    fn index(&self, index: usize) -> &Self::Output {
        if index >= N {
            panic!("Out of bounds indexing for a Tensor");
        }
        match &self.data {
            Storage::Stack(data) => &data[index],
            Storage::Heap(data) => &data[index],
        }
    }
}

impl<T: TensorType, const N: usize> IndexMut<usize> for Tensor<T, N> {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        if index >= N {
            panic!("Out of bounds indexing for a Tensor");
        }
        match &mut self.data {
            Storage::Stack(data) => &mut data[index],
            Storage::Heap(data) => &mut data[index],
        }
    }
}

impl<T:TensorType, const N: usize> Default for Tensor<T, N> {
    /// After Carefull consideration it is better to lose some optimisation  
    /// by using the heap because in case of a very big N with high dim the stack could overflow.
    /// And on The Heap we can only use one element per dimension.
    /// the T::default will call the innertype default value
    fn default() -> Self {
        let data = Storage::Heap(vec![T::default()]);
        Tensor { data: data, dim: 0 }
    }
}

pub trait Size {
    fn size(&self) -> Vec<usize>;
}

impl<T: Scalar> Size for T {
    fn size(&self) -> Vec<usize> {
        vec![]  // Scalars have no dimensions
    }
}

impl<T:TensorType, const N: usize> Size for Tensor<T, N> {
    fn size(&self) -> Vec<usize> {
        let mut sizes = vec![];

        // Get the size of the outer container (either stack or heap)
        sizes.push(
            match &self.data {
                Storage::Heap(vec) => vec.len(),
                Storage::Stack(arr) => arr.len(),
            }
        );

        // If the tensor is not scalar (i.e., it has sub-tensors), calculate recursively
        if self.dim > 1 {
            // Here, we assume self[0] is a sub-tensor
            let sub_tensor = &self[0]; // Borrowing the first element (sub-tensor)
            sizes.extend(sub_tensor.size());  // Recursively call size()
        }
        sizes
    }
}

// Implement Add for Tensor (adding two tensors of the same dimension)
impl<T: TensorType + Add<&T, Output = T>, const N: usize> Add<&Tensor<T, N>> for Tensor<T, N> {
    type Output = Tensor<T, N>;

    fn add(self, rhs: &Tensor<T, N>) -> Self::Output {
        if self.size() != rhs.size() {
            panic!("Tensors must have the same dimension and size to be added.");
        }

        let mut result = self;
        for i in 0..N {
            result[i] = self[i] + rhs[i];  // Now we're adding the elements by reference
        }
        result
    }
}


// // Implement Mul for Tensor (multiplying tensor by scalar)
// impl<T: Scalar, const N: usize> Mul<T> for Tensor<T, N> {
//     type Output = Self;

//     fn mul(self, rhs: T) -> Self {
//         let mut result = self;
//         for i in 0..N {
//             result[i] = self[i] * rhs;
//         }
//         result
//     }
// }

// impl <T:TensorType, const N:usize> Tensor<T,N> {
//     /// Creates a `sizes.len()` dimensional tensor.
//     /// - Fills column-first.
//     /// - If `elements` has fewer elements than needed, fills with `Scalar::unit()`.
//     /// - If `elements` has more elements, only the required number is used.
//     pub fn new( sizes: Vec<usize>, elements : Vec<T::Scalar>) -> Tensor<T, N> {
//         let heap_allocation = sizes.len() > 4 || elements.len() > 1000;
//         Self::new_high_dim(sizes, elements, heap_allocation)
//     }

//     fn new_dim1(size: usize, elements : Vec<T::Scalar>, heap_allocation: bool) -> Tensor<T::Scalar, N> {
//         let mut stack_data = [T::Scalar::unit(); size];

//         for i in 0..size {
//             stack_data[i] = elements.get(i).copied().unwrap_or(T::Scalar::unit());
//         }

//         let storage = if heap_allocation {
//             Storage::Heap(stack_data.to_vec())
//         } else {
//             Storage::Stack(stack_data)
//         };

//         Tensor { 
//             data: storage, 
//             dim: 1 
//         }
//     }


//     fn new_high_dim(sizes: Vec<usize>, elements: Vec<T::Scalar>, heap_allocation: bool) -> Tensor<T, N> {
//         if sizes.is_empty() {
//             panic!("Tensor must have at least one dimension.");
//         }
//         if sizes.len() == 1 {
//             return Self::new_dim1(sizes[0], elements, heap_allocation);
//         }

//         let sub_tensor_count = sizes[0]; // Number of subtensors at this level
//         let remaining_sizes = &sizes[1..]; // Remaining sizes for subtensors

//         let sub_tensor_size = remaining_sizes.iter().product(); // Elements in each sub-tensor

//         let data = if heap_allocation {
//             Self::heap_sub_tensors(sub_tensor_count, sub_tensor_size, remaining_sizes, &elements)
//         } else {
//             Self::stack_sub_tensors(sub_tensor_count, sub_tensor_size, remaining_sizes, &elements)
//         };

//         Tensor { 
//             data, 
//             dim: sizes.len(),
//         }
//     }

//     fn heap_sub_tensors(
//         sub_tensor_count: usize,
//         sub_tensor_size: usize,
//         remaining_sizes: &[usize],
//         elements: &[T::Scalar],
//     ) -> Storage<T, N> {

//         let mut heap_data = Vec::with_capacity(sub_tensor_count);

//         for i in 0..sub_tensor_count {
//             let start_idx = i * sub_tensor_size;
//             let end_idx = (i + 1) * sub_tensor_size;
//             let sub_elements = if end_idx > elements.len() {
//                 elements[start_idx..].to_vec() // Return all elements from start_idx to the end of the vector
//             } else {
//                 elements[start_idx..end_idx].to_vec() // Normal case: Slice the elements from start_idx to end_idx
//             };
//             heap_data.push(Self::new_high_dim(remaining_sizes.to_vec(), sub_elements, true));
//         }
//         Storage::Heap(heap_data)
//     }

//     fn stack_sub_tensors(
//         sub_tensor_count: usize,
//         sub_tensor_size: usize,
//         remaining_sizes: &[usize],
//         elements: &[T::Scalar],
//     ) -> Storage<T, N> {

//         let mut stack_data = [Self::default(); sub_tensor_count];

//         for i in 0..sub_tensor_count.min(N) {
//             let start_idx = i * sub_tensor_size;
//             let end_idx = (i + 1) * sub_tensor_size;
//             let sub_elements = elements.get(start_idx..end_idx).unwrap_or(&[]).to_vec();
//             stack_data[i] = Self::new_high_dim(remaining_sizes.to_vec(), sub_elements, false);
//         }
//         Storage::Stack(stack_data)
//     }
		
// }


// #[cfg(test)]
// mod tests {
//     use super::*;
//     use crate::Complex;


//     // A helper function to create a tensor of f32
//     fn create_tensor_f32(data: [f32; 3], dim: usize) -> Tensor<f32, 3> {
//         Tensor { data, dim }
//     }

//     // A helper function to create a tensor of Complex
//     fn create_tensor_complex(data: [Complex; 3], dim: usize) -> Tensor<Complex, 3> {
//         Tensor { data, dim }
//     }

//     #[test]
//     fn test_add_tensors_f32() {
//         let tensor1 = create_tensor_f32([1.0, 2.0, 3.0], 1);
//         let tensor2 = create_tensor_f32([4.0, 5.0, 6.0], 1);
        
//         // Adding two tensors
//         let result = tensor1 + tensor2;
        
//         assert_eq!(result.data, [5.0, 7.0, 9.0]);
//     }

//     #[test]
//     #[should_panic(expected = "Tensors must have the same dimension and size to be added.")]
//     fn test_add_tensors_f32_mismatched_dims() {
//         let tensor1 = create_tensor_f32([1.0, 2.0, 3.0], 1);
//         let tensor2 = create_tensor_f32([1.0, 2.0, 3.0], 2);
        
//         // This will panic because the dimensions don't match
//         let _ = tensor1 + tensor2;
//     }

//     #[test]
//     fn test_mul_tensor_by_scalar_f32() {
//         let tensor = create_tensor_f32([1.0, 2.0, 3.0], 1);
//         let scalar = 2.0;
        
//         // Multiplying tensor by scalar
//         let result = tensor * scalar;
        
//         assert_eq!(result.data, [2.0, 4.0, 6.0]);
//     }

//     #[test]
//     fn test_add_tensors_complex() {
//         let tensor1 = create_tensor_complex(
//             [Complex { re: 1.0, im: 1.0 }, Complex { re: 2.0, im: 2.0 }, Complex { re: 3.0, im: 3.0 }],
//             1,
//         );
//         let tensor2 = create_tensor_complex(
//             [Complex { re: 4.0, im: 4.0 }, Complex { re: 5.0, im: 5.0 }, Complex { re: 6.0, im: 6.0 }],
//             1,
//         );
        
//         // Adding two tensors of Complex numbers
//         let result = tensor1 + tensor2;
        
//         assert_eq!(
//             result.data,
//             [
//                 Complex { re: 5.0, im: 5.0 },
//                 Complex { re: 7.0, im: 7.0 },
//                 Complex { re: 9.0, im: 9.0 }
//             ]
//         );
//     }

//     #[test]
//     fn test_mul_tensor_by_scalar_complex() {
//         let tensor = create_tensor_complex(
//             [Complex { re: 1.0, im: 1.0 }, Complex { re: 2.0, im: 2.0 }, Complex { re: 3.0, im: 3.0 }],
//             1,
//         );
//         let scalar = Complex { re: 2.0, im: 2.0 };
        
//         // Multiplying tensor by a scalar (Complex number)
//         let result = tensor * scalar;
        
//         assert_eq!(
//             result.data,
//             [
//                 Complex { re: 0.0, im: 4.0 },
//                 Complex { re: 0.0, im: 8.0 },
//                 Complex { re: 0.0, im: 12.0 }
//             ]
//         );
//     }

// }

