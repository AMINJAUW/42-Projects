fn operate(a: bool, b: bool, op: char) -> bool {
    match op {
        '&' => a && b,
        '|' => a || b,
        '^' => a != b,
        '>' => !a || b,
        '=' => a == b,
        _ => unreachable!("Should come here !"),
    }
}

fn calculate_formula(formula: &str) -> Result<bool, &str> {
    let mut values_stack: Vec<bool> = Vec::new();

    for char in formula.chars() {
        match char {
            '0' | '1' => values_stack.push(char == '1'),

            '!' => {
                if let Some(a) = values_stack.pop() {
                    values_stack.push(!a);
                } else {
                    return Err("Not enough operators");
                }
            }

            '&' | '|' | '^' | '>' | '=' => {
                if let (Some(b), Some(a)) = (values_stack.pop(), values_stack.pop()) {
                    let c = operate(a, b, char);
                    values_stack.push(c);
                } else {
                    return Err("Not enough operators");
                }
            }

            _ => return Err("Invalid char"),
        }
    }
    if let Some(result) = values_stack.pop() {
        if values_stack.is_empty() {
            Ok(result)
        } else {
            Err("Not enough operators")
        }
    } else {
        Err("empty string")
    }
}

pub fn eval_formula(formula: &str) -> bool {
    match calculate_formula(formula) {
        Ok(res) => res,
        Err(e) => {
            println!("{e}");
            false
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_simple_and() {
        assert_eq!(eval_formula("11&"), true);
        assert_eq!(eval_formula("10&"), false);
        assert_eq!(eval_formula("01&"), false);
        assert_eq!(eval_formula("00&"), false);
    }

    #[test]
    fn test_simple_or() {
        assert_eq!(eval_formula("11|"), true);
        assert_eq!(eval_formula("10|"), true);
        assert_eq!(eval_formula("01|"), true);
        assert_eq!(eval_formula("00|"), false);
    }

    #[test]
    fn test_simple_xor() {
        assert_eq!(eval_formula("11^"), false);
        assert_eq!(eval_formula("10^"), true);
        assert_eq!(eval_formula("01^"), true);
        assert_eq!(eval_formula("00^"), false);
    }

    #[test]
    fn test_implication() {
        assert_eq!(eval_formula("11>"), true);
        assert_eq!(eval_formula("10>"), false);
        assert_eq!(eval_formula("01>"), true);
        assert_eq!(eval_formula("00>"), true);
    }

    #[test]
    fn test_equivalence() {
        assert_eq!(eval_formula("11="), true);
        assert_eq!(eval_formula("10="), false);
        assert_eq!(eval_formula("01="), false);
        assert_eq!(eval_formula("00="), true);
    }

    #[test]
    fn test_negation() {
        assert_eq!(eval_formula("1!"), false);
        assert_eq!(eval_formula("0!"), true);
    }

    #[test]
    fn test_complex_formula() {
        // Formula: (1 AND 0) OR 1 -> should be true
        assert_eq!(eval_formula("10&1|"), true);
        // Formula: (1 AND 0) OR 0 -> should be false
        assert_eq!(eval_formula("10&0|"), false);
    }

    #[test]
    fn test_invalid_char() {
        assert_eq!(calculate_formula("1a&").is_err(), true);
    }

    #[test]
    fn test_not_enough_operands() {
        assert_eq!(calculate_formula("&").is_err(), true);
        assert_eq!(calculate_formula("1&").is_err(), true);
        assert_eq!(calculate_formula("1!&").is_err(), true);
    }

    #[test]
    fn test_extra_operands() {
        // Formula: "10" has extra operand after evaluation
        assert_eq!(calculate_formula("10").is_err(), true);
    }
}
