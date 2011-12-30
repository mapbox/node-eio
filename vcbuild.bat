rm build.sln
python gyp/gyp build.gyp --depth=. -f msvs -G msvs_version=2010
msbuild build.sln
copy Default\\eio.node lib\\eio.node
rem test!
set NODE_PATH=lib
node node_modules\expresso\bin\expresso
rem node -e "console.log(require('eio'))"