#!/bin/bash

R='\e[91m'
G='\e[92m'
B='\e[94m'
X='\e[0m'

user_cmd=(
	'./pipex test/infile "" test/user_output'
	'./pipex test/infile "cat" "" test/user_output'
	'./pipex test/infile "" "grep 42" test/user_output'
	'./pipex test/infile "" "" test/user_output'
	'./pipex test/nofile "cat" "grep 42" test/user_output'
	'./pipex test/infile "cat" "wc" test/user_output'
	'./pipex test/infile "cot" "wc" test/user_output'
	'./pipex test/infile "cat" "grep 42" "wc -l" test/user_output'
	'./pipex here_doc stop "wc -l" test/user_output'
	'./pipex here_doc stop "cat" "head -n1" test/user_output'
)

bash_cmd=(
	'< test/infile "" > test/bash_output'
	'< test/infile cat | "" > test/bash_output'
	'< test/infile "" | grep 42 > test/bash_output'
	'< test/infile "" | "" > test/bash_output'
	'< test/nofile cat | grep 42 > test/bash_output'
	'< test/infile cat | wc > test/bash_output'
	'< test/infile cot | wc > test/bash_output'
	'< test/infile cat | grep 42 | wc -l > test/bash_output'
	'echo -n "" > test/bash_output'
	'here_doc' #'<< stop cat | head -n1 >> test/bash_output'
)

function test() {
    max_index=${#user_cmd[@]}
    if [ ${#bash_cmd[@]} -gt $max_index ]; then
        max_index=${#bash_cmd[@]}
    fi

    for ((i=0; i<max_index; i++)); do
		echo ""
		echo -e "--- ${B}TEST ${i}${X} ---"
		echo -n "" > test/user_output
		echo -n "" > test/bash_output
        if [ $i -lt ${#user_cmd[@]} ]; then
			echo "test: ${user_cmd[$i]}"
			eval "${user_cmd[$i]}"
        fi
        if [ $i -lt ${#bash_cmd[@]} ]; then
			if [[ ${bash_cmd[$i]} == "here_doc" ]]; then
				cat <<-stop | head -n1 > test/bash_output
				42
				stop
			else
            	eval "${bash_cmd[$i]}"
			fi
        fi
		user_file="test/user_output"
		bash_file="test/bash_output"
		if cmp -s "$user_file" "$bash_file"; then
			echo -e "grade: ${G}OK${X}"
		else
			echo -e "grade: ${R}KO${X}"
		fi
		echo ""
    done
}

test
