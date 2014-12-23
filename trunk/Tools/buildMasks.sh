#!/bin/bash

images="Bullet.png Frighty.png Gordy.png Killy.png Melon.png"
directoryPathNormalDPI="../Resources/NormalDPI/"
directoryPathHiDPI="../Resources/HiDPI/"


for image in $images
do
	imagePathNormalDPI="$directoryPathNormalDPI$image"
	imagePathHiDPI="$directoryPathHiDPI$image"

	maskPathNormalDPI="$imagePathNormalDPI.mask"
	maskPathHiDPI="$imagePathHiDPI.mask"

	printf "Building mask $image.mask... "
	python MaskBuilder/MaskBuilder.py --output $maskPathNormalDPI $imagePathNormalDPI
	cp $maskPathNormalDPI $maskPathHiDPI
	echo " ...done"
done
