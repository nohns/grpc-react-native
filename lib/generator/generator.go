package generator

import (
	"github.com/poly-auth/grpc-react-native/lib/generator/printer"
	"google.golang.org/protobuf/compiler/protogen"
)

// Takes a protogen file and returns a generator
func FromProtogenFile(f *protogen.File) *fileGenerator {
	filename := f.GeneratedFilenamePrefix + ".grpc_rn.swift"

	return &fileGenerator{
		filename: filename,
		Printer:  printer.New(nil),
	}
}

type fileGenerator struct {
	Printer  *printer.FilePrinter
	filename string
}

// Generate complete file
func (g *fileGenerator) Generate() {

}

// Add partials to main file
func (g *fileGenerator) AppendPartial(partials ...PartialGeneratorBehavior) {
	for _, p := range partials {
		g.Printer.Append(p.ToBuffer())
	}
}

// Short-hand: Print indented line to file buffer
func (g *fileGenerator) P(elms ...interface{}) {
	g.Printer.P(elms...)
}
