# SeaShell
by Sarah Yoon and Winston Venderbush

### Features:
* Forks and executes commands
* Parses multiple commands on one line
* Redirects using >, <, >>, 2>, &>, and |
* Supports blank cd and cd ~ support for home directory

### Attempted:
* IDK

### Bugs:
* IDK

### Files & Function Headers:
* parse.c - Handles all line parsing functions
```no-highlight
/*******************************************************
PROMPT: prints current dir and delimiter 
Takes as input: none
Returns: none
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

