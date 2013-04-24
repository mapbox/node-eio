build:
	npm install

clean:
	rm -rf build
	rm -f lib/eio.node

test:
	npm test

.PHONY: build test clean
