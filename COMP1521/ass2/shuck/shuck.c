////////////////////////////////////////////////////////////////////////
// COMP1521 21t2 -- Assignment 2 -- shuck, A Simple Shell
// <https://www.cse.unsw.edu.au/~cs1521/21T2/assignments/ass2/index.html>
//
// Written by Chun-Ho Raphael Woo (z5360132) on 2021-07-29.
//
// 2021-07-12    v1.0    Team COMP1521 <cs1521@cse.unsw.edu.au>
// 2021-07-21    v1.1    Team COMP1521 <cs1521@cse.unsw.edu.au>
//     * Adjust qualifiers and attributes in provided code,
//       to make `dcc -Werror' happy.
//

#include <sys/types.h>

#include <sys/stat.h>
#include <sys/wait.h>

#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// [[ TODO: put any extra `#include's here ]]
#include <spawn.h>
#include <glob.h>

// [[ TODO: put any `#define's here ]]

//
// Interactive prompt:
//     The default prompt displayed in `interactive' mode --- when both
//     standard input and standard output are connected to a TTY device.
//
static const char *const INTERACTIVE_PROMPT = "shuck& ";

//
// Default path:
//     If no `$PATH' variable is set in Shuck's environment, we fall
//     back to these directories as the `$PATH'.
//
static const char *const DEFAULT_PATH = "/bin:/usr/bin";

//
// Default history shown:
//     The number of history items shown by default; overridden by the
//     first argument to the `history' builtin command.
//     Remove the `unused' marker once you have implemented history.
//
static const int DEFAULT_HISTORY_SHOWN __attribute__((unused)) = 10;

//
// Input line length:
//     The length of the longest line of input we can read.
//
static const size_t MAX_LINE_CHARS = 1024;

//
// Special characters:
//     Characters that `tokenize' will return as words by themselves.
//
static const char *const SPECIAL_CHARS = "!><|";

//
// Word separators:
//     Characters that `tokenize' will use to delimit words.
//
static const char *const WORD_SEPARATORS = " \t\r\n";

// [[ TODO: put any extra constants here ]]
//bool FILE_NEED_EXPAN = false;

// [[ TODO: put any type definitions (i.e., `typedef', `struct', etc.) here ]]

static void execute_command(char **words, char **path, char **environment, char *file_fp);
static void do_exit(char **words);
static int is_executable(char *pathname);
static char **tokenize(char *s, char *separators, char *special_chars);
static void free_tokens(char **tokens);

// [[ TODO: put any extra function prototypes here ]]
void spawn_process(char *path, char **env, char **argv);
void save_n_return(FILE *fp_write, char **words, bool file_need_expan, char **words_ptr);
int file_num_line(FILE *fp_read, char line[MAX_LINE_CHARS]);
void cd(char **words);
void pwd();
void history (char **words, FILE *fp_write, FILE *fp_read, char *program, bool file_need_expan, char ** new_words);
bool too_much_argument(char **words, int value, char *program);
bool file_expansion (char *word);
char** expand_word(char *word, char **words, int location);

int main (void)
{
    // Ensure `stdout' is line-buffered for autotesting.
    setlinebuf(stdout);

    // Environment variables are pointed to by `environ', an array of
    // strings terminated by a NULL value -- something like:
    //     { "VAR1=value", "VAR2=value", NULL }
    extern char **environ;

    // Grab the `PATH' environment variable for our path.
    // If it isn't set, use the default path defined above.
    char *pathp;
    if ((pathp = getenv("PATH")) == NULL) {
        pathp = (char *) DEFAULT_PATH;
    }
    char **path = tokenize(pathp, ":", "");

    // Should this shell be interactive?
    bool interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);

    //set up the path for the file /shuck.history
    // file_fp need to be free
    char *file_name = "/.shuck_history";
    char *home = getenv("HOME");
    int home_len = strlen(home) + strlen(file_name) + 2;
    char file_fp[home_len];
    strcpy(file_fp, home);
    strcat(file_fp, file_name);

    // Main loop: print prompt, read line, execute command
    while (1) {
        // If `stdout' is a terminal (i.e., we're an interactive shell),
        // print a prompt before reading a line of input.
        if (interactive) {
            fputs(INTERACTIVE_PROMPT, stdout);
            fflush(stdout);
        }

        char line[MAX_LINE_CHARS];
        if (fgets(line, MAX_LINE_CHARS, stdin) == NULL)
            break;

        // Tokenise and execute the input line.
        char **command_words =
            tokenize(line, (char *) WORD_SEPARATORS, (char *) SPECIAL_CHARS);
        execute_command(command_words, path, environ, file_fp);
        free_tokens(command_words);
    }
    free_tokens(path);
    return 0;
}

