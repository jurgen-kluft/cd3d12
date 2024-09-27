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
	// Dependencies
	unittestpkg := cunittest.GetPackage()

	// The main (cd3d12) package
	mainpkg := denv.NewPackage(repo_name)

	// library
	mainlib := denv.SetupDefaultCppLibProject(repo_name, repo_path+repo_name)

	// unittest project
	maintest := denv.SetupDefaultCppTestProject(repo_name+"_test", repo_path+repo_name)
	maintest.Dependencies = append(maintest.Dependencies, unittestpkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, mainlib)

	mainpkg.AddMainLib(mainlib)
	mainpkg.AddUnittest(maintest)
	return mainpkg
}
