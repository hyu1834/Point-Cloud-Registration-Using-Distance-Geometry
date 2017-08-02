#!/bin/bash


system_platform=$(uname)
distribution_name=$(lsb_release -is)
release_version=$(lsb_release -rs)

# if the linux distribution is LINUX
if [ "$system_platform" = "Linux" ]
then
	# check whether the distribution is Ubuntu
	if [ "$distribution_name" = "Ubuntu" ]
	then
		# First make sure everything is up to date
		sudo apt-get -y update
		sudo apt-get -y upgrade
		# install dependencies
		sudo apt-get install -y doxygen
		sudo apt-get install -y texlive-full
		# check what version of ubuntu version is it
		echo "System detected: $distribution_name-$release_version"
		if [ "$release_version" = "16.04" ]
		then
			echo "16.04"
	    elif [ "$release_version" = "14.04" ]
	    then
	    	echo "14.04"
	    fi


	    sudo ldconfig
	fi
elif [ "$system_platform" = "Darwin" ]
then
	echo "OSX"
else
	echo "Window"
fi