// save command into the fp
void save_n_return(FILE *fp_write, char **words, bool file_need_expan, char **new_words) {
    int i = 0;
    while (words[i] != NULL) {
        if (i != 0) {
            fputc(' ', fp_write);
        }
        fprintf(fp_write, "%s", words[i]);
        i++;
    }
    fputc('\n', fp_write);
    if (file_need_expan) {
        free_tokens(new_words);
    }
    return;
}

int file_num_line(FILE *fp_read, char line[MAX_LINE_CHARS]) {
    int i = 0;
    while (fgets(line, MAX_LINE_CHARS, fp_read)) {
        //loop through the entire file to check num of line
        i++;
    }
    return i;
}

// change the directory 
void cd(char **words) {
    if (words[1] == NULL) {
        // cd command runs with no argument
        // change directory to HOME
        char *home = getenv("HOME");
        chdir(home);
    } else if (words[1] != NULL && chdir(words[1]) != 0) {
        // if it fail to return or no argument is provided
        // print to strerr, cd: 'words[1]' : error
        fprintf(stderr, "cd: %s: ", words[1]);
        perror("");
        return;
    } 
}

// show the current directory
void pwd (void) {
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("pwd: ");        
    } else {
        printf("current directory is '%s'\n", cwd);   
    }
}

// show the previous command typed
// dont accept two number
// dont accept non number as variable n
// if no number is provide as n, 10 is default
void history (char **words, FILE *fp_write, FILE *fp_read, char *program, bool file_need_expan, char **new_words) {
    int n = 10;
    int i = 0;
    int start_print_line;
    bool too_many_arg = too_much_argument(words, 2, program);
    if (too_many_arg == true) {
        // if too many argument
        save_n_return(fp_write, words, file_need_expan, new_words);
        return;
    }
    if (words[1] != NULL) {
        // if n is specified
        // check if it is a number or not
        int c = words[1][0];
        if (c >= '0' && c <= '9' && words[1][1] == '\0') {
            // if n is a digit
            n = atoi(words[1]);
        } else {
            save_n_return(fp_write, words, file_need_expan, new_words);
            fprintf(stderr, "%s: %s: numeric argument required\n", program, words[1]);
            return;
        }
        
    }
    char line[MAX_LINE_CHARS];
    i = file_num_line(fp_read, line);
    start_print_line = i - n;
    i = 0;
    fseek(fp_read, 0, SEEK_SET);
    while (fgets(line, MAX_LINE_CHARS, fp_read)) {
        //loop through the entire file to check num of line
        // if the line has reach the start_print_line
        // print the line
        if (i >= start_print_line) {
            printf("%d: ", i);
            fputs(line, stdout);
        }
        i++;
    }
}

// it will goint throught the word list and see if the number of word in the list is over the value set
// if so, return too many argument
bool too_much_argument(char **words, int value, char *program) {
    int i = 0;
    while (words[i] != NULL) {
        //check number of argument
        i++;
    }
    if (i > value) {
        // if too much argument
        fprintf(stderr, "%s: too many arguments\n", program);
        return true;
    } else {
        return false;
    }
}

// return true if provided word has need le char in the word
bool file_expansion (char *word) {
    char *needles = "*?[~";   
    char *ret;
    int s = 0;
    while (needles[s] != '\0') {
        char needle = needles[s];
        ret = strchr(word, needle);
        if (ret != NULL) {
            // if provided word has needle char in the word
            return true;
        }
        s++;
    }
    return false;
}

// return a new char** of the word expended, if no need to expand, return the old char**
// old char will not be freed
char** expand_word(char *word, char **words, int location) {
    // malloc two block, one for before the location, one for after the location, assume 1024 extra words max
    char **temp_words_before_location = calloc(1024, sizeof(*temp_words_before_location));
    char **temp_words_after_location = calloc(1024, sizeof(*temp_words_after_location));
    int i = 0;
    int j = 0;
    while (words[i] != NULL) {
        if (i <= location) {
            temp_words_before_location[i] = strdup(words[i]);
        } else {    
            temp_words_after_location[j] = strdup(words[i]);
        }  
        i++;   
    }
    char *newline = strrchr(word, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }
    glob_t matches; // holds pattern expansion
    int result = glob(word, GLOB_NOCHECK|GLOB_TILDE, NULL, &matches);

    if (result != 0) {
        // if glob fail
        printf("glob returns %d\n", result);
    } else if ((int)matches.gl_pathc >= 1){
        i = 0;
        int new_location = location + i;
        while (i < matches.gl_pathc) {
            // place the new word in the before_location array
            // new_location will be the value at the end of the array
            temp_words_before_location[new_location] = strdup(matches.gl_pathv[i]);
            i++;
            new_location++;
        }
        // after adding new words from glob to the before_location array, add the after_location 
        // array to the before location array then realloc words and make words the same as 
        // the before location array
        i = 0;
        while (temp_words_after_location[i] != NULL) {
            temp_words_before_location[new_location] = strdup(temp_words_after_location[i]);
            i++;
            new_location++;
        }
        free_tokens(temp_words_after_location);
        globfree(&matches);
        return temp_words_before_location;
    }
    return words;
}

