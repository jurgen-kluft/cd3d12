package cd3d12

import (
	denv "github.com/jurgen-kluft/ccode/denv"
	cunittest "github.com/jurgen-kluft/cunittest/package"
)

const (
	repo_path = "github.com\\jurgen-kluft\\"
	repo_name = "cd3d12"
)

func GetPackage() *denv.Package {
	name := repo_name

	// Dependencies
	unittestpkg := cunittest.GetPackage()

	// The main (cd3d12) package
	mainpkg := denv.NewPackage(name)

	// library
	mainlib := denv.SetupDefaultCppLibProject(name, repo_path+name)

	// unittest project
	maintest := denv.SetupDefaultCppTestProject(name+"_test", repo_path+name)
	maintest.Dependencies = append(maintest.Dependencies, unittestpkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, mainlib)

	mainpkg.AddMainLib(mainlib)
	mainpkg.AddMainLib(maintest)
	return mainpkg
}
