plugins:
	make plugin-swift && make plugin-java && make plugin--js

plugin-swift:
	cd ./plugins/swift && go build -o ../../bin/protoc-gen-rn-grpc-swift 

plugin-java:
	cd ./plugins/java && go build -o ../../bin/protoc-gen-rn-grpc-java 

plugin-js:
	cd ./plugins/js && go build -o ../../bin/protoc-gen-rn-grpc-js 