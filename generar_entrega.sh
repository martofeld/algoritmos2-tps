#!/bin/bash
DIR=$1

if [[ -z $DIR ]]; then
	echo "NO DIR"
	exit 1
fi

function run_tests {
	echo "Corriendo pruebas"
	gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c
	chmod +x ./pruebas
	./pruebas
	if [[ $? -ne 0 ]]; then
		exit $?
	fi
}

function copy_files {
	cp ../testing.h testing.h
	cp ../testing.c testing.c
}

function zip_files {
	echo "Generando .zip"
	if [ -f 101320_$DIR ]; then
		rm 101320_$DIR.zip
	fi

	zip 101320_$DIR *.c *.h -x main.c
}

function clean_up {
	rm testing.h
	rm testing.c
	rm pruebas
	cd ..
}

cd $DIR
copy_files
run_tests
zip_files
clean_up