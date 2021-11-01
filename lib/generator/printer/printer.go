package printer

import (
	"bufio"
	"bytes"
	"fmt"
)

// Configure printer with options of this structs
type PrinterConfig struct {
	indentStep int
}

type FilePrinter struct {
	buf    *bytes.Buffer
	indent int
	conf   *PrinterConfig
}

// Print a line to the file. The line will have the indentation of the current set indent
func (p *FilePrinter) P(content ...interface{}) {
	// Pad line with current indentation
	fmt.Fprint(p.buf, p.genIdent())

	// Write content
	fmt.Fprint(p.buf, content...)

	// Write newline
	fmt.Fprintln(p.buf)
}

// Add one indentation level to the content
func (p *FilePrinter) Indent() {
	p.indent++
}

// Remove one indentation level of the content
func (p *FilePrinter) Outdent() {
	if p.indent > 0 {
		p.indent--
	}
}

func (p *FilePrinter) PrintBlock(body func()) {
	p.Indent()
	body()
	p.Outdent()
}

func (p *FilePrinter) Append(content bytes.Buffer) {

	// Print each line of buffer into this printer
	s := bufio.NewScanner(bytes.NewReader(content.Bytes()))
	for s.Scan() {
		p.P(s.Text())
	}
}

// Get the printed file as bytes
func (p *FilePrinter) Buffer() bytes.Buffer {
	return *p.buf
}

func (p *FilePrinter) genIdent() string {
	var indent string
	spaceCount := p.indent * p.conf.indentStep
	for i := 0; i < spaceCount; i++ {
		indent += " "
	}

	return indent
}

// Create new file printer. Supports auto indentation, and print short hands
func New(conf *PrinterConfig) *FilePrinter {
	if conf == nil {
		conf = &PrinterConfig{
			indentStep: 4,
		}
	}

	return &FilePrinter{
		buf:  new(bytes.Buffer),
		conf: conf,
	}
}
