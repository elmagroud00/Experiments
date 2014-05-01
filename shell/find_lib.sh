#!/bin/bash 
#sijiewang 2012/05/13

function parse()
{
	ldd $1 

	if [ $? -eq 0 ]; then
		ldd $1 | awk -F "=>" '{print $2}' | awk '{print $1}' | sed '/^$/d' | grep "/"  &>>$tmp
	fi
}

function ergodic()
{
    cd $1	

	for file in `ls`
	do
		echo "process $file ... ..."

		if [ -d $file ]; then
			echo "find folder: $file"
			ergodic $file
			cd .. 
		fi

		if [ -f $file ]; then
			echo "find file: $file"	
			echo $file | grep -i "so"
			if [ $? -eq 0 ]; then
				parse $file
			fi
		fi
	done
}
#################### Main ########################
if [ $# != 2 ]; then
	echo "Usage: $0 <lib folder> <output file>"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Parameter error, first parameter  must be a folder"
	exit 2 
fi

folder=$1
output=$2
tmp="/tmp/find_lib_sh`data +%Y%m%d%H%M%S`"

echo "lib folder: $folder"
echo "output file: $output"
echo "temp output file: $tmp"

cat /dev/null>$tmp 
if [ $? -ne 0 ]; then
	echo "create $tmp failed"
	exit 3
fi

cat /dev/null>$output
if [ $? -ne 0 ]; then
	echo "create $output failed"
	exit 4
fi

ergodic $folder

if [ -f $tmp ]; then
	sort -u $tmp > $output
	rm -rf $tmp
fi
