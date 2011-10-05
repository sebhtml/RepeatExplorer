#!/usr/bin/python

import sys

file=sys.argv[1]

print "create table repeats (chromosome varchar(255),position integer,repeatWord varchar(255),twinWord varchar(255),copyNumber integer);"
print "create index i1 on repeats(chromosome);"
print "create index i2 on repeats(position);"
print "create index i3 on repeats(repeatWord);"
print "create index i4 on repeats(twinWord);"

print "begin;"

for line in open(file):
	tokens=line.split()
	print "insert into repeats (chromosome,position,repeatWord,twinWord,copyNumber) values ('"+tokens[0]+"',"+tokens[1]+",'"+tokens[2]+"','"+tokens[3]+"',"+tokens[4]+");"

print "commit;"
