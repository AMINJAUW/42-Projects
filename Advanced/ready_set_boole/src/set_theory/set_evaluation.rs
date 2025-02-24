use super::super::logical_forms::conjunctive_normal_form::{parse_into_tree, Node};

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

fn add_sets(set_a: &Vec<i32>, set_b: &Vec<i32>) -> Vec<i32> {
    //intersection
    let mut result = Vec::new();
    for element in set_b {
        if set_a.contains(element) && set_b.contains(element) {
            result.push(element.clone());
        }
    }
    return result;
}

fn or_sets(set_a: &Vec<i32>, set_b: &Vec<i32>) -> Vec<i32> {
    //union
    let mut result = set_a.clone();
    for element in set_b {
        if !set_a.contains(element) {
            result.push(element.clone());
        }
    }
    return result;
}

fn invers_set(set: &Vec<i32>, sets: &Vec<Vec<i32>>) -> Vec<i32> {
    let mut result: Vec<i32> = Vec::new();
    let mut global_set: Vec<i32> = Vec::new();
    for i in 0..sets.len() {
        global_set = or_sets(&global_set, &sets[i]);
    }

    for element in global_set {
        if !set.contains(&element) {
            result.push(element);
        }
    }
    result
}

fn finale_set(tree: &Node, sets: &Vec<Vec<i32>>) -> Vec<i32> {
    match tree.val {
        'A'..='Z' => {
            let mut set = sets[(tree.val as u8 - b'A') as usize].clone();
            if tree.is_neg {
                set = invers_set(&set, sets);
            }
            return set;
        }
        '&' => {
            let left_set = finale_set(tree.left_leaf.as_ref().unwrap(), sets);
            let right_set = finale_set(tree.right_leaf.as_ref().unwrap(), sets);
            let result = add_sets(&left_set, &right_set);
            return result;
        }
        '|' => {
            let left_set = finale_set(tree.left_leaf.as_ref().unwrap(), sets);
            let right_set = finale_set(tree.right_leaf.as_ref().unwrap(), sets);
            let result = or_sets(&left_set, &right_set);
            return result;
        }

        _ => {
            unreachable!();
        }
    }
}

pub fn eval_set(formula: &str, sets: Vec<Vec<i32>>) -> Vec<i32> {
    if find_vars(formula).len() != sets.len() {
        println!("Error not the same number of var in the formula as there are sets");
        return vec![];
    }
    match parse_into_tree(formula) {
        Err(e) => {
            println!("{e}");
            return vec![];
        }
        Ok(mut stack) => {
            let tree = stack.pop().unwrap();
            return finale_set(&tree, &sets);
        }
    }
}
