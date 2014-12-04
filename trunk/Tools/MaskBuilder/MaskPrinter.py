import argparse
import sys
from MaskBuilder import toBinaryArray
from MaskBuilder import toInteger

debug = 0

def readFileBytes(filename):
	f = open(filename, "rb")
	characters = []
	try:
		byte = f.read(1)
		while byte != "":
			characters.append(ord(byte))
			byte = f.read(1)
	finally:
		f.close()
	return characters

if __name__ == "__main__":

	parser = argparse.ArgumentParser()
	parser.add_argument("mask", help="The path of the mask file to print. The file has to have been generated with the MaskBuilder.py tool.")
	parser.add_argument("-d", "--debug", help="If set to true, some debugging messages will be displayed. 0 by default", default=0, type=int)

	args = parser.parse_args()
	maskFile = args.mask
	debug = args.debug

	mask = readFileBytes(maskFile)

	if debug:
		print("Width bits:");
		bits = []
		for i in xrange(0, 2):
			bits.append(mask[i])
		print bits
		
		print("Height bits:");
		bits = []
		for i in xrange(2, 4):
			bits.append(mask[i])
		print bits

	imageWidth = mask[0]*256 + mask[1]
	imageHeight = mask[2]*256 + mask[3]

	if debug:
		print("Image size is {},{}").format(imageWidth, imageHeight)
		print mask

	dataOffset = 4

	data = []
	for x in xrange(dataOffset, len(mask)):
		byte = mask[x]
		bits = toBinaryArray(byte, 8)
		if debug:
			print bits
		for i in reversed(bits):
			data.append(i)
	if debug:
		print ""
		print data
	n = 0
	for i in xrange(0, imageHeight):
		s = ""
		for j in xrange(0, imageWidth):
			s += "-" if data[n] == 0 else "*"
			n += 1
		print s