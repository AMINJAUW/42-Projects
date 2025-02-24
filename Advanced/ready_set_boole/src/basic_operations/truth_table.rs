enum ASTNode {
    Variable(char),
    Constant(bool),
    Not(Box<ASTNode>),
    And(Box<ASTNode>, Box<ASTNode>),
    Or(Box<ASTNode>, Box<ASTNode>),
    Xor(Box<ASTNode>, Box<ASTNode>),
    MaterialConditional(Box<ASTNode>, Box<ASTNode>),
    MaterialBiconditional(Box<ASTNode>, Box<ASTNode>),
}

fn populate_tree(formula: &str) -> Result<ASTNode, &str> {
    let mut stack = Vec::new();

    for token in formula.chars() {
        match token {
            'A'..='Z' => {
                stack.push(ASTNode::Variable(token));
            }
            '0' => {
                stack.push(ASTNode::Constant(false));
            }
            '1' => {
                stack.push(ASTNode::Constant(true));
            }
            '!' => {
                if let Some(expr) = stack.pop() {
                    stack.push(ASTNode::Not(Box::new(expr)));
                } else {
                    return Err("Too many operators for the number of Variables");
                }
            }
            '&' => {
                if let (Some(right), Some(left)) = (stack.pop(), stack.pop()) {
                    stack.push(ASTNode::And(Box::new(left), Box::new(right)));
                } else {
                    return Err("Too many operators for the number of Variables");
                }
            }
            '|' => {
                if let (Some(right), Some(left)) = (stack.pop(), stack.pop()) {
                    stack.push(ASTNode::Or(Box::new(left), Box::new(right)));
                } else {
                    return Err("Too many operators for the number of Variables");
                }
            }
            '^' => {
                if let (Some(right), Some(left)) = (stack.pop(), stack.pop()) {
                    stack.push(ASTNode::Xor(Box::new(left), Box::new(right)));
                } else {
                    return Err("Too many operators for the number of Variables");
                }
            }
            '>' => {
                if let (Some(right), Some(left)) = (stack.pop(), stack.pop()) {
                    stack.push(ASTNode::MaterialConditional(
                        Box::new(left),
                        Box::new(right),
                    ));
                } else {
                    return Err("Too many operators for the number of Variables");
                }
            }
            '=' => {
                if let (Some(right), Some(left)) = (stack.pop(), stack.pop()) {
                    stack.push(ASTNode::MaterialBiconditional(
                        Box::new(left),
                        Box::new(right),
                    ));
                } else {
                    return Err("Too many operators for the number of Variables");
                }
            }
            _ => {
                return Err("Invalid operator");
            }
        }
    }

    if let Some(tree) = stack.pop() {
        if stack.is_empty() {
            return Ok(tree);
        } else {
            return Err("Invalid formula");
        }
    } else {
        return Err("Invalid Formula");
    }
}

fn first_line(formula: &str) -> Vec<char> {
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

    // Print the header line
    let formatted_vars: Vec<String> = vars.iter().map(|&var| format!("| {}", var)).collect();
    let separator = "| = |$";
    let dash_line = "|---".repeat(vars.len() + 1) + "|";

    // Combine the formatted variables and the separator
    let output = formatted_vars.join(" ") + " " + separator;
    println!("{}", output);
    println!("{}", dash_line);

    vars // Return the sorted vector of variables
}

fn evaluate_tree(node: &ASTNode, vars: &std::collections::HashMap<char, bool>) -> bool {
    match node {
        ASTNode::Variable(c) => *vars.get(c).unwrap(),
        ASTNode::Constant(val) => *val,
        ASTNode::Not(expr) => !evaluate_tree(&*expr, vars),
        ASTNode::And(left, right) => evaluate_tree(&*left, vars) && evaluate_tree(&*right, vars),
        ASTNode::Or(left, right) => evaluate_tree(&*left, vars) || evaluate_tree(&*right, vars),
        ASTNode::Xor(left, right) => evaluate_tree(&*left, vars) != evaluate_tree(&*right, vars),
        ASTNode::MaterialConditional(left, right) => {
            !evaluate_tree(&*left, vars) || evaluate_tree(&*right, vars)
        }
        ASTNode::MaterialBiconditional(left, right) => {
            evaluate_tree(&*left, vars) == evaluate_tree(&*right, vars)
        }
    }
}

use std::collections::HashMap;

fn print_rest(tree: &ASTNode, vars: &Vec<char>) {
    let total_combinations = 1 << vars.len(); // 2^n combinations

    let reversed_vars: Vec<char> = vars.iter().cloned().rev().collect();

    for i in 0..total_combinations {
        let mut vars_map = HashMap::new();

        for (j, &var) in reversed_vars.iter().enumerate() {
            let value = (i & (1 << j)) != 0; // check if the bit for this variable is set to 1
            vars_map.insert(var, value);
        }

        let values: Vec<String> = vars
            .iter()
            .map(|&var| {
                if let Some(&val) = vars_map.get(&var) {
                    if val { "1" } else { "0" }.to_string()
                } else {
                    "0".to_string() // Default to "0" if variable not found
                }
            })
            .collect();

        // Evaluate the expression and format the output
        let result = evaluate_tree(tree, &vars_map);
        let output = format!("| {}", values.join(" | "))
            + &format!(" | {} |$", if result { "1" } else { "0" });
        println!("{}", output);
    }
}

pub fn print_truth_table(formula: &str) {
    match populate_tree(formula) {
        Err(e) => println!("{e}"),
        Ok(tree) => {
            let vars = first_line(formula);
            print_rest(&tree, &vars)
        }
    }
}
