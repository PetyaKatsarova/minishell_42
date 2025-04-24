/**
 * 
 * ls | grep "test" | wc -l
 * 
 *  cat < input.txt > output.txt
    Reads from input.txt, writes to output.txt.

    echo hi > file1 > file2      # Only the last one should be effective (file2)

    echo hi >                   # Should print syntax error
    Empty redirection target

    > file                      # Should create/empty file
    >> file                     # Should create file

    export VAR=42 > out.txt     # `VAR` still set, but out.txt is touched

    !! (echo hi > file) runs the command in a subshell.
    The parentheses () create a new child shell.
    Inside that child shell: echo hi > file is executed.
    Redirection affects only the subshell, not the main shell.
    VAR=main
(echo hi > file; VAR=sub)
echo $VAR
➡ file gets hi, but VAR remains main in the main shell.
 */