// it will spawn process based on the path and argv given
void spawn_process(char *path, char **env, char **argv) {
    pid_t pid;
    if (posix_spawn(&pid, path, NULL, NULL, argv, env) != 0) {
        perror("spawn");
        exit(EXIT_FAILURE);
    }
    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        printf("%s exit status = %d\n", path, exit_status);
    }
    return;
}

//
// Execute a command, and wait until it finishes.
//
//  * `words': a NULL-terminated array of words from the input command line
//  * `path': a NULL-terminated array of directories to search in;
//  * `environment': a NULL-terminated array of environment variables.
//
static void execute_command(char **words, char **path, char **environment, char *file_fp)
{
    bool file_need_expan = false;
    int count = 0;
    char **new_words = words;
    while (words[count] != NULL) {
        if (file_expansion(words[count])) {
            // if the word need to be expand
            new_words = expand_word(words[count], words, count);
            file_need_expan = true;
            break;
        }
        count++;
    }
    if (file_need_expan == true) {
        while (new_words[count] != NULL) {
            if (file_expansion(new_words[count])) {
                // if the word need to be expand
                // may need to free the word[count]
                char **temp_ptr = new_words;
                new_words = expand_word(new_words[count], new_words, count);
                if (temp_ptr != new_words) {
                    // if the pointer changed
                    // free the preverious char**
                    free_tokens(temp_ptr);
                }
            }
            count++;
        }
    }
    
    assert(words != NULL);
    assert(path != NULL);
    assert(environment != NULL);
    char *program;
    if (file_need_expan == true) {
        program = new_words[0];
    } else {
        program = words[0];
    }

    FILE *fp_write = fopen(file_fp, "a");
    if (fp_write == NULL) {
        perror("$HOME/.shuck_history_write");
        exit(1);
    }
    FILE *fp_read = fopen(file_fp, "r");
    if (fp_read == NULL) {
        perror("$HOME/.shuck_history_read");
        exit(1);
    }
    

    if (program == NULL) {
        // nothing to do
        fclose(fp_write);
        fclose(fp_read);
        return;
    }

    if (strcmp(program, "exit") == 0) {
        save_n_return(fp_write, words, file_need_expan, new_words);
        fclose(fp_write);
        fclose(fp_read);

        do_exit(words);
        // `do_exit' will only return if there was an error.
        return;
    }

    //subset 0
    if (strcmp(program, "cd") == 0) {
        // if 'cd'
        // move to the file 
        // if the **words change because it need expan, use the new **word instead
        if (file_need_expan) {
            cd(new_words);
        } else {
            cd(words);
        }
        save_n_return(fp_write, words, file_need_expan, new_words);
        fclose(fp_write);
        fclose(fp_read);
        return;  
    }
    if (strcmp(program, "pwd") == 0) {
        // if 'pwd'
        pwd();
        save_n_return(fp_write, words, file_need_expan, new_words);
        fclose(fp_write);
        fclose(fp_read);
        return;
    }

    //subset 2
    if (strcmp(program, "history") == 0) {
        // if program == history
        history(words, fp_write, fp_read, program, file_need_expan, new_words);
        save_n_return(fp_write, words, file_need_expan, new_words);
        fclose(fp_write);
        fclose(fp_read);
        return;       
    }


    if (strcmp(program, "!") == 0) {
        // if !n
        char line[MAX_LINE_CHARS];
        int n = file_num_line(fp_read, line) - 1;
        int i = 0;
        bool too_many_arg = too_much_argument(words, 2, program);
        if (too_many_arg == true) {
            // if too many argument
            save_n_return(fp_write, words, file_need_expan, new_words);
            return;
        }
        if (words[1] != NULL) {
            // if n is specified
            // check if it is a number or not
            int c = words[1][0];
            if (c >= '0' && c <= '9' && words[1][1] == '\0') {
                // if n is a digit and digit only
                n = atoi(words[1]);
            } else {
                save_n_return(fp_write, words, file_need_expan, new_words);
                fprintf(stderr, "%s: %s: numeric argument required\n", program, words[1]);
                return;
            }
        }
        fseek(fp_read, 0, SEEK_SET);
        while (fgets(line, MAX_LINE_CHARS, fp_read)) {
            if (i == n) {
                // if it reach the line we to to execute
                // leave so line will be the command we want to execute
                fputs(line, stdout); 
                break;
            }
            i++;
        }
        
        // run the execute command with the line collected with fgets
        char **command_words =
        tokenize(line, (char *) WORD_SEPARATORS, (char *) SPECIAL_CHARS);
        execute_command(command_words, path, environment, file_fp);
        fclose(fp_write);
        fclose(fp_read);
        free_tokens(command_words);
        return;
    }
    
    // subset 1
    if (strrchr(program, '/') == NULL) {
        // search for a program to run
        int i = 0;
        bool is_path = false;
        while (path[i] != NULL && is_path == false) {
            // loop through all the possiblility for possible path for the program
            char n_path[256] = "";
            strcat(n_path, path[i]);
		    strcat(n_path, "/");
		    strcat(n_path, program);

            if (is_executable(n_path) == true) {
                // if path found
                // execute the program 
                char *n_path_ptr = &n_path[0];
                if (file_need_expan == true) {
                    spawn_process(n_path_ptr, environment, new_words);
                } else {
                    spawn_process(n_path_ptr, environment, words);
                }  
                save_n_return(fp_write, words, file_need_expan, new_words);
                fclose(fp_write);
                fclose(fp_read);
                is_path = true;
                return;
            } 
            i++;
        }
	    if (is_path == false) {
            // if no path were found
		    fprintf(stderr, "%s: command not found\n", program);
	    }
    } else if (is_executable(program)) {
        // if it is suppose to be excuteable by itself, then try execute it with out any modify
        spawn_process(program, environment, words);
        save_n_return(fp_write, words, file_need_expan, new_words);
        fclose(fp_write);
        fclose(fp_read);
        return;
    } else {
        fprintf(stderr, "%s: command not found\n", program);
    }
}



