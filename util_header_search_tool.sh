#!/bin/sh
set -e
DATADIR=$(cd $(dirname $0) && pwd)
HEADERDIR=$(cd $(dirname $0) && cd util && pwd)

defineLineToGUID() {
	sed -n 's/[#]ifndef INCLUDED_.*_GUID_\(.*\)$/\1/p' $@
}

[ -e ${DATADIR}/guid.list.txt -a -e ${DATADIR}/guid.transforms.txt ] || $0 --update

if [ "x$1" = "x--update" ]; then
	echo "Updating GUID databases."
	(
		cd ${HEADERDIR}
		# Generate file to use with sed
		grep "#ifndef INCLUDED_" *.h | defineLineToGUID | sed 's/\([^:]*\):\(.*\)/s:\2:\1:/' > ${DATADIR}/guid.transforms.txt
		# Generate input for grep
		defineLineToGUID *.h > ${DATADIR}/guid.list.txt
	)
	 
	exit 0
fi

grep -F -f ${DATADIR}/guid.list.txt $@ | defineLineToGUID | sed -f ${DATADIR}/guid.transforms.txt | sed 's/:/\t/'
