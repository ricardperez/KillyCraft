import os, sys
from PIL import Image
import argparse

debug = 0

def toBinaryArray(number, nBits):
    bits = [0] * nBits
    n = number
    for x in xrange(0,nBits):
    	index = nBits-x-1
    	bits[index] = (n % 2)
    	n = n / 2
    return bits

def toInteger(bits):
	number = 0
	base = 1
	for b in reversed(bits):
		number += base if b == 1 else 0
		base *= 2
	return number

def buildImageMask(imageName, alphaThreshold):
	image = Image.open(imageName)
	imageData = image.load()

	imageWidth = image.size[0]
	imageHeight = image.size[1]

	mask = []

	bitsWidth = toBinaryArray(imageWidth, 16)
	bitsHeight = toBinaryArray(imageHeight, 16)
	mask.append(toInteger(bitsWidth[0:8]))
	mask.append(toInteger(bitsWidth[8:16]))
	mask.append(toInteger(bitsHeight[0:8]))
	mask.append(toInteger(bitsHeight[8:16]))

	if debug:
		print("After adding the image size: ({}, {})".format(imageWidth,imageHeight));
		print mask

	bitWeight = [1]
	for x in xrange(1,8):
		bitWeight.append(bitWeight[x-1]*2)

	nextChunkSize = 0
	nextByte = 0;

	for j in xrange(0,image.size[1]):
		for i in xrange(0, image.size[0]):
			alpha = imageData[i,j][3]
			bit = (1 if (alpha >= alphaThreshold) else 0)
			if debug:
				print("({}, {}) -> {} ({})".format(i,j,bit,alpha))
			nextByte += (bit * bitWeight[nextChunkSize])
			nextChunkSize += 1
			if (nextChunkSize == 8):
				mask.append(nextByte)
				nextChunkSize = 0
				nextByte = 0

	if nextChunkSize != 0:
		mask.append(nextByte)

	return mask

def bytesToChars(bytes):
	characters = []
	for b in bytes:
		characters.append(chr(b))

	return characters

def writeCharsToFile(chars, fileName):
	f = open(fileName, "wb")
	for c in chars:
		f.write(c)
	f.close()


if __name__ == "__main__":

	parser = argparse.ArgumentParser()
	parser.add_argument("image", help="The path of the image to build the mask from.")
	parser.add_argument("-o", "--output", help="The path of the file to write the mask to. If not provided or empty, the std::out will be used.", default="")
	parser.add_argument("-t", "--threshold", help="The alpha threshold to consider a pixel transparent. The default value is 150.", default=150, type=int)
	parser.add_argument("-d", "--debug", help="If set to true, some debugging messages will be displayed. 0 by default", default=0, type=int)

	args = parser.parse_args()
	imageName = args.image
	outFile = args.output
	alphaThreshold = args.threshold
	debug = args.debug

	mask = buildImageMask(imageName, alphaThreshold)
	if debug:
		print mask

	chars = bytesToChars(mask)

	if len(outFile) > 0:
		writeCharsToFile(chars, outFile)
	else:
		s = ""
		for c in chars:
			s += c
		print s

