local ORIG_SUBNET_ID_FLAG = 0x80000000;
local SUBNET_ID_MASK = 0x7fffffff;

local y, n = 0, 0
local f = io.input(arg[1])
local nNodes = f:read("*number", 1)
local nodeInfo = {}
for i=1, nNodes do
  nodeInfo[i] = 0
end

function getSubNetId(i)
    if ((nodeInfo[i] % ORIG_SUBNET_ID_FLAG) == i) then
		return i
	else
		nodeInfo[i] = getSubNetId(nodeInfo[i] % ORIG_SUBNET_ID_FLAG)
		return nodeInfo[i]
	end
end

while true do
	local isConnData, n1, n2 = f:read(1, "*number", "*number", 1)
	if not isConnData then break end
	if isConnData == 'c' then
		if ((nodeInfo[n1] ~= 0) and (nodeInfo[n2] ~= 0)) then
			v1 = getSubNetId(n1)
            v2 = getSubNetId(n2)
            if (v1 ~= v2) then
                nodeInfo[n2] = v1
                nodeInfo[v2] = v1
			end
		elseif ((nodeInfo[n1] ~= 0) or (nodeInfo[n2] ~= 0)) then
			if (nodeInfo[n1] ~= 0) then
                nodeInfo[n2] = getSubNetId(n1)
            else
                nodeInfo[n1] = getSubNetId(n2)
			end
		else
			nodeInfo[n2] = n1
            nodeInfo[n1] = (n1 + ORIG_SUBNET_ID_FLAG)
		end
	elseif (((nodeInfo[n1] ~= 0) and (nodeInfo[n2] ~= 0)) and (getSubNetId(n1) == getSubNetId(n2))) then
		y = y + 1
	else
		n = n + 1
	end
end

print(string.format("%s,%s",y,n))