//
// Implement the `exit' shell built-in, which exits the shell.
//
// Synopsis: exit [exit-status]
// Examples:
//     % exit
//     % exit 1
//
static void do_exit(char **words)
{
    assert(words != NULL);
    assert(strcmp(words[0], "exit") == 0);

    int exit_status = 0;

    if (words[1] != NULL && words[2] != NULL) {
        // { "exit", "word", "word", ... }
        fprintf(stderr, "exit: too many arguments\n");

    } else if (words[1] != NULL) {
        // { "exit", something, NULL }
        char *endptr;
        exit_status = (int) strtol(words[1], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "exit: %s: numeric argument required\n", words[1]);
        }
    }

    exit(exit_status);
}


//
// Check whether this process can execute a file.  This function will be
// useful while searching through the list of directories in the path to
// find an executable file.
//
static int is_executable(char *pathname)
{
    struct stat s;
    return
        // does the file exist?
        stat(pathname, &s) == 0 &&
        // is the file a regular file?
        S_ISREG(s.st_mode) &&
        // can we execute it?
        faccessat(AT_FDCWD, pathname, X_OK, AT_EACCESS) == 0;
}


//
// Split a string 's' into pieces by any one of a set of separators.
//
// Returns an array of strings, with the last element being `NULL'.
// The array itself, and the strings, are allocated with `malloc(3)';
// the provided `free_token' function can deallocate this.
//
static char **tokenize(char *s, char *separators, char *special_chars)
{
    size_t n_tokens = 0;

    // Allocate space for tokens.  We don't know how many tokens there
    // are yet --- pessimistically assume that every single character
    // will turn into a token.  (We fix this later.)
    char **tokens = calloc((strlen(s) + 1), sizeof *tokens);
    assert(tokens != NULL);

    while (*s != '\0') {
        // We are pointing at zero or more of any of the separators.
        // Skip all leading instances of the separators.
        s += strspn(s, separators);

        // Trailing separators after the last token mean that, at this
        // point, we are looking at the end of the string, so:
        if (*s == '\0') {
            break;
        }

        // Now, `s' points at one or more characters we want to keep.
        // The number of non-separator characters is the token length.
        size_t length = strcspn(s, separators);
        size_t length_without_specials = strcspn(s, special_chars);
        if (length_without_specials == 0) {
            length_without_specials = 1;
        }
        if (length_without_specials < length) {
            length = length_without_specials;
        }

        // Allocate a copy of the token.
        char *token = strndup(s, length);
        assert(token != NULL);
        s += length;

        // Add this token.
        tokens[n_tokens] = token;
        n_tokens++;
    }

    // Add the final `NULL'.
    tokens[n_tokens] = NULL;

    // Finally, shrink our array back down to the correct size.
    tokens = realloc(tokens, (n_tokens + 1) * sizeof *tokens);
    assert(tokens != NULL);

    return tokens;
}


//
// Free an array of strings as returned by `tokenize'.
//
static void free_tokens(char **tokens)
{
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
