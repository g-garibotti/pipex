# Pipex Project Checklist

## 1. Project Setup
- [ ] Create project directory structure
- [ ] Set up Makefile with required rules (NAME, all, clean, fclean, re)
- [ ] Create main.c file
- [ ] Create pipex.h header file

## 2. Argument Parsing
- [ ] Validate number of arguments
- [ ] Parse and store input file, commands, and output file

## 3. File Handling
- [ ] Implement function to open input file
- [ ] Implement function to create/open output file

## 4. Pipe Creation
- [ ] Implement pipe creation using pipe()

## 5. Process Creation and Management
- [ ] Implement fork() to create child processes
- [ ] Set up proper input/output redirection for each process using dup2()

## 6. Command Execution
- [ ] Parse commands to separate command and arguments
- [ ] Implement command execution using execve()

## 7. Error Handling
- [ ] Implement error checking for all system calls
- [ ] Create informative error messages
- [ ] Ensure proper exit statuses

## 8. Memory Management
- [ ] Properly allocate and free memory
- [ ] Check for and fix any memory leaks

## 9. Norm Compliance
- [ ] Ensure all functions are 25 lines or less
- [ ] Follow naming conventions (snake_case for functions and variables)
- [ ] Proper indentation and spacing
- [ ] Appropriate comments (only outside of functions)

## 10. Testing
- [ ] Create test cases
- [ ] Compare output with shell command results

## 11. Bonus (if applicable)
- [ ] Implement handling for multiple pipes
- [ ] Implement "here_doc" functionality

## 12. Documentation
- [ ] Write clear comments in your code
- [ ] Create a README.md file explaining how to use your program

## 13. Final Review
- [ ] Run Norminette on all .c and .h files
- [ ] Ensure Makefile doesn't relink
- [ ] Test with various inputs and edge cases