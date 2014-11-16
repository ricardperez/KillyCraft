import os, sys
from PIL import Image

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

def buildImageMask(imageName, byteSize, bitsForWidth, bitsForHeight):
	image = Image.open(imageName)
	imageData = image.load()

	imageWidth = image.size[0]
	imageHeight = image.size[1]

	mask = []

	mask.extend(toBinaryArray(imageWidth, bitsForWidth))
	mask.extend(toBinaryArray(imageHeight, bitsForHeight))

	bitWeight = [1]
	for x in xrange(1,byteSize):
		bitWeight.append(bitWeight[x-1]*2)

	nextChunkSize = 0
	nextByte = 0;

	for j in xrange(0,image.size[1]):
		for i in xrange(0, image.size[0]):
			alpha = imageData[i,j][3]
			bit = (0 if (alpha == 0) else 1)
			nextByte += (bit * bitWeight[nextChunkSize])
			nextChunkSize += 1
			if (nextChunkSize == byteSize):
				mask.append(nextByte)
				nextChunkSize = 0
				nextByte = 0

	if nextChunkSize != 0:
		mask.append(nextByte)

	return mask

def buildTextFromBytes(bytes):
	characters = []
	for b in bytes:
		characters.append(chr(b))
	print characters
	result = ""
	result.join(characters)
	return result

if __name__ == "__main__":
	byteSize = 8
	bitsForWidth = 10
	bitsForHeight = 10
	mask = buildImageMask("/Users/ricardperez/Desktop/Bullet.png", byteSize, bitsForWidth, bitsForHeight)

	print "Mask calculated..."
	print mask

	imageWidth = toInteger(mask[0:bitsForWidth])
	imageHeight = toInteger(mask[bitsForWidth:bitsForWidth+bitsForHeight])

	text = buildTextFromBytes(mask)
	print "Mask text..."
	print text

	print("Image size is {},{}").format(imageWidth, imageHeight)

	dataOffset = bitsForWidth+bitsForHeight

	data = []
	for x in xrange(dataOffset, len(mask)):
		byte = mask[x]
		bits = toBinaryArray(byte, byteSize)
		for i in reversed(bits):
			data.append(i)
	n = 0
	for i in xrange(0, imageWidth):
		s = ""
		for j in xrange(0, imageHeight):
			s += "-" if data[n] == 0 else "*"
			n += 1
		print s
