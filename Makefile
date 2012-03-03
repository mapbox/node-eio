build:
	node-waf build


test:
	@NODE_PATH=./lib:$NODE_PATH node_modules/.bin/expresso

.PHONY: build test
