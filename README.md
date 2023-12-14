<h1 align="center">
        pipex
</h1>

<p align="center">
        <i>42 cursus - Rank 2</i><br>
        Final grade: <b>100/100</b>
</p>

# 📝 Subject
This project consists in reproducing as closely as possible the behaviour of the next shell instruction:<br>
```shell
$> < file1 cmd1 | cmd2 > file2
```
The behaviour of this instruction can be easily summarized:<br>
- Use `cmd1` on `file1`
- Use `cmd2` on the result
- Put that final result in `file2`

Example:<br>
- file1 content (infile)
```
Hello
World!
```
- Instruction used
```shell
$> < file1 cat -e | grep W > file2
```
- file2 content (outfile)
```
World!$
```
This project aims to make us understand how forks, pipes and file descriptors actually work, by creating and manipulating them.

# 🖥️ Usage
To compile the project, you simply need to type `make` in your shell terminal.<br>
You will get an executable file named `pipex`.

You can execute it as following, it will have the same behaviour as the shell instruction we've just seen:
```shell
./pipex file1 cmd1 cmd2 file2
```
