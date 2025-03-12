use crate::{Element, ScalarTrait, Tensor};
use core::fmt;

impl<T: ScalarTrait> fmt::Display for Tensor<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        fn print_tensor<T: ScalarTrait>(
            tensor: &Tensor<T>,
            indices: &mut Vec<usize>,
            f: &mut fmt::Formatter<'_>,
        ) -> fmt::Result {
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
        fn format_tensor<T: ScalarTrait + fmt::Debug>(
            tensor: &Tensor<T>,
            level: usize,
            f: &mut fmt::Formatter,
        ) -> fmt::Result {
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
