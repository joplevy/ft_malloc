gcc -o toto  main.c -L. -lft_malloc
env -i ./run.sh ./toto
make
