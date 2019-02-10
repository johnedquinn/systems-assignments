
#!/bin/bash

# Initial prototype
if [ $# -eq 0 ]
then
	echo "Usage: extract.sh archive1 archive2..."
else
for i in "$@"
do
	case $i in
		*.tar.gz)
			if ! tar xzvf $i; then
				exit 1
			fi
			;;
		*.tgz)
			if ! tar xzvf $i; then
				exit 1
			fi
			;;
		*.tbz)
			if ! tar xvjf $i; then
				exit 1
			fi
			;;
		*.tar.bz2)
			if ! tar xvjf $i; then
				exit 1
			fi
			;;
		*.txz)
			if ! tar Jxvf $i; then
				exit 1
			fi
			;;
		*.tar.xz)
			if ! tar Jxvf $i; then
				exit 1
			fi
			;;
		*.zip)
			if ! unzip -o $i; then
				exit 1
			fi
			;;
		*.jar)
			if ! unzip -o $i; then
				exit 1
			fi
			;;
		*)
			echo "Unknown archive format: " $i
			exit 1
			;;
	esac
done
fi
