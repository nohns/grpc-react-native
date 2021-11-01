plugins:
	${MAKE} plugin-swift
	${MAKE} plugin-java
	${MAKE} plugin-js

plugin-swift:
	@${MAKE} plugin NAME=swift

plugin-java:
	@${MAKE} plugin NAME=java

plugin-js:
	@${MAKE} plugin NAME=js

plugin: 
	@cd ./plugins/${NAME} && go build -o ../../bin/protoc-gen-rn-grpc-${NAME}
	@echo "Finshed building protoc-gen-rn-grpc-${NAME}"
