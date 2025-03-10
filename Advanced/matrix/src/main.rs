
use matrix::tensor::Tensor;
use matrix::scalar::complex::Complex;

fn generate_f32_sequence(len: usize) -> Vec<f32> {
    (0..len).map(|x| x as f32).collect()
}

// Helper function to generate a vector of increasing Complex numbers
fn generate_complex_sequence(len: usize) -> Vec<Complex> {
    (0..len)
        .map(|x| Complex { re: x as f32, im: (x as f32) * 2.0 })
        .collect()
}

fn main() {
    let tensor = Tensor::new(vec![2,3,4,5], generate_complex_sequence(2 * 3 * 4 * 5));

    println!("{}", tensor);
}
