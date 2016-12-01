# SeaShell
by Sarah Yoon and Winston Venderbush

####NOTE: This project requires GNU Readline to run properly!
#####To install GNU Readline easily, run:
```no-highlight
$ brew install readline
```

### Features:
* Forks and executes commands
* Parses multiple commands on one line
* Redirects using >, <, >>, 2>, &>, and |
* Supports blank cd and cd ~ support for home directory
* Support for tab auto-completion, history navigation with vertical arrow keys, text navigation with horizontal arrow keys (via GNU readline) 

### Attempted:
* ~~Beautifying prompt (ie. show only current base directory, not entire path from root), etc.~~ (possible functionality included, but we decided we didn't like the way it looked as much!)
* User settings (multiple short/long multiple prompt modes, multiple prompt colors, etc.)
* Color support (for prompt) in shell
* Handling spaces/quotes in filenames


### Bugs:
* Opening files with spaces in their names is currently impossible (because of splitting on space)
* CTRL + D throws a segmentation fault rather than cleanly exiting the shell process

### Files & Function Headers:
* parse.c - Handles all line parsing functions
```no-highlight
/*******************************************************
PROMPT: returns current dir and delimiter for prompt
Takes as input: none
Returns: char array containing the prompt and delimiter
*******************************************************/

/*******************************************************
SPLIT: splits str on delimiter 
Takes as input: input string, delimiter
Returns: array of pointers to strings
*******************************************************/

/*******************************************************
TRIMSPACE: removes extra white space from inside and 
            around a given string
Takes as input: input string
Returns: "trimmed" output string
*******************************************************/

/*******************************************************
PARSE: Handles parsing multiple commands and passes 
        them to check for redirection or piping
Takes as input: input string
Returns: none
*******************************************************/
```
* shell.c - Handles the forking/executing of commands, redirection
```no-highlight
/*******************************************************
CHECKRP: Checks input string from terminal for redirects
          piping, or other necessary markers and passes 
          to other functions to handle accordingly
Takes as input: input string
Returns: none
*******************************************************/

/*******************************************************
LEFTREDIR: Splits the input on "<" and performes the
            proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

/*******************************************************
RIGHTREDIR: Splits the input on ">" and performes the
            proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

/*******************************************************
RIGHTDOUBLEREDIR: Splits the input on ">>" and performes the
            proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

/*******************************************************
TWOREDIR: Splits the input on "2>" and performes the
            proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

/*******************************************************
AMPREDIR: Splits the input on "&>" and performes 
            the proper redirection before passing the
            command for execution
Takes as input: input string
Returns: none
*******************************************************/

/*******************************************************
PARSEPIPE: Splits the input on "|" and performes proper
            redirection, passing commands to individual
            forked processes for execution
Takes as input: input string
Returns: none
*******************************************************/

/*******************************************************
EXECUTE: forks child that executes cmd, waits for child
Takes as input: line is a string, the input from the
                terminal
Returns: 1 if successful, 0 otherwise
*******************************************************/
```
* main.c - Gets the show on the road! (main function)

