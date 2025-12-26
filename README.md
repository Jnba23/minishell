# Minishell

A small UNIX shell built from scratch.  
Reproduces basic bash behavior using parsing, tokenization, and process control.

## 🎯 Objectives
- Implement our own command interpreter
- Learn parsing, environment variables, pipes & redirections
- Strengthen knowledge of `fork()`, `execve()`, signals, and file descriptors

## 🧱 Features
- Prompt + history
- Builtins:
  - echo (-n), cd, pwd, export, unset, env, exit
- Single & multiple pipes
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable expansion (`$VAR`)
- Quote handling (single / double quotes)
- Signal handling similar to bash (`ctrl-C`, `ctrl-D`, `ctrl-\`)

## 🛠️ Build
```bash
make
```
## ▶️ Run
```bash
./minishell
```
## 📚 Notes
- Uses readline (42 Linux setup)
- Based on POSIX standards
