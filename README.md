# Pipex — 42 Project

A program that replicates the behavior of shell **pipes** in C. Mimics the functionality of `< infile cmd1 | cmd2 > outfile` as part of the 42 school curriculum.

## How It Works

```bash
# Shell equivalent:
< infile cmd1 | cmd2 > outfile

# Pipex:
./pipex infile "cmd1" "cmd2" outfile
```

## Example

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
# Equivalent to: < input.txt grep hello | wc -l > output.txt
```

## Bonus Features

- Multiple pipes: `./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile`
- Here_doc support: `./pipex here_doc LIMITER cmd1 cmd2 outfile`

## Tech Stack

- **C**
- **Unix pipes & fork**
- **Makefile**

## How to Build

```bash
make
make bonus    # for bonus features
```

## Author

**Houssame El Bandoudi** — [GitHub](https://github.com/HOUSSAMEELBANDOUDI) | 42 Student (hel-band)
