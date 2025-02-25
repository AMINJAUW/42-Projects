# The Sorting Algorithm *Push_swap*

The objective here is to create a sorting algorithm, using 2 stacks  
We are free to implement it as we want in C.  

See the full [Project Subject](./en.subject.pdf)
for more details.

### My Algorithm

- less than 5 elements:  
hardcoded to minimise the movements

- more than 5  
Go through the whole stack and for each element push it on stack b only if this element is in the 30% top values in stack a, until there is only 5 elements left.  
Sort the 5 elements.  
Then calculate for each element in B calculate the number of operations needed to push it on the stack a on the right position.  
And then do just that for the minimum for until the whole stack is sorted.  
Rotate the stack to have the smallest element in front.


## Installation

```bash
make
```

## Usage

Example usage
```bash
./push_swap 2 1 3 6 5 8
``` 

---
**[⬅ Back to My Profile](https://github.com/AMINJAUW)**  
📬 **Want to reach me? Contact me via GitHub!**