LDFLAGS := -lGL -lGLEW -lglut -lSOIL -ggdb

default: circle.png triangle.png square.png young.png

%.png: %.bmp
	convert $< $@

%.bmp: main %.glsl
	./main $(basename $@)

clean:
	rm -f main *.bmp *.png
