ORIG_SUBNET_ID_FLAG = 0x80000000;
SUBNET_ID_MASK = 0x7fffffff;
y=0
n=0
lines = readFile(arguments[0]).split("\n");
lines.pop()
nNodes = parseInt(lines[0])
nodeInfo = new Array(nNodes+1)
for (var i=1; i <= nNodes; ++i) {
	nodeInfo[i] = 0;
}

function getSubNetId(i) {
    return ((nodeInfo[i] & SUBNET_ID_MASK) == i) ? i : nodeInfo[i] = getSubNetId(nodeInfo[i] & SUBNET_ID_MASK);
}

for (var i=1; i < lines.length; ++i) {
	var isConnData = (lines[i][0] == 'c');
	var n1 = parseInt(lines[i].substring(2));
	var n2 = parseInt(lines[i].substring(lines[i].indexOf(' ',3) + 1));
	if (isConnData) {
		if ((nodeInfo[n1] != 0) && (nodeInfo[n2] != 0)) {
			var v1 = getSubNetId(n1);
            var v2 = getSubNetId(n2);
            if (v1 != v2) {
                nodeInfo[n2] = v1;
                nodeInfo[v2] = v1;
			}
		} else if ((nodeInfo[n1] != 0) || (nodeInfo[n2] != 0)) {
			if (nodeInfo[n1] != 0)
				nodeInfo[n2] = getSubNetId(n1);
			else
				nodeInfo[n1] = getSubNetId(n2);
		} else {
			nodeInfo[n2] = n1;
            nodeInfo[n1] = n1 | ORIG_SUBNET_ID_FLAG;
		}
	} else if ((nodeInfo[n1] != 0 && nodeInfo[n2] != 0) && (getSubNetId(n1) == getSubNetId(n2))) {
		++y;
	} else {
		++n;
	}
}
print(y + "," + n)
