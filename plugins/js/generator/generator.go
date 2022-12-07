package generator

import (
	"github.com/nohns/grpc-react-native/plugins/js/partials"
	"github.com/nohns/grpc-react-native/plugins/js/printer"
	"google.golang.org/protobuf/compiler/protogen"
)

// Takes a protogen file and returns a generator
func FromProtogenFile(f *protogen.File) *fileGenerator {
	filename := f.GeneratedFilenamePrefix + ".grpc_rn.hex"

	return &fileGenerator{
		f:        f,
		filename: filename,
		Printer:  printer.New(nil),
	}
}

type fileGenerator struct {
	f        *protogen.File
	Printer  *printer.FilePrinter
	filename string
}

// Generate complete file
func (g *fileGenerator) Generate() error {
	return nil
}

// Add partials to main file
func (g *fileGenerator) AppendPartial(partials ...partials.PartialGeneratorBehavior) {
	for _, p := range partials {
		g.Printer.Append(p.ToBuffer())
	}
}

// Short-hand: Print indented line to file buffer
func (g *fileGenerator) P(elms ...interface{}) {
	g.Printer.P(elms...)
}
