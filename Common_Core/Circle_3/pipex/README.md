# *Pipex*

The objective here is learn about forks pipes and execve  
See the full [Project Subject](./en.subject.pdf)
for more details.

## Installation

```bash
make
```

## Usage

Example usage
```bash
./pipex file1 cmd1 cmd2 file2
``` 
It must take 4 arguments:  
- file1 and file2 are file names.  
- cmd1 and cmd2 are shell commands with their parameters  

Example
```bash
 ./pipex infile "ls -l" "wc -l" outfile
```
will behave like 
```bash
< infile ls -l | wc -l > outfile
```
---
**[⬅ Back to My Profile](https://github.com/AMINJAUW)**  
📬 **Want to reach me? Contact me via GitHub!**