module github.com/poly-auth/grpc-react-native/plugins/swift

go 1.16

replace github.com/poly-auth/grpc-react-native/lib/generator => ../../lib/generator

require (
	github.com/poly-auth/grpc-react-native/lib/generator v0.0.0-00010101000000-000000000000
	google.golang.org/protobuf v1.27.1
)
