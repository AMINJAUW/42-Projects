use crate::ScalarTrait;
use core::fmt;
use std::ops::{Add, Sub, Mul, Div, Neg, AddAssign, SubAssign, MulAssign, DivAssign};

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Complex {
    pub re: f32,
    pub im: f32,
}

// Implement the Scalar trait for Complex
impl ScalarTrait for Complex {
    fn unit() -> Self {
        Complex { re: 1.0f32, im: 1.0f32 }
    }
}

impl Default for Complex {
    fn default() -> Self {
        Complex { re: 0.0, im: 0.0 }
    }
}

impl fmt::Display for Complex {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        if self.im >= 0.0 {
            write!(f, "({} + {}i)", self.re, self.im)
        } else {
            write!(f, "({} - {}i)", self.re, -self.im)
        }
    }
}

impl Add for Complex {
    type Output = Self;

    fn add(self, rhs: Self) -> Self {
        Self {
            re: self.re + rhs.re,
            im: self.im + rhs.im,
        }
    }
}

// Implement subtraction
impl Sub for Complex {
    type Output = Self;

    fn sub(self, rhs: Self) -> Self {
        Self {
            re: self.re - rhs.re,
            im: self.im - rhs.im,
        }
    }
}

// Implement multiplication
impl Mul for Complex {
    type Output = Self;

    fn mul(self, rhs: Self) -> Self {
        Self {
            re: self.re * rhs.re - self.im * rhs.im,
            im: self.re * rhs.im + self.im * rhs.re,
        }
    }
}

//implementation multiplication with a f32
impl Mul<f32> for Complex {

    type Output = Self;
    
    fn mul(self, rhs: f32) -> Self::Output {
        Self {
            re: self.re * rhs,
            im: self.im * rhs,
        }
    }
}

// Implement division
impl Div for Complex {
    type Output = Self;

	/// Complex division goes as follow
	/// z = z_n / z_d = (a + bi) / (c + di)  
	/// We then multiply it by z_d*  the complex conjugate od the denominator  
	/// z = (a + bi) * (c - di) / (c^2 + d^2)  
    fn div(self, rhs: Self) -> Self {
        let denominator = rhs.re * rhs.re + rhs.im * rhs.im;
        Self {
            re: (self.re * rhs.re + self.im * rhs.im) / denominator,
            im: (self.im * rhs.re - self.re * rhs.im) / denominator,
        }
    }
}

// Implement negation
impl Neg for Complex {
    type Output = Self;

    fn neg(self) -> Self {
        Self {
            re: -self.re,
            im: -self.im,
        }
    }
}

// Implement AddAssign
impl AddAssign for Complex {
    fn add_assign(&mut self, rhs: Self) {
        self.re += rhs.re;
        self.im += rhs.im;
    }
}

// Implement SubAssign
impl SubAssign for Complex {
    fn sub_assign(&mut self, rhs: Self) {
        self.re -= rhs.re;
        self.im -= rhs.im;
    }
}

// Implement MulAssign
impl MulAssign for Complex {
    fn mul_assign(&mut self, rhs: Self) {
        let re = self.re * rhs.re - self.im * rhs.im;
        let im = self.re * rhs.im + self.im * rhs.re;
        self.re = re;
        self.im = im;
    }
}

// Implement DivAssign
impl DivAssign for Complex {
    fn div_assign(&mut self, rhs: Self) {
        let denominator = rhs.re * rhs.re + rhs.im * rhs.im;
        let re = (self.re * rhs.re + self.im * rhs.im) / denominator;
        let im = (self.im * rhs.re - self.re * rhs.im) / denominator;
        self.re = re;
        self.im = im;
    }
}
 
// Implement magnitude (absolute value)
impl Complex {
    pub fn abs(self) -> f32 {
        (self.re * self.re + self.im * self.im).sqrt()
    }

    pub fn conj(self) -> Self {
        Self {
            re: self.re,
            im: -self.im,
        }
    }
}