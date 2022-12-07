package main

import (
	"encoding/hex"
	"fmt"
	"path"
	"path/filepath"
	"strings"

	"google.golang.org/protobuf/compiler/protogen"
	"google.golang.org/protobuf/proto"
	"google.golang.org/protobuf/reflect/protoreflect"
)

const (
	// Property names
	PropNameClient = "client"
	PropNameProto  = "proto"

	// Method parameters
	ParamNameData   = "data"
	ParamTargetName = "target"

	// Type names
	TypeClient       = "Client"
	TypeChannelCreds = "ChannelCredentials"

	// Spacing
	IndentSpace2 = "  "
)

func main() {
	protogen.Options{}.Run(func(p *protogen.Plugin) error {
		for _, f := range p.Files {
			if !f.Generate {
				continue
			}

			// Create file
			gf := NewGenGrpcrnFile(p, f, true)
			if err := gf.Gen(); err != nil {
				return err
			}
		}
		return nil
	})
}

type genGrpcrnFile struct {
	p  *protogen.Plugin
	f  *protogen.File
	g  *protogen.GeneratedFile
	gt *protogen.GeneratedFile

	currIndent  int
	currTIndent int
	indentSpace string
	fileName    string
}

func NewGenGrpcrnFile(p *protogen.Plugin, f *protogen.File, types bool) *genGrpcrnFile {

	protoFileName := strings.TrimSuffix(path.Base(*f.Proto.Name), filepath.Ext(*f.Proto.Name))
	protoGenPath := path.Dir(*f.Proto.Name) + "/" + protoFileName

	gf := &genGrpcrnFile{
		p: p,
		f: f,
		g: p.NewGeneratedFile(protoGenPath+".grpcrn.js", ""),

		indentSpace: IndentSpace2,
		fileName:    protoFileName,
	}
	if types {
		gf.gt = p.NewGeneratedFile(protoGenPath+".grpcrn.d.ts", "")
	}

	return gf
}

func (gf *genGrpcrnFile) Gen() error {

	// Imports
	gf.printNamedImport([]string{TypeClient, TypeChannelCreds}, "grpc-react-native")

	// Go through all services and add them to the output
	srvDescs := gf.f.Desc.Services()
	for i := 0; i < srvDescs.Len(); i++ {
		srvDesc := srvDescs.Get(i)
		if err := gf.printService(srvDesc); err != nil {
			return err
		}
	}

	// Generate types for protobufs
	if gf.gt != nil {
		msgDescs := gf.f.Desc.Messages()
		for i := 0; i < msgDescs.Len(); i++ {
			msgDesc := msgDescs.Get(i)
			if err := gf.printMessageTypeDecl(msgDesc); err != nil {
				return err
			}
		}
	}

	return nil
}

func (gf *genGrpcrnFile) printMessageTypeDecl(msgDesc protoreflect.MessageDescriptor) error {
	fieldDescs := msgDesc.Fields()

	fields := make(map[string]string, fieldDescs.Len())

	extractType := func(fd protoreflect.FieldDescriptor) {

	}

	for i := 0; i < fieldDescs.Len(); i++ {
		fieldDesc := fieldDescs.Get(i)

		switch fieldDesc.Kind() {
		case protoreflect.Int32Kind, protoreflect.Uint32Kind, protoreflect.Sint32Kind, protoreflect.Fixed32Kind:
			// Number
			fields[fieldDesc.JSONName()] = "number"
			break

		case protoreflect.Int64Kind, protoreflect.Uint64Kind, protoreflect.Sint64Kind, protoreflect.Fixed64Kind:
			// String formatted number
			fields[fieldDesc.JSONName()] = "string"
			break

		case protoreflect.FloatKind, protoreflect.DoubleKind:
			// Number
			fields[fieldDesc.JSONName()] = "number"
			break

		case protoreflect.StringKind:
			// String
			fields[fieldDesc.JSONName()] = "string"
			break

		case protoreflect.BoolKind:
			// Boolean
			fields[fieldDesc.JSONName()] = "boolean"

		case protoreflect.BytesKind:
			// Boolean
			fields[fieldDesc.JSONName()] = "ArrayBuffer"

		}
	}

	gf.printInterfaceDecl(string(msgDesc.Name()), []string{})

	return nil
}

func (gf *genGrpcrnFile) printInterfaceDecl(name string, props map[string]string) {

	gf.TP("declare interface ", name, " {")
	gf.indent(true)

	for p, pt := range props {
		gf.TP(p, ": ", pt, ";")
	}

	gf.outdent(true)
	gf.TP("}")
}

func (gf *genGrpcrnFile) printService(srvDesc protoreflect.ServiceDescriptor) error {
	mtdDescs := srvDesc.Methods()

	// Get Uint8Array representation of buffer
	protoVal, err := gf.printProtoDescBuf()
	if err != nil {
		return err
	}

	// Define class
	clsName := srvDesc.Name() + "Client"
	gf.P("export class ", clsName, " extends ", TypeClient, " {")
	gf.TP("declare class ", clsName, " extends ", TypeClient, " {")
	gf.indent(true)

	// Define properties
	gf.printProperty(PropNameProto, protoVal, &propertyOpts{
		typ:                "Uint8Array",
		nameTypeOnlyPrefix: "private",
	})

	// Define constructor
	paramNameTarget := "target"
	paramNameChanCreds := "channelCredentials"
	gf.printClassMethod("constructor", []string{paramNameTarget, paramNameChanCreds}, []string{
		"super(" + paramNameTarget + ", " + paramNameChanCreds + ", this." + PropNameProto + ".buffer);",
	}, &classMethodOpts{
		parameterTypes: []string{
			"string",
			TypeChannelCreds,
		},
	})

	// Go through all methods and add them to the output
	for i := 0; i < mtdDescs.Len(); i++ {
		mtdDesc := mtdDescs.Get(i)
		if err := gf.printRpcMethod(string(srvDesc.Name()), mtdDesc); err != nil {
			return err
		}
	}

	// Print ending parenthesis
	gf.outdent(true)
	gf.P("}")
	gf.TP("}")

	return nil
}

func (gf *genGrpcrnFile) printRpcMethod(svcName string, mtdDesc protoreflect.MethodDescriptor) error {
	mtdName := "/" + gf.fileName + "." + svcName + "/" + string(mtdDesc.Name())

	switch {
	case !mtdDesc.IsStreamingClient(), !mtdDesc.IsStreamingServer(): // Unary request
		gf.printClassMethod(string(mtdDesc.Name()), []string{"data"}, []string{
			"return this." + PropNameClient + ".makeUnaryCall('" + mtdName + "', data);",
		}, &classMethodOpts{
			async:      true,
			returnType: "Promise<" + string(mtdDesc.Output().Name()) + ">",
			parameterTypes: []string{
				string(mtdDesc.Input().Name()),
			},
		})
	}

	return nil
}

// Increase amount of indentation when printing
func (gf *genGrpcrnFile) indent(inclTypes bool) {
	gf.currIndent++
	if inclTypes {
		gf.currTIndent++
	}
}

// Decrease amount of indentation when printing
func (gf *genGrpcrnFile) outdent(inclTypes bool) {
	gf.currIndent--
	if inclTypes {
		gf.currTIndent--
	}
}

// Wrapper method for print function of js files
func (gf *genGrpcrnFile) P(v ...interface{}) {

	// Prepend spaces to given values
	nv := v
	if gf.currIndent > 0 {
		nv = make([]interface{}, 0, len(v)+gf.currIndent)
		for i := 0; i < gf.currIndent; i++ {
			nv = append(nv, gf.indentSpace)
		}
		for _, vv := range v {
			nv = append(nv, vv)
		}
	}

	gf.g.P(nv...)
}

// Wrapper method for print function of d.ts file (type definitions)
func (gf *genGrpcrnFile) TP(v ...interface{}) {
	if gf.gt == nil {
		return
	}

	// Prepend spaces to given values
	nv := v
	if gf.currTIndent > 0 {
		nv = make([]interface{}, 0, len(v)+gf.currTIndent)
		for i := 0; i < gf.currTIndent; i++ {
			nv = append(nv, gf.indentSpace)
		}
		for _, vv := range v {
			nv = append(nv, vv)
		}
	}

	gf.gt.P(nv...)
}

type classMethodOpts struct {
	async          bool
	parameterTypes []string
	returnType     string
}

// Define class method
func (gf *genGrpcrnFile) printClassMethod(name string, params []string, bodyLines []string, opts *classMethodOpts) {
	// Create default options
	if opts == nil {
		pt := make([]string, 0, len(params))
		for i := 0; i < len(params); i++ {
			pt = append(pt, "any")
		}
		opts = &classMethodOpts{
			async:          false,
			parameterTypes: pt,
			returnType:     "any",
		}
	}
	// Is method async?
	funcDeclPrefix := ""
	if opts.async {
		funcDeclPrefix += "async "
	}
	// Generate typed params
	typedParams := make([]string, 0, len(params))
	for i, p := range params {
		t := opts.parameterTypes[i]
		typedParams = append(typedParams, p+": "+t)
	}
	// Generate return type, if not constructor
	returnType := ": " + opts.returnType
	if name == "constructor" {
		returnType = ""
	}

	gf.P(funcDeclPrefix, name, "(", strings.Join(params, ", "), ") {")
	gf.TP(name, "(", strings.Join(typedParams, ", "), ")", returnType, ";")
	gf.indent(false)

	gf.P(strings.Join(bodyLines, "\n"+gf.indentSpace+gf.indentSpace))

	gf.outdent(false)
	gf.P("}")
}

type propertyOpts struct {
	typ                string
	nameTypeOnlyPrefix string
}

func (gf *genGrpcrnFile) printProperty(name string, val string, opts *propertyOpts) {
	if opts == nil {
		opts = &propertyOpts{}
	}
	if opts.typ == "" {
		opts.typ = "any"
	}

	if val != "" {
		val = " = " + val
	}

	gf.P(name + val + ";")
	gf.TP(opts.nameTypeOnlyPrefix, " ", name+": "+opts.typ+";")
}

func (gf *genGrpcrnFile) printNamedImport(imports []string, from string) {
	gf.P("import {", strings.Join(imports, ", "), "} from '", from, "';")
	gf.TP("import type {", strings.Join(imports, ", "), "} from '", from, "';")
}

func (gf *genGrpcrnFile) printProtoDescBuf() (string, error) {
	indentSpace := ""
	for i := 0; i < gf.currIndent; i++ {
		indentSpace += gf.indentSpace
	}

	buf, err := proto.Marshal(gf.f.Proto)
	if err != nil {
		fmt.Println(err)
		return "", err
	}

	lineLen := 0
	byteChars := make([]string, 0, len(buf))
	for _, b := range buf {
		char := "0x" + hex.EncodeToString([]byte{b})

		if lineLen == 13 {
			char = "\n" + gf.indentSpace + indentSpace + char
			lineLen = 0
		}
		lineLen++

		byteChars = append(byteChars, char)
	}

	lines := "new Uint8Array(["
	gf.indent(false)
	lines += gf.indentSpace + indentSpace + strings.Join(byteChars, ", ")
	gf.outdent(false)
	lines += indentSpace + "]);"

	return lines, nil
}
