use super::conjunctive_normal_form::{parse_into_tree, Node};
use std::collections::HashMap;

fn find_vars(formula: &str) -> Vec<char> {
    let mut vars = Vec::new();

    for var in formula.chars() {
        match var {
            'A'..='Z' => {
                if !vars.contains(&var) {
                    vars.push(var);
                }
            }
            _ => {}
        }
    }

    vars.sort();
    vars
}

fn evaluate_tree(tree: &Node, vars: &std::collections::HashMap<char, bool>) -> bool {
    match tree.val {
        '&' => {
            return evaluate_tree(tree.left_leaf.as_ref().unwrap(), vars)
                && evaluate_tree(tree.right_leaf.as_ref().unwrap(), vars)
        }

        '|' => {
            return evaluate_tree(tree.left_leaf.as_ref().unwrap(), vars)
                || evaluate_tree(tree.right_leaf.as_ref().unwrap(), vars)
        }

        'A'..='Z' => {
            if tree.is_neg {
                !*vars.get(&tree.val).unwrap()
            } else {
                *vars.get(&tree.val).unwrap()
            }
        }

        _ => {
            println!("Weird error");
            return false;
        }
    }
}

fn sat_calculation(tree: &Node, vars: Vec<char>) -> bool {
    let total_combinations = 1 << vars.len(); // 2^n combinations

    let reversed_vars: Vec<char> = vars.iter().cloned().rev().collect();

    for i in 0..total_combinations {
        let mut vars_map = HashMap::new();

        for (j, &var) in reversed_vars.iter().enumerate() {
            let value = (i & (1 << j)) != 0; // check if the bit for this variable is set to 1
            vars_map.insert(var, value);
        }
        if evaluate_tree(tree, &vars_map) {
            return true;
        }
    }
    return false;
}

pub fn sat(formula: &str) -> bool {
    match parse_into_tree(formula) {
        Err(e) => {
            println!("{e}");
            return false;
        }
        Ok(mut stack) => {
            let mut tree = stack.pop().unwrap();
            tree.to_cnf();
            let vars = find_vars(formula);
            return sat_calculation(&tree, vars);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_sat() {
        assert_eq!(sat("AB|"), true);
        assert_eq!(sat("AB&"), true);
        assert_eq!(sat("AA!&"), false);
        assert_eq!(sat("AA^"), false);
    }
}
