package partials

import (
	gen "github.com/poly-auth/grpc-react-native/lib/generator"
)

// Create a new partial containing all client code
func NewClient() *clientPartial {
	partial := &clientPartial{}
	partial.Init(nil)

	return partial
}

func (cp clientPartial) Gen() {

}

type clientPartial struct {
	gen.PartialGenerator
}
