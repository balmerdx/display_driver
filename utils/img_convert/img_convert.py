import sys
import os.path
from PIL import Image

def toHiColor(r, g, b):
	r = r//8
	g = g//4
	b = b//8
	return b + g*32 + r*32*64


def writeImg16bit(name, image, prefix):
	image = image.convert('RGB')
	width, height = image.size

	f = open(name, "wt")
	print("const Bitmap16bit "+prefix+"img = {", file=f)
	print(str(width)+", " + str(height) + ", {", file=f)

	index = 0
	for y in range(height):
		for x in range(width):
			r, g, b = image.getpixel((x,y))
			s = toHiColor(r, g, b)
			if index%16==15:
				print(hex(s)+",", file=f)
			else: 
				print(hex(s)+",", end="", file=f)
			index+=1

	print("}};", file=f)
	f.close()
	pass

def writeImg4bit(name, image, prefix):
	pal_size = 16
	image = image.convert('RGB').convert('P', palette=Image.ADAPTIVE, colors=pal_size)
	#image.save("logo_py.png", colors=255)
	width, height = image.size

	f = open(name, "wt")
	print("const Bitmap4bit "+prefix+"img = {", file=f)
	print(str(width)+", " + str(height) + ",", file=f)
	print("{", file=f, end='')

	pal = image.getpalette()
	for i in range(0, pal_size*3, 3):
		r,g,b = pal[i], pal[i+1], pal[i+2]
		#print(str(r)+"," + str(g) + ","+ str(b), file=f)
		print(hex(toHiColor(r,g,b))+", ", file=f, end='')
	print("}, {", file=f)

	for y in range(height):
		for x in range(0, (width+1)//2*2, 2):
			s = image.getpixel((x,y))
			if x+1<width:
				s += image.getpixel((x+1,y))*16
			s = hex(s)
			if len(s)==3:
				s = " "+s
			print(s+",", end="", file=f)
		print("", file=f)
	print("}};", file=f)

	f.close()
	pass

def main():
	if len(sys.argv)<2:
		print("Convert images to headers.")
		print("  img_convert.py [-c4 -c16] filename.png [filename.h]")
		print("  -c4 4 bit image (default)")
		print("  -c16 16 bit image")

	start_idx = 1
	use_4_bit = True
	if len(sys.argv)>2:
		c = sys.argv[1]
		if c[0] == '-':
			start_idx = start_idx+1
			if c == '-c4':
				use_4_bit = True
			if c == '-c16':
				use_4_bit = False

	filename = sys.argv[start_idx]
	hname = os.path.splitext(filename)[0]+'.h'

	if len(sys.argv) > start_idx+1:
		hname = sys.argv[start_idx+1]

	name = os.path.splitext(os.path.basename(hname))[0]
	img = Image.open(filename)
	if img==None:
		return
	print(img.size[0], "x", img.size[1])
	prefix = name+"_"
	if use_4_bit:
		writeImg4bit(hname, img, prefix)
	else:
		writeImg16bit(hname, img, prefix)
	pass


if __name__ == "__main__":
	main()
