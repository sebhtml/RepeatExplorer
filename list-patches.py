#!/usr/bin/python

import sys

file=sys.argv[1]
minimumLength=int(sys.argv[2])

# psu|Lmjchr31    92458   GGCGGTTCATCACAGGCGCCT   AGGCGCCTGTGATGAACCGCC   2

currentChromosome=None
currentStart=None
previousCopies=None
lastEnd=None

for line in open(file):
	tokens=line.split()
	chromosome=tokens[0]
	position=int(tokens[1])
	copies=int(tokens[4])

	if previousCopies==None and copies > 1:
		currentStart=position
	else:
		if previousCopies==1 and copies > 1:
			# a patch starts here
			currentStart=position
		elif previousCopies > 1 and copies == 1 and currentStart!=None:
			# a patch ends at position-1
			theLength=(position-1)-currentStart+1
			if theLength >= minimumLength:
				print "Repeat from "+str(currentStart)+" to "+str(position-1)+" with length "+str(theLength),
				if lastEnd!=None:
					print " distance from previous: "+str(currentStart-lastEnd)
				else:
					print ""
				lastEnd=position-1

	previousCopies=copies
