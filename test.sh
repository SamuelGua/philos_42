#!/bin/bash

make

VFF="valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes"
file_in="in"

if [ ! -e "$file_in" ]; then
	touch "$file_in"
	echo "$file_in was created"
fi

echo "	[1] : 1 800 200 200 not eat and die 
	[2] : 3 800 200 200 no one die
	[3] : 3 800 200 200 [7] no one die
	[4] : 4 410 200 200 no one die
	[5] : 4 310 200 100 one die
Put a number :" 
read user_input

case "$user_input" in
	"1")
			./philo 1 800 200 200
		;;
	"2")
			./philo 5 800 200 200 
		;;
	"3")
			./philo 5 800 200 200 7
		;;
	"4")
			./philo 4 410 200 200
		;;
	"5")
			./philo 4 310 200 100
		;;
	*)
		echo "wrong numbers"


esac
