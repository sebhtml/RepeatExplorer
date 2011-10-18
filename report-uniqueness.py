#!/usr/bin/python

# report uniqueness of a genome
# also known as mappability

import sys

if len(sys.argv) != 2:
	print "Provide a file"
	sys.exit()

file=sys.argv[1]

genomeWide={}
frequencies={}
lastChromosome=None

def dumpFrequencies(name,frequencies):
	print name 

	total=0
	for i in frequencies.items():
		count=i[1]
		total += count

	keys=frequencies.keys()
	keys.sort()

	for i in keys:
		copies=i
		
		count=frequencies[copies]
		ratio=(0.0+count)/total*100
		print str(copies)+"	"+str(count)+"	"+str(ratio)+"%"
	frequencies.clear()

for line in open(file):
	tokens=line.split()
	copies=int(tokens[4])
	chromosome=tokens[0]
	
	if lastChromosome!=None and chromosome!=lastChromosome:
		dumpFrequencies(lastChromosome,frequencies)

	if copies not in frequencies:
		frequencies[copies] = 0
	frequencies[copies] += 1

	if copies not in genomeWide:
		genomeWide[copies] = 0
	genomeWide[copies] += 1

	lastChromosome = chromosome

dumpFrequencies(lastChromosome,frequencies)
dumpFrequencies("Genome-wide",genomeWide)


