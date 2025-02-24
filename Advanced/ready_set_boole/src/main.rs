use ready_set_bool::advanced_topics::curve::map;
use ready_set_bool::advanced_topics::inverse_function::reverse_map;
use ready_set_bool::basic_operations::adder::adder;
use ready_set_bool::basic_operations::boolean_evaluation::eval_formula;
use ready_set_bool::basic_operations::gray_code::gray_code;
use ready_set_bool::basic_operations::multiplier::multiplier;
use ready_set_bool::basic_operations::truth_table::print_truth_table;
use ready_set_bool::logical_forms::conjunctive_normal_form::conjunctive_normal_form;
use ready_set_bool::logical_forms::negation_normal_form::negation_normal_form;
use ready_set_bool::logical_forms::sat::sat;
use ready_set_bool::set_theory::powerset::{powerset, print_powerset};
use ready_set_bool::set_theory::set_evaluation::eval_set;
use std::io::{self, Write};
use std::num::ParseIntError;
use std::process::exit;
use std::str::FromStr;

fn main() {
    loop {
        // Prompt the user for an exercise number

        println!("Select an exercise between 0 and 11 to test (other will exit): ");
        println!();
        // Flush stdout to ensure prompt appears before user input
        io::stdout().flush().unwrap();

        // Read user input
        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");

        // Parse the input as an integer
        run_exercice(input.trim().parse::<u32>());
        println!();
        println!("{}", "-".repeat(45));
        println!();
    }
}

fn run_exercice(input: Result<u32, ParseIntError>) {
    match input {
        Ok(choice) => match choice {
            0 => {
                // Adder
                let nums = prompt_for_numbers::<u32>(
                    "Enter two numbers to add (separated by space): ",
                    Some(2),
                    false,
                );
                let (a, b) = (nums[0], nums[1]);
                let result = adder(a, b);
                println!("Adder: {} + {} = {}", a, b, result);
            }
            1 => {
                // Multiplier
                let nums = prompt_for_numbers::<u32>(
                    "Enter two numbers to multiply (separated by space): ",
                    Some(2),
                    false,
                );
                let (a, b) = (nums[0], nums[1]);
                let result = multiplier(a, b);
                println!("Multiplier: {} * {} = {}", a, b, result);
            }
            2 => {
                // Gray Code
                let n = prompt_for_numbers::<u32>(
                    "Enter a number to tranform in Gray code format: ",
                    Some(1),
                    false,
                )[0];
                let result = gray_code(n);
                println!("Binary: {} in gray code is {}", n, result);
            }
            3 => {
                // Boolean Evalation
                println!("Enter your Boolean formula to check: ");
                io::stdout().flush().unwrap();
                let mut formula = String::new();
                io::stdin()
                    .read_line(&mut formula)
                    .expect("Failed to read line");
                println!("{}", eval_formula(formula.trim()));
            }
            4 => {
                // Truth Table
                println!("Enter your Boolean formula to show the Truth Table: ");
                io::stdout().flush().unwrap();
                let mut formula = String::new();
                io::stdin()
                    .read_line(&mut formula)
                    .expect("Failed to read line");
                print_truth_table(formula.trim());
            }
            5 => {
                // Negation normal form
                println!("Enter your Boolean formula to Transform into Negation normal form: ");
                io::stdout().flush().unwrap();
                let mut formula = String::new();
                io::stdin()
                    .read_line(&mut formula)
                    .expect("Failed to read line");
                println!("{}", negation_normal_form(formula.trim()));
            }
            6 => {
                // conjunctive Normal form
                println!("Enter your Boolean formula to Transform into conjunctive Normal form: ");
                io::stdout().flush().unwrap();
                let mut formula = String::new();
                io::stdin()
                    .read_line(&mut formula)
                    .expect("Failed to read line");
                println!("{}", conjunctive_normal_form(formula.trim()));
            }
            7 => {
                // SAT
                println!("Enter your Boolean formula to perform a SAT on it: ");
                io::stdout().flush().unwrap();
                let mut formula = String::new();
                io::stdin()
                    .read_line(&mut formula)
                    .expect("Failed to read line");
                println!("{}", sat(formula.trim()));
            }
            8 => {
                //Power Set
                let set = prompt_for_numbers::<i32>(
                    "Enter initial set to calculate Power sets",
                    None,
                    false,
                );
                print_powerset(&powerset(set));
            }
            9 => {
                // Set Evaluation
                println!("Enter your Boolean formula to evaluate with sets: ");
                io::stdout().flush().unwrap();
                let mut formula = String::new();
                io::stdin()
                    .read_line(&mut formula)
                    .expect("Failed to read line");

                // Determine how many sets the user wants to input
                let num_sets =
                    prompt_for_numbers::<usize>("Enter the number of sets: ", Some(1), false)[0];
                let mut sets = Vec::new();

                // Collect each set
                for i in 0..num_sets {
                    let prompt = format!(
                        "Enter the elements for set {} (separated by space): ",
                        (b'A' + i as u8) as char
                    );
                    let set = prompt_for_numbers::<i32>(&prompt, None, true);
                    sets.push(set);
                }

                // Evaluate the formula with the collected sets
                let result = eval_set(formula.trim(), sets);
                println!("The result of evaluating the formula is: {:?}", result);
            }
            10 => {
                //map
                let nums = prompt_for_numbers::<u16>(
                    "Give 2 u16 numbers between 0 and 65535",
                    Some(2),
                    false,
                );
                let f64_value = map(nums[0], nums[1]);
                println!("the value mapped = {}", f64_value);
                println!("Decoded gives: {:?}", reverse_map(f64_value));
            }
            11 => {
                //reverse map
                let num =
                    prompt_for_numbers::<f64>("Give a number between 0 and 1", Some(1), false);
                let (x, y) = reverse_map(num[0]);
                println!("Decoded gives: {} {}", x, y);
                println!("the value re mapped = {}", map(x, y));
            }
            _ => {
                // Handle invalid input
                println!("Invalid choice. Goodbye.");
                exit(1);
            }
        },
        Err(_) => {
            // Handle parsing error
            println!("Invalid choice. Goodbye.");
            exit(1);
        }
    }
}

fn prompt_for_numbers<T>(prompt: &str, count: Option<usize>, accept_empty: bool) -> Vec<T>
where
    T: FromStr + std::fmt::Debug,
    <T as FromStr>::Err: std::fmt::Debug,
{
    loop {
        println!("{}", prompt);
        io::stdout().flush().unwrap();

        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");

        let nums: Vec<T> = input
            .trim()
            .split_whitespace()
            .filter_map(|s| s.parse::<T>().ok())
            .collect();

        if let Some(n) = count {
            if nums.len() == n {
                return nums;
            } else {
                println!("Invalid input. Please enter exactly {} numbers.", n);
            }
        } else {
            if !nums.is_empty() || accept_empty {
                // If accept_empty is true, allow returning an empty vector
                return nums;
            } else {
                println!("Invalid input. Please enter at least one number.");
            }
        }
    }
}
