#!/usr/bin/python
from sys import argv
from array import array
from itertools import repeat
from fileinput import input

ORIG_SUBNET_ID_FLAG = 0x80000000;
SUBNET_ID_MASK = ~ORIG_SUBNET_ID_FLAG;
y = 0
n = 0

def getSubNetId(i):
	if ((nodeInfo[i] & SUBNET_ID_MASK) == i):
		return i
	else:
		nodeInfo[i] = getSubNetId(nodeInfo[i] & SUBNET_ID_MASK);
		return nodeInfo[i]

fd = open(argv[1], "r")
nodeInfo = array('I',repeat(0, int(fd.readline()) + 1))
line = fd.readline()

while line:
	strIdx=line.find(' ',2);
	n1 = int(line[2:strIdx]);
	n2 = int(line[strIdx+1:len(line)]);
	if (line[0] == 'c'):
		if (nodeInfo[n1] != 0 and nodeInfo[n2] != 0):
			v1 = getSubNetId(n1);
			v2 = getSubNetId(n2);
			if (v1 != v2):
				nodeInfo[n2] = v1;
				nodeInfo[v2] = v1;
		elif (nodeInfo[n1] != 0 or nodeInfo[n2] != 0):
			if (nodeInfo[n1] != 0):
				nodeInfo[n2] = getSubNetId(n1);
			else:
				nodeInfo[n1] = getSubNetId(n2);
		else:
			nodeInfo[n2] = n1;
			nodeInfo[n1] = n1 | ORIG_SUBNET_ID_FLAG;
	elif (nodeInfo[n1] != 0 and nodeInfo[n2] != 0 and (getSubNetId(n1) == getSubNetId(n2))):
		y += 1;
	else:
		n += 1;
	line = fd.readline()
print `y`+","+`n`;
