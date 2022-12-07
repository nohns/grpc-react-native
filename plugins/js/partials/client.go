package partials

import (
	"bytes"

	"github.com/nohns/grpc-react-native/plugins/js/printer"
)

// Create a new partial containing all client code
func NewClient() *clientPartial {
	partial := &clientPartial{}
	partial.Init(nil)

	return partial
}

func (cp clientPartial) Gen() {

}

func (cp clientPartial) Init(conf *printer.PrinterConfig) {

}

func (cp clientPartial) ToBuffer() bytes.Buffer {
	return bytes.Buffer{}
}

type clientPartial struct {
	PartialGenerator
}
