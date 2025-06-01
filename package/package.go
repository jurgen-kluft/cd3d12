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

	// dependencies
	unittestpkg := cunittest.GetPackage()

	// main package
	mainpkg := denv.NewPackage(repo_path, repo_name)

	// main library
	mainlib := denv.SetupCppLibProject(mainpkg, name)

	// test library
	testlib := denv.SetupCppTestLibProject(mainpkg, name)

	// unittest
	maintest := denv.SetupCppTestProject(mainpkg, name)
	maintest.AddDependencies(unittestpkg.GetTestLib()...)
	maintest.AddDependency(testlib)

	mainpkg.AddMainLib(mainlib)
	mainpkg.AddTestLib(testlib)
	mainpkg.AddUnittest(maintest)
	return mainpkg
}
