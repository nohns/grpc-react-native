package main

import (
	"fmt"

	"github.com/poly-auth/grpc-react-native/lib/generator"
	"github.com/poly-auth/grpc-react-native/plugins/swift/partials"
	"google.golang.org/protobuf/compiler/protogen"
)

func main() {
	protogen.Options{}.Run(func(p *protogen.Plugin) error {
		for _, f := range p.Files {
			if !f.Generate {
				continue
			}

			fileGen := generator.FromProtogenFile(f)

			for _, s := range f.Services {
				fmt.Print(s)
			}

			// Create client partial
			cp := partials.NewClient()

			fileGen.AppendPartial(*cp)

		}
		return nil
	})
}
