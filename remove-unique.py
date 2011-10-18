#!/usr/bin/python

import sys

file=sys.argv[1]

for line in open(file):
	if line.split()[4]!="1":
		print line,
