#!/bin/bash
clear
i=1
j=1
empty_red="\033[41m "
empty_blue="\033[44m "
red_queen="\033[41m\u265B"
blue_queen="\033[44m\u265B"
# echo "solutions/FMatrix${1}.txt"
file=$( echo "solutions/FMatrix${1}.txt" )
# cat $file
while read line
do
	for word in $line
	do
		S=$(((i+j)%2))
		if [ $S -eq 0 ]
		then
			if [ $word -eq 0 ]
			then
				A=${blue_queen}
			else
				A=${empty_blue}
			fi
			echo -n -e "${A} "
		else
			if [ $word -eq 0 ]
			then
				A=${red_queen}
			else
				A=${empty_red}
			fi
			echo -n -e "${A} "

		fi
		j=$((j + 1))
	done
	echo -e -n "\e[0m" # blue, ensure it exists normally
	echo "" # new line
	i=$((i + 1))
	j=1
done < $file
# done < solutions/FMatrix.txt
