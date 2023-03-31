# PIPES & REDIRECTIONS

echo "Hello, World" > file | cat < file | echo "$PATH .$PWD .$HOME .$USER" > file15 | cat < file15 | wc -l

echo "$PATH" > EXPANDING | echo "UserName: $USER" >> EXPANDING | cat < EXPANDING | grep "ahammout" | wc -l

cat EXPANDING > file1 > file2 > file3 > file4 > file5 > file6 > file7 | cat < file7


/// REDIRECTING IN / HEREDOC WITH NON CMD.