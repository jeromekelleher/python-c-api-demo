all: consumer.cpython-35m-x86_64-linux-gnu.so demo.cpython-35m-x86_64-linux-gnu.so

consumer.cpython-35m-x86_64-linux-gnu.so: consumermodule.c
	python3 setup.py build_ext -i

demo.cpython-35m-x86_64-linux-gnu.so: demomodule.c
	python3 setup.py build_ext -i

clean:
	rm -fR build *.so 
