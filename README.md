# Deadlock Detection Program

This program implements the deadlock detection algorithm with multiple resources of each type. It reads from a file the following inputs: the number of processes, the number of resource types, the number of resources of each type in existence (vector E), the current allocation matrix C (first row, followed by the second row, and so on), and the request matrix R (first row, followed by the second row, and so on). The output of the program indicates whether there is a deadlock in the system. In case there is, the program prints out the identities of all processes that are deadlocked.

## How to Compile and Run the Program

1. Ensure you have `gcc` installed on your system.
2. Clone this repository.
3. Navigate to the repository directory.
4. Run the following command to compile the program:

   ```
   make
   ```

5. Run the program with the following command:

   ```
   ./main
   ```

## Input File Format

The input file should be named `input.txt` and should be placed in the same directory as the executable. The format of the input file is as follows:

```
<number_of_processes> <number_of_resource_types>
<resources_of_each_type>
<current_allocation_matrix>
<request_matrix>
```

### Example

```
3 2
10 5
0 1
2 0
3 0
1 0
0 2
1 1
```

In this example:
- There are 3 processes and 2 resource types.
- The vector E (resources of each type in existence) is [10, 5].
- The current allocation matrix C is:
  ```
  0 1
  2 0
  3 0
  ```
- The request matrix R is:
  ```
  1 0
  0 2
  1 1
  ```
