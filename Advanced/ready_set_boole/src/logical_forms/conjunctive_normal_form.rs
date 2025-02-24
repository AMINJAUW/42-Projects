#[derive(Clone)]
pub struct Node {
    pub val: char,
    pub is_neg: bool,
    pub right_leaf: Option<Box<Node>>,
    pub left_leaf: Option<Box<Node>>,
}

impl Node {
    // Constructor to create a new node with no children
    fn new(val: char) -> Self {
        Node {
            val,
            is_neg: false,
            right_leaf: None,
            left_leaf: None,
        }
    }

    // Method to add a child node
    fn add_leaves(&mut self, left_leaf: Node, right_leaf: Node) {
        self.left_leaf = Some(Box::new(left_leaf));
        self.right_leaf = Some(Box::new(right_leaf));
    }

    fn inverse_node(&mut self) {
        match self.val {
            'A'..='Z' => self.is_neg = !self.is_neg,

            '|' => {
                //¬(A ∨ B) ⇔ (¬A ∧ ¬B)
                self.right_leaf.as_mut().unwrap().inverse_node();
                self.left_leaf.as_mut().unwrap().inverse_node();
                self.val = '&'
            }
            '&' => {
                self.right_leaf.as_mut().unwrap().inverse_node();
                self.left_leaf.as_mut().unwrap().inverse_node();
                self.val = '|'
            }

            _ => unreachable!(),
        }
    }

    pub fn to_cnf(&mut self) {
        match self.val {
            '&' => {
                self.right_leaf.as_mut().unwrap().to_cnf();
                self.left_leaf.as_mut().unwrap().to_cnf();
            }

            '|' => {
                if self.left_leaf.as_ref().unwrap().val == '&' {
                    let left = self
                        .left_leaf
                        .as_ref()
                        .unwrap()
                        .left_leaf
                        .as_ref()
                        .unwrap()
                        .clone();
                    let right = self
                        .left_leaf
                        .as_ref()
                        .unwrap()
                        .right_leaf
                        .as_ref()
                        .unwrap()
                        .clone();

                    let mut new_left = Node::new('|');
                    let mut new_right = Node::new('|');
                    new_left.add_leaves(*left, *self.right_leaf.as_ref().unwrap().clone());
                    new_right.add_leaves(*right, *self.right_leaf.as_ref().unwrap().clone());

                    self.val = '&';
                    self.add_leaves(new_left, new_right);
                    self.to_cnf();
                } else if self.right_leaf.as_ref().unwrap().val == '&' {
                    let left = self
                        .right_leaf
                        .as_ref()
                        .unwrap()
                        .left_leaf
                        .as_ref()
                        .unwrap()
                        .clone();
                    let right = self
                        .right_leaf
                        .as_ref()
                        .unwrap()
                        .right_leaf
                        .as_ref()
                        .unwrap()
                        .clone();

                    let mut new_left = Node::new('|');
                    let mut new_right = Node::new('|');
                    new_left.add_leaves(*self.left_leaf.as_ref().unwrap().clone(), *left);
                    new_right.add_leaves(*self.left_leaf.as_ref().unwrap().clone(), *right);

                    self.val = '&';
                    self.add_leaves(new_left, new_right);
                    self.to_cnf();
                } else {
                    // Recursively apply to_cnf on both children if necessary
                    self.left_leaf.as_mut().unwrap().to_cnf();
                    self.right_leaf.as_mut().unwrap().to_cnf();
                }
            }
            _ => return,
        }
    }

    fn ft_to_str(&self) -> String {
        let mut result = String::new();

        if let (Some(left), Some(right)) = (&self.left_leaf, &self.right_leaf) {
            result.push_str(&left.ft_to_str());
            result.push_str(&right.ft_to_str());
        }

        result.push(self.val);
        if self.is_neg {
            result.push('!');
        }

        result
    }
}

pub fn parse_into_tree(formula: &str) -> Result<Vec<Node>, &str> {
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
                    node.add_leaves(left, right);
                    stack.push(node)
                }
            }

            '>' => {
                //(A ⇒ B) ⇔ (¬A ∨ B)
                let mut node = Node::new('|');
                if let (Some(right), Some(mut left)) = (stack.pop(), stack.pop()) {
                    left.inverse_node();
                    node.add_leaves(left, right);
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
                    sub_node_left.add_leaves(left_left, left_right);
                    sub_node_right.add_leaves(right_left, right_right);
                    node.add_leaves(sub_node_left, sub_node_right);
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
                    sub_node_left.add_leaves(left_left, left_right);
                    sub_node_right.add_leaves(right_left, right_right);
                    node.add_leaves(sub_node_left, sub_node_right);
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

pub fn conjunctive_normal_form(formula: &str) -> String {
    let mut output = String::new();
    match parse_into_tree(formula) {
        Err(e) => {
            output.push_str(e);
        }
        Ok(mut stack) => {
            let mut tree = stack.pop().unwrap();
            tree.to_cnf();
            output.push_str(&tree.ft_to_str());
        }
    }
    return output;
}
