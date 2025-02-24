pub fn print_powerset(powerset: &Vec<Vec<i32>>) {
    for subset in powerset {
        println!("{:?} ", subset);
    }
    println!("Total size of the powerSet = {}", powerset.len());
}

pub fn powerset(set: Vec<i32>) -> Vec<Vec<i32>> {
    let mut power_set: Vec<Vec<i32>> = Vec::new();
    if set.len() == 0 {
        power_set.push(set);
        return power_set;
    }
    let number_of_subsets: u32 = 1 << set.len(); //total size of the power set 2^n with n = |S|

    for i in 0..number_of_subsets {
        let mut new_set = Vec::new();
        for j in 0..32 {
            if (i & (1 << j)) != 0 {
                new_set.push(set[j]);
            }
        }
        power_set.push(new_set);
    }
    return power_set;
}
