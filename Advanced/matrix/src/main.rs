use matrix::{Complex, Tensor};



fn generate_f32_sequence(len: usize) -> Vec<f32> {
    (0..len).map(|x| x as f32).collect()
}

// Helper function to generate a vector of increasing Complex numbers
fn generate_complex_sequence(len: usize) -> Vec<Complex> {
    (0..len)
        .map(|x| Complex { re: x as f32, im: (x as f32) * 2.0 * (if x%2 == 0 {-1.0} else {1.0}) })
        .collect()
}

fn main() {
	let t = Tensor::new(vec![2,3,4,5], generate_complex_sequence(2*3*4*5));

	println!("Initial Tenson\n{}\n\nTransposed\n{}",t.clone(), t.conjugate_transpose());
}
