function fsize (file)
  local current = file:seek()      -- get current position
  local size = file:seek("end")    -- get file size
  file:seek("set", current)        -- restore position
  return size
end
function min (a, b)
  if a < b then return a else return b end
end

local resultString = {"1","2","draw","play"}
local returnCode = 3
local f = io.input(arg[1])
local readOffset = fsize(f)
local BUFFER_SZ = 4096
local numReadCycles = math.floor(readOffset / BUFFER_SZ)
f:seek("set", readOffset - min(BUFFER_SZ, readOffset))
local currentRowIdx = 2
local rdBuf = f:read(min(BUFFER_SZ, readOffset))
local rdPtr = string.len(rdBuf) - 1
local startPtr = string.find(rdBuf, "\n")
local cols = string.find(string.sub(rdBuf, startPtr + 1), "\n") / 2
readOffset = readOffset - min(BUFFER_SZ, readOffset)
local ew, sn, swne, senw = {}, {}, {}, {}
senw[1] = {}
senw[2] = {}
for idx=1,cols+1 do
    ew[idx] = 0
    sn[idx] = 0
    swne[idx] = 0
    senw[1][idx] = 0
    senw[2][idx] = 0
end

repeat
	while rdPtr > startPtr do
		currentRowIdx = 3 - currentRowIdx
		local i = cols + 1
		local value = string.byte(rdBuf, rdPtr) - 48
		ew[i] = value
		sn[i] = value
		swne[i] = value
		senw[currentRowIdx][i] = value

		while i ~= 2 do
			i = i - 1
			rdPtr = rdPtr - 2
			value = string.byte(rdBuf, rdPtr) - 48
			if value > 0 then
				ew[i] = (ew[i + 1] * 4) + value
				sn[i] = (sn[i] * 4) + value
				swne[i] = (swne[i - 1] * 4) + value
				senw[currentRowIdx][i] = (senw[3-currentRowIdx][i + 1] * 4) + value
				if ew[i] == 0x55 or ew[i] == 0xaa or sn[i] == 0x55 or sn[i] == 0xaa or swne[i] == 0x55 or swne[i] == 0xaa or senw[currentRowIdx][i] == 0x55 or senw[currentRowIdx][i] == 0xaa then 
					print(resultString[value])
					os.exit(0)
				end
			else
				ew[i] = 0
				sn[i] = 0
				swne[i] = 0
				senw[currentRowIdx][i] = 0;
				returnCode = 4
			end
		end
		rdPtr = rdPtr - 2
	end
	readOffset = readOffset - min(BUFFER_SZ - startPtr, readOffset)
	f:seek("set", readOffset)
	local tmpStr = string.sub(rdBuf, 1, startPtr)
	rdBuf = f:read(min(BUFFER_SZ - startPtr, readOffset)) .. tmpStr
	rdPtr = string.len(rdBuf) - 1
	startPtr = string.find(rdBuf, "\n")
	numReadCycles = numReadCycles - 1
until numReadCycles ~= 0
print(resultString[returnCode])

