package cd3d12

import (
	denv "github.com/jurgen-kluft/ccode/denv"
)

const (
	repo_path = "github.com\\jurgen-kluft\\"
	repo_name = "cd3d12"
)

func GetPackage() *denv.Package {
	name := repo_name

	// The main (cd3d12) package
	mainpkg := denv.NewPackage(name)

	// library
	mainlib := denv.SetupDefaultCppLibProject(name, repo_path+name)

	mainpkg.AddMainLib(mainlib)
	return mainpkg
}
