import scala.collection.mutable.ArrayBuffer

object netconnections {
	val ORIG_SUBNET_ID_FLAG:Int = 0x80000000
	val SUBNET_ID_MASK:Int = 0x7fffffff
	val nodeInfo = new ArrayBuffer[Int](nNodes+1)
	var y:Int = 0
	var n:Int = 0

	def getSubNetId(i:Int):Int = {
		if ((nodeInfo(i) & SUBNET_ID_MASK) == i) {
			return i
		} else {
			nodeInfo(i) = getSubNetId(nodeInfo(i) & SUBNET_ID_MASK)
			return nodeInfo(i)
		}
	}

	def main(args: Array[String]) {
		val lines = io.Source.fromFile(args(0),"utf-8").getLines
		val nNodes:Int = (lines.next).split("$")(0).toInt
		nodeInfo = new ArrayBuffer[Int](nNodes+1)
		for (i <- 0 until nNodes+1) {
			nodeInfo += 0
		}
		while(lines.hasNext) {
			val strParts = lines.next.split(" ")
			val isConnData:Boolean = strParts(0) == "c"
			val n1:Int = strParts(1).toInt
			val n2:Int = strParts(2).split("$")(0).toInt

			if (isConnData) {
				if ((nodeInfo(n1) != 0) && (nodeInfo(n2) != 0)) {
					val v1:Int = getSubNetId(n1)
					val v2:Int = getSubNetId(n2)
					if (v1 != v2) {
						nodeInfo(n2) = v1
						nodeInfo(v2) = v1
					}
				} else if ((nodeInfo(n1) != 0) || (nodeInfo(n2) != 0)) {
					if (nodeInfo(n1) != 0) {
						nodeInfo(n2) = getSubNetId(n1)
					} else {
						nodeInfo(n1) = getSubNetId(n2)
					}
				} else {
					nodeInfo(n2) = n1;
					nodeInfo(n1) = n1 | ORIG_SUBNET_ID_FLAG;
				}
			} else if ((nodeInfo(n1) != 0) && (nodeInfo(n2) != 0) && (getSubNetId(n1) == getSubNetId(n2))) {
				y = y + 1
			} else {
				n = n + 1
			}
		}
		print(y+","+n+"\n")
	}
}
