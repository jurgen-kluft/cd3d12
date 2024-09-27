package main

import (
	ccode "github.com/jurgen-kluft/ccode/ccode-base"
	cpkg "github.com/jurgen-kluft/cd3d12/package"
)

func main() {
	ccode.Init()
	ccode.GenerateFiles()
	ccode.Generate(cpkg.GetPackage())
}
