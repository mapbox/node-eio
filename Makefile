build:
	node-waf build


test:
	@NODE_PATH=./lib:$NODE_PATH node_modules/.bin/expresso

gyp:
	rm -rf ./tmp/makefiles/
	python gyp/gyp build.gyp --depth=. -f make --generator-output=./tmp/makefiles
	make -C ./tmp/makefiles/ V=1
	cp tmp/makefiles/out/Default/eio.node lib/eio.node

.PHONY: build test gyp
