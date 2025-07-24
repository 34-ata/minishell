# Minishell

A lightweight Unix shell implementation written in C, designed to replicate core functionality of bash with custom parsing, execution, and built-in command handling.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Architecture](#architecture)
- [Signal Handling](#signal-handling)
- [Error Handling](#error-handling)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Authors](#authors)

## 🔍 Overview

Minishell is a simplified shell implementation that provides essential shell functionality including command execution, piping, redirection, environment variable handling, and built-in commands. This project demonstrates low-level system programming concepts and shell mechanics.

## ✨ Features

### Core Functionality
- **Command Execution**: Execute system commands with full path resolution
- **Built-in Commands**: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- **Environment Variables**: Full support for environment variable expansion
- **Signal Handling**: Proper handling of `SIGINT` and `SIGQUIT`

### Advanced Features
- **Piping**: Connect commands with pipes (`|`)
- **Redirection**: Input (`<`), output (`>`), and append (`>>`) redirection
- **Heredoc**: Support for heredoc syntax (`<<`)
- **Quote Handling**: Proper parsing of single and double quotes
- **Variable Expansion**: `$VAR`, `$?` (exit status), and `$0` (shell name) expansion

### Parser Features
- **Robust Tokenization**: Advanced lexical analysis with quote handling
- **Syntax Validation**: Comprehensive syntax error detection
- **Command Chaining**: Support for complex command combinations

## 🚀 Installation

### Prerequisites
- GCC compiler
- GNU Readline library
- Make utility
- Unix-like operating system (Linux/macOS)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/minishell.git
cd minishell

# Compile the project
make

# Run minishell
./minishell
```

### Clean Build
```bash
make clean    # Remove object files
make fclean   # Remove all generated files including readline
make re       # Rebuild everything
```

## 💻 Usage

### Basic Commands
```bash
# Start minishell
./minishell

# Execute commands
minishell$> ls -la
minishell$> pwd
minishell$> echo "Hello World"
```

### Piping and Redirection
```bash
# Piping
minishell$> ls | grep .c | wc -l

# Output redirection
minishell$> echo "Hello" > output.txt
minishell$> echo "World" >> output.txt

# Input redirection
minishell$> wc -l < input.txt

# Heredoc
minishell$> cat << EOF
> This is a heredoc
> Multiple lines supported
> EOF
```

### Environment Variables
```bash
# Export variables
minishell$> export NAME="John"
minishell$> echo $NAME

# View environment
minishell$> env

# Unset variables
minishell$> unset NAME
```

## 🔧 Built-in Commands

| Command | Description | Usage |
|---------|-------------|-------|
| `cd` | Change directory | `cd [directory]` |
| `echo` | Display text | `echo [-n] [string ...]` |
| `env` | Display environment variables | `env` |
| `exit` | Exit the shell | `exit [status]` |
| `export` | Set environment variables | `export [var=value]` |
| `pwd` | Print working directory | `pwd` |
| `unset` | Remove environment variables | `unset [variable]` |

### Built-in Command Details

#### `cd` - Change Directory
```bash
cd              # Go to HOME directory
cd ~            # Go to HOME directory  
cd -            # Go to previous directory (OLDPWD)
cd /path/to/dir # Go to specific directory
```

#### `echo` - Display Text
```bash
echo "Hello World"           # Basic output
echo -n "No newline"         # Suppress trailing newline
echo $USER                   # Variable expansion
echo "Exit status: $?"       # Special variable expansion
```

#### `export` - Environment Variables
```bash
export VAR=value            # Set and export variable
export VAR="multi word"     # Handle spaces with quotes
export                      # List all exported variables
```

## 🏗️ Architecture

### Core Components

#### 1. Parser System (`parsing/`)
- **Lexical Analysis**: Tokenizes input into commands, arguments, and operators
- **Syntax Validation**: Checks for syntax errors and malformed commands
- **Quote Processing**: Handles single/double quotes and escape sequences
- **Variable Expansion**: Expands environment variables and special parameters

#### 2. Execution Engine (`execute/`)
- **Command Resolution**: PATH-based command lookup and execution
- **Process Management**: Fork/exec model with proper process handling  
- **Pipe Implementation**: Inter-process communication via pipes
- **Redirection**: File descriptor manipulation for I/O redirection

#### 3. Built-in Commands (`builtin/`)
- **Command Detection**: Identifies built-in vs external commands
- **Environment Management**: Handles environment variable operations
- **Directory Navigation**: Implements `cd` with OLDPWD tracking
- **Process Control**: Manages shell exit and signal handling

#### 4. Utility Systems (`utils/`)
- **Signal Management**: Custom signal handlers for different contexts
- **Error Handling**: Comprehensive error reporting and recovery
- **Memory Management**: Dynamic allocation and cleanup routines
- **String Processing**: Advanced string manipulation utilities

### Data Structures

#### Command Structure (`t_cmds`)
```c
typedef struct s_cmds {
    char                *cmd;        // Command name
    char                **flags;     // Command flags
    char                **args;      // Command arguments
    char                **input;     // Input redirections
    char                **output;    // Output redirections
    char                **heredoc;   // Heredoc delimiters
    char                **append;    // Append redirections
    int                 status;      // Command status flags
    pid_t               pid;         // Process ID
    char                **envr;      // Environment variables
    struct s_main_env   *env;        // Environment structure
    struct s_cmds       *next;       // Next command in pipeline
} t_cmds;
```

#### Environment Structure (`t_main_env`)
```c
typedef struct s_main_env {
    char    **envr;      // Environment variable array
    char    *minipwd;    // Shell executable path ($0)
} t_main_env;
```

### Execution Flow

1. **Input Reading**: Readline library handles input with history
2. **Parsing Phase**: 
   - Tokenization and quote processing
   - Syntax validation
   - Command structure creation
3. **Execution Phase**:
   - Built-in command detection
   - Process creation and management
   - Pipe and redirection setup
   - Command execution
4. **Cleanup**: Memory deallocation and resource cleanup

## 📡 Signal Handling

### Signal Contexts

#### Main Process (`MAIN_P`)
- **SIGINT**: Displays new prompt line
- **SIGQUIT**: Ignored (no core dump)

#### Child Process (`CHILD_P`)  
- **SIGINT**: Default behavior (terminate)
- **SIGQUIT**: Default behavior (core dump)

#### Heredoc Process (`HEREDOC_P`)
- **SIGINT**: Special handling with cleanup
- **SIGQUIT**: Ignored

### Implementation
```c
void set_signal(int context) {
    switch(context) {
        case MAIN_P:
            signal(SIGINT, &handler);
            signal(SIGQUIT, SIG_IGN);
            break;
        case CHILD_P:
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            break;
        case HEREDOC_P:
            signal(SIGINT, &handler_heredoc);
            signal(SIGQUIT, SIG_IGN);
            break;
    }
}
```

## ⚠️ Error Handling

### Comprehensive Error Coverage

#### Syntax Errors
- Unclosed quotes detection
- Invalid pipe sequences  
- Malformed redirections
- Empty command validation

#### Runtime Errors
- Command not found (127)
- Permission denied (126)
- File/directory access errors (1)
- Invalid numeric arguments (255)

#### Resource Management
- Memory allocation failures
- File descriptor leaks prevention
- Process cleanup on errors
- Environment corruption protection

### Exit Status Codes
- `0`: Success
- `1`: General error
- `126`: Permission denied / Not executable
- `127`: Command not found
- `130`: Interrupted by SIGINT
- `255`: Invalid exit argument

## 📁 Project Structure

```
minishell/
├── builtin/              # Built-in command implementations
│   ├── cd.c             # Directory navigation
│   ├── echo.c           # Text output command
│   ├── env.c            # Environment display
│   ├── exit.c           # Shell termination
│   ├── export.c         # Variable export
│   ├── pwd.c            # Working directory
│   ├── unset.c          # Variable removal
│   └── check_built.c    # Built-in detection
├── execute/              # Command execution engine
│   ├── execute.c        # Main execution logic
│   ├── read_and_exec.c  # Execution controller
│   ├── heredoc.c        # Heredoc processing
│   └── child.c          # Child process handling
├── parsing/              # Input parsing system
│   ├── parse1.c         # Primary parser
│   ├── parse2.c         # Output handling
│   ├── parse3.c         # Input handling
│   ├── parse4.c         # Command extraction
│   ├── parse5.c         # Flag processing
│   ├── parse6.c         # Argument processing
│   ├── dollar.c         # Variable expansion
│   └── arg_control.c    # Argument validation
├── utils/                # Utility functions
│   ├── signal.c         # Signal management
│   ├── error_msg.c      # Error reporting
│   ├── execute_utils_*.c # Execution utilities
│   ├── cd_utils*.c      # Directory utilities
│   └── main_utils.c     # General utilities
├── inc/                  # Header files
│   └── minishell.h      # Main header
├── lib/                  # External libraries
│   └── libft/           # Custom C library
├── Makefile             # Build configuration
└── main.c               # Entry point
```

## 🤝 Contributing

### Development Guidelines

1. **Code Style**: Follow consistent C coding standards
2. **Memory Management**: Always free allocated memory
3. **Error Handling**: Implement comprehensive error checking
4. **Documentation**: Comment complex algorithms and data structures

### Contribution Process

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-feature`)
3. Commit changes (`git commit -am 'Add new feature'`)
4. Push to branch (`git push origin feature/new-feature`)
5. Create a Pull Request

## 👥 Authors

- **fuyar** - *Main Developer* - Core implementation and architecture
- **faata** - *Co-Developer* - Built-in commands and utilities

## 📄 License

This project is part of the 42 School curriculum. Created for educational purposes.

---

**Note**: This shell implementation is designed for educational purposes and may not include all features of production shells like bash or zsh. It demonstrates fundamental concepts of shell programming and Unix system calls.
