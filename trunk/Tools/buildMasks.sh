#!/bin/bash

images="Bullet.png Frighty.png Gordy.png Killy.png Melon.png"
directoriesPath="../Resources/"
directories="NormalDPI/ HiDPI/"

for image in $images
do
	for directory in $directories
	do
		imagePath="$directoriesPath$directory$image"
		maskPath="$imagePath.mask"

		printf "Building mask $directory$image.mask... "
		python MaskBuilder/MaskBuilder.py --output $maskPath $imagePath
		echo " ...done"
	done
done
