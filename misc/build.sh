#! /bin/sh

rm /home/arch/code/c/Advent/misc/execute_puzzles

printf "\n\n**********************************************************************************************************************\n\n"

gcc -Wall -c -g /home/arch/code/c/Advent/src/execute_puzzles.c -o /home/arch/code/c/Advent/bin/execute_puzzles.o
gcc -Wall -c -g /home/arch/code/c/Advent/src/libAdventPuzzles/core.c -o /home/arch/code/c/Advent/bin/static/core.o
#gcc -Wall -c -g -lcurl /home/arch/code/c/Advent/src/libAdventPuzzles/sn_instance.c -o /home/arch/code/c/Advent/bin/static/sn_instance.o
gcc -Wall -c -g /home/arch/code/c/Advent/src/libAdventPuzzles/file.c -o /home/arch/code/c/Advent/bin/static/file.o
gcc -Wall -c -g /home/arch/code/c/Advent/src/libAdventPuzzles/config.c -o /home/arch/code/c/Advent/bin/static/config.o
#gcc -Wall -c -g /home/arch/code/c/Advent/src/libAdventPuzzles/json.c -o /home/arch/code/c/Advent/bin/static/json.o
#ar rcs /home/arch/code/c/Advent/bin/static/libAdventPuzzles.a /home/arch/code/c/Advent/bin/static/core.o /home/arch/code/c/Advent/bin/static/file.o /home/arch/code/c/Advent/bin/static/sn_instance.o /home/arch/code/c/Advent/bin/static/config.o /home/arch/code/c/Advent/bin/static/json.o
ar rcs /home/arch/code/c/Advent/bin/static/libAdventPuzzles.a /home/arch/code/c/Advent/bin/static/core.o /home/arch/code/c/Advent/bin/static/file.o /home/arch/code/c/Advent/bin/static/config.o
 
#gcc -Wall -g -lcurl -lpthread /home/arch/code/c/Advent/bin/snfilesync.o -L/home/arch/code/c/Advent/bin/static -lSNFsync -o /home/arch/code/c/Advent/misc/snfilesync

gcc -Wall -g /home/arch/code/c/Advent/bin/execute_puzzles.o -L/home/arch/code/c/Advent/bin/static -lAdventPuzzles -o /home/arch/code/c/Advent/misc/execute_puzzles

printf "\n\n**********************************************************************************************************************\n\n"
