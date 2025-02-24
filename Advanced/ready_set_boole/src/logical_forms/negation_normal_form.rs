#[derive(Clone)]
struct Node {
    val: char,
    is_neg: bool,
    children: Option<Vec<Box<Node>>>,
}

impl Node {
    // Constructor to create a new node with no children
    fn new(val: char) -> Self {
        Node {
            val,
            is_neg: false,
            children: None,
        }
    }

    // Method to add a child node
    fn add_child(&mut self, child: Node) {
        match &mut self.children {
            Some(children) => {
                children.push(Box::new(child));
            }
            None => {
                self.children = Some(vec![Box::new(child)]);
            }
        }
    }

    fn inverse_node(&mut self) {
        match self.val {
            'A'..='Z' => self.is_neg = !self.is_neg,

            '|' => {
                //¬(A ∨ B) ⇔ (¬A ∧ ¬B)
                let children = self.children.as_mut().unwrap();
                children[0].inverse_node();
                children[1].inverse_node();
                self.val = '&'
            }
            '&' => {
                let children = self.children.as_mut().unwrap();
                children[0].inverse_node();
                children[1].inverse_node();
                self.val = '|'
            }

            _ => unreachable!(),
        }
    }

    fn nnf(&self) -> String {
        let mut result = String::new();

        if let Some(children) = &self.children {
            result.push_str(&children[0].nnf());
            result.push_str(&children[1].nnf());
        }
        result.push(self.val);
        if self.is_neg {
            result.push('!');
        }

        result
    }
}

fn parse_into_tree(formula: &str) -> Result<Vec<Node>, &str> {
    let mut stack: Vec<Node> = Vec::new();

    for token in formula.chars() {
        match token {
            'A'..='Z' => {
                let node = Node::new(token);
                stack.push(node);
            }

            '!' => {
                if let Some(mut node) = stack.pop() {
                    node.inverse_node();
                    stack.push(node)
                } else {
                    return Err("not enough values for operator: invalid formula");
                }
            }

            '&' | '|' => {
                let mut node = Node::new(token);
                if let (Some(right), Some(left)) = (stack.pop(), stack.pop()) {
                    node.add_child(left);
                    node.add_child(right);
                    stack.push(node)
                }
            }

            '>' => {
                //(A ⇒ B) ⇔ (¬A ∨ B)
                let mut node = Node::new('|');
                if let (Some(right), Some(mut left)) = (stack.pop(), stack.pop()) {
                    left.inverse_node();
                    node.add_child(left);
                    node.add_child(right);
                    stack.push(node)
                } else {
                    return Err("not enough values for operator: invalid formula");
                }
            }

            '=' => {
                //(A ⇔ B) ⇔ (¬A ∨ B) ∧ (A ∨ ¬B)
                let mut node = Node::new('&');
                let mut sub_node_left = Node::new('|');
                let mut sub_node_right = Node::new('|');
                if let (Some(left_right), Some(mut left_left)) = (stack.pop(), stack.pop()) {
                    let right_left = left_left.clone();
                    let mut right_right = left_right.clone();
                    left_left.inverse_node();
                    right_right.inverse_node();
                    sub_node_left.add_child(left_left);
                    sub_node_left.add_child(left_right);
                    sub_node_right.add_child(right_left);
                    sub_node_right.add_child(right_right);
                    node.add_child(sub_node_left);
                    node.add_child(sub_node_right);
                    stack.push(node);
                } else {
                    return Err("not enough values for operator: invalid formula");
                }
            }

            '^' => {
                // A ^ B ⇔ (A ∧ ¬B) ∨ (¬A ∧ B)
                let mut node = Node::new('|');
                let mut sub_node_left = Node::new('&');
                let mut sub_node_right = Node::new('&');
                if let (Some(mut left_right), Some(left_left)) = (stack.pop(), stack.pop()) {
                    let mut right_left = left_left.clone();
                    let right_right = left_right.clone();
                    left_right.inverse_node();
                    right_left.inverse_node();
                    sub_node_left.add_child(left_left);
                    sub_node_left.add_child(left_right);
                    sub_node_right.add_child(right_left);
                    sub_node_right.add_child(right_right);
                    node.add_child(sub_node_left);
                    node.add_child(sub_node_right);
                    stack.push(node);
                } else {
                    return Err("not enough values for operator: invalid formula");
                }
            }

            _ => {
                return Err("Invalid character in formula");
            }
        }
    }

    if stack.len() != 1 {
        return Err("Invalid formula");
    }
    return Ok(stack);
}

pub fn negation_normal_form(formula: &str) -> String {
    let mut output = String::new();
    match parse_into_tree(formula) {
        Err(e) => {
            output.push_str(e);
        }
        Ok(mut stack) => {
            let tree = stack.pop().unwrap();
            output = tree.nnf();
        }
    }
    return output;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_opposite_and_operation() {
        // Test: !(A ∧ B) (in RPN: AB&!)
        let formula = "AB&!"; // ¬(A ∧ B) should transform to ¬A ∨ ¬B
        let expected = "A!B!|"; // Output in NNF
        let result = negation_normal_form(formula);
        assert_eq!(result, expected);
    }

    #[test]
    fn test_opposite_or_operation() {
        // Test: !(A ∨ B) (in RPN: AB|!)
        let formula = "AB|!"; // ¬(A ∨ B) should transform to ¬A ∧ ¬B
        let expected = "A!B!&"; // Output in NNF
        let result = negation_normal_form(formula);
        assert_eq!(result, expected);
    }

    #[test]
    fn test_xor_operation() {
        // Test: !(A ⊕ B) (in RPN: AB^)
        let formula = "AB^"; // (A ⊕ B) should transform to (A ∧ ¬B) ∨ (¬A ∧ B)
        let expected = "AB!&A!B&|"; // Output in NNF
        let result = negation_normal_form(formula);
        assert_eq!(result, expected);
    }

    #[test]
    fn test_opposite_xor_operation() {
        // Test: !(A ⊕ B) (in RPN: AB^!)
        let formula = "AB^!"; // ¬(A ⊕ B) should transform to ¬((A ∧ ¬B) ∨ (¬A ∧ B)) = ¬(A ∧ ¬B) ∧ ¬(¬A ∧ B) = (¬A ∨ B) ∧ (A ∨ ¬B)
        let expected = "A!B|AB!|&"; // Output in NNF
        let result = negation_normal_form(formula);
        assert_eq!(result, expected);
    }

    #[test]
    fn test_material_conditional() {
        // Test: !(A → B) (in RPN: AB>!)
        let formula = "AB>"; // (A → B) should transform to ¬A ∨ B
        let expected = "A!B|"; // Output in NNF
        let result = negation_normal_form(formula);
        assert_eq!(result, expected);
    }

    #[test]
    fn test_opposite_material_conditional() {
        // Test: !(A → B) (in RPN: AB>!)
        let formula = "AB>!"; // ¬(A → B) should transform to A ∧ ¬B
        let expected = "AB!&"; // Output in NNF
        let result = negation_normal_form(formula);
        assert_eq!(result, expected);
    }

    #[test]
    fn test_material_biconditional() {
        // Test: !(A ↔ B) (in RPN: AB=!)
        let formula = "AB="; // ¬(A ↔ B) should transform to (¬A ∨ B) ∧ (A ∨ ¬B)
        let expected = "A!B|AB!|&"; // Output in NNF
        let result = negation_normal_form(formula);
        assert_eq!(result, expected);
    }
}
