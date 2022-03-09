#! /bin/bash

###
# Macro define

# The swap file/partition size should be equal to the whole size of remote memory
SWAP_PARTITION_SIZE="48G"

# Cause of sudo, NOT use ${HOME}
home_dir="/mnt/ssd/yifan"
swap_file="${home_dir}/swapfile"
connect_exe="syscaller"
leap_ko="leap_functionality.ko"

##
# Do the action

action=$1
if [ -z "${action}" ]
then
	echo "This shellscipt for Infiniswap pre-configuration."
	echo "Run it with sudo or root"
	echo ""
	echo "Pleaes slect what to do: [install | create (create swapfile) | use-leap | use-kernel-default | add-pid | uninstall]"

	read action
fi

if [ -z "${home_dir}"  ]
then
	echo " Warning : home_dir is null."
fi

## self defined function
function close_swap_partition () {
	swap_bd=$(swapon -s | grep "dev" | cut -d " " -f 1 )

	if [ -z "${swap_bd}" ]
	then
		echo "Nothing to close."
	else
		echo "Swap Partition to close :${swap_bd} "
		sudo swapoff "${swap_bd}"
	fi

	#check
	echo "Current swap partition:"
	swapon -s
}


function create_swap_file () {
	if [ -e ${swap_file} ]
	then
		echo "Please confirm the size of swapfile match the expected ${SWAP_PARTITION_SIZE}"
		cur_size=$(du -sh ${swap_file} | awk '{print $1;}' )
		if [ "${cur_size}" != "${SWAP_PARTITION_SIZE}" ]
		then
			echo "Current ${swap_file} : ${cur_size} NOT equal to expected ${SWAP_PARTITION_SIZE}"
			echo "Delete it"
			sudo rm ${swap_file}

			echo "Create a file, ~/swapfile, with size ${SWAP_PARTITION_SIZE} as swap device."
			sudo fallocate -l ${SWAP_PARTITION_SIZE} ${swap_file}
			sudo chmod 600 ${swap_file}
		fi
	else
		# not exit, create a swapfile
		echo "Create a file, ~/swapfile, with size ${SWAP_PARTITION_SIZE} as swap device."
		sudo fallocate -l ${SWAP_PARTITION_SIZE} ${swap_file}
		sudo chmod 600 ${swap_file}
		du -sh ${swap_file}
	fi

	sleep 1
	echo "Mount the ${swap_file} as swap device"
	sudo mkswap ${swap_file}
	sudo swapon ${swap_file}

	# check
	swapon -s
}



function connect_to_server () {
	if [ -z "${connect_exe}" ]
	then
		echo "Compile the connect syscall"
		gcc syscaller.c -o syscaller
	fi

	# Connect to memory server
	echo "${connect_exe}"
	`${connect_exe}`
}


if [ "${action}" = "install" ]
then
	echo "Close current swap partition && Create swap file"
	close_swap_partition

	create_swap_file

	connect_to_server

elif [ "${action}" = "create" ]
then
	echo "Close current swap partition && Create swap file"
	close_swap_partition

	create_swap_file

elif [ "${action}" = "use-leap" ]
then
  echo "Use the leap prefetcher"
  sudo insmod ${leap_ko} cmd="prefetch" && sudo rmmod ${leap_ko}


elif [ "${action}" = "use-kernel-default" ]
then
  echo "Use the kernel default prefetcher"
  sudo insmod ${leap_ko} cmd="readahead" && sudo rmmod ${leap_ko}


elif [ "${action}" = "add-pid" ]
then
  echo "Add the application to Leap"
  sudo insmod ${leap_ko} process_name="java" cmd="init" && sudo rmmod ${leap_ko}

elif [ "${action}" = "uninstall" ]
then
	echo "Close current swap partition"
	close_swap_partition

	# echo "rmmod rswap-client"
	# sudo rmmod rswap-client

else
	echo "!! Wrong choice : ${action}"
fi
