package generator

import (
	"bytes"

	"github.com/poly-auth/grpc-react-native/lib/generator/printer"
)

// Created from
type PartialGenerator struct {
	Printer *printer.FilePrinter
}

func (pg *PartialGenerator) Init(printerConf *printer.PrinterConfig) {
	pg.Printer = printer.New(printerConf)
}

func (pg *PartialGenerator) P(vals ...interface{}) {
	pg.Printer.P(vals...)
}

func (pg *PartialGenerator) PIndent(body func()) {
	pg.Printer.Indent()
	body()
	pg.Printer.Outdent()
}

func (pg *PartialGenerator) ToBuffer() bytes.Buffer {
	return pg.Printer.Buffer()
}

// Append sub partials to this partial
func (pg *PartialGenerator) AppendSubPartial(partials ...*PartialGeneratorBehavior) {
	for _, p := range partials {
		pg.Printer.Append((*p).ToBuffer())
	}
}

type PartialGeneratorBehavior interface {
	ToBuffer() bytes.Buffer
	Init(conf *printer.PrinterConfig)
	Gen()
}
