# Table of contents

- [ROOT6](#root6)
- [HepMC](#hepmc)
- [How to check the installation](#how-to-check-the-installation)
- [MadGraph5_aMC@NLO](#madgraph)

# Installation tutorial

For simplicity we will consider arbitrary path $PACKAGE_PATH for the directory path where we will place all packages required for this project. This consideration is not a requirement and you can configure the paths yourself the way it is convenient for you. 

**Recommended $PACKAGE_PATH**: ~/Packages

**Later if you see $PACKAGE_PATH replace it with your path.** Or add it in your profile (~/.bashrc or ~/.zshrc, or other)

And don't forget to **create** this path first with the following command

```sh
mkdir -p $PACKAGE_PATH
```

## ROOT6

Install the [required dependencies](https://root.cern/install/dependencies/).

Then install ROOT6 via package manager (if available, [see here](https://root.cern/install/)) or pre-compiled release for your platform [here](https://root.cern/install/all_releases/).

### Pre-compiled release

If your option is the installation of pre-compiled release, after downloading place the .tar.gz file in $PACKAGE_PATH. After heading in $PACKAGE_PATH substitute the "name_of_file.tar.gz" for your .tar.gz file name containing ROOT6 package and run

```sh
tar -xvzf "name_of_file.tar.gz"
```

Now extracted files are located at $PACKAGE_PATH/root which you should export in your profile (usually ~/.bashrc or ~/.zshrc; or other) to add search option in CMake or for python3 support. To do this as well as add easily accessible root executable add the following lines to your profile

```sh
export ROOT_PATH=$PACKAGE_PATH/root

source $ROOT_PATH/bin/thisroot.sh
```

### Installation with package manager

With package manager compiled root binaries will be located at /bin and libraries at /lib. In this case no $ROOT_PATH is not needed to be added to your profile.

### ROOT6 compilation

Alternatively, you can also compile ROOT6 yourself, however it will take quite a lot of computational power and might take a long time to compile. This step is **not recommended** if you do not have enough experience compiling packages from source.

### Testing ROOT installation

If you followed throught the above instructions you can check if ROOT was installed succesfully by running in python

```py
import root
```

## HepMC

First find the package for your distribution containing VDT library (can be cern-vdt, libvdt-dev) and install it. This library is a requirement for HepMC. 

HepMC can be installed via package manager on some distributions. See if your package manager contain hepmc package [here](https://gitlab.cern.ch/hepmc/HepMC3). Also note, that libraries for python need to be installed separately, which can be done with package manager or pip, if available. If there is no installation candidates for you, you can compile it yourself. I recommend first heading into $PACKAGE_PATH directory and then you clone the repository:

```sh
git clone https://gitlab.cern.ch/hepmc/HepMC3 --depth=1
```

Then head into HepMC3 directory and run cmake to generate a Makefile

```sh
cmake -DHEPMC3_BUILD_EXAMPLES=ON
```

After it is done, compile libraries with

```sh
make -j2
```

You can set higher number of threads for compilation, if you have sufficient RAM (more than ~2.5 GB per thread) otherwise you may run out of it.

Finally set environmental variables

```sh
export HEPMC3_PATH=$PACKAGE_PATH/HepMC3
export PYTHONPATH=$HEPMC3_PATH/outputs/lib:$PYTHONPATH
```

## How to check the installation

For c++ you can run cmake in mg5-crossec-course root directory to test if all packages were installed successfully.

If you followed through the above instructions you can check if packages mentioned in these instruction were installed successfully by running in python

```py
import ROOT
import hepmc
```
If no errors occurred, the installation was successful

## MadGraph

For MadGraph (i.e. MadGraph5_aMC@NLO) no compilation is needed. The code instead is compiled for the process you choose to generate. To install MadGraph clone its repository to the desired location (recommended location - your $PACKAGE_PATH). Then add $PATH variable in your profile in order to use mg5_aMC executable from any directory:

```sh
export PATH=$PACKAGE_PATH/mg5amcnlo/bin:$PATH
```

To test whether MadGraph is working run in the terminal to launch MadGraph interface after updating your profile

```sh
mg5_aMC
```

### MadAnalysis

To install MadAnalysis run in MadGraph interface

```
install MadAnalysis5
```
