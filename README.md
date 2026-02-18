# Table of contents

- [Overview](#overview)
- [Requirements](#requirements)
- [Analytic calculation](#analytic-calculation)
- [Installation](#installation)
- [How to use](#how-to-use)
    - [PYTHIA8+FASTJET](#pythia8+fastjet)
    - [HERWIG7+FASTJET](#herwig7+fastjet)
    - [POWHEGBOX+PYTHIA8+FASTJET](#powhegbox+pythia8+fastjet)
- [Using this project for teaching](#using-this-project-for-teaching)
- [Sources](#sources)

# Overview

This is a simple projects that contains tutorials and examples demonstraiting MadGraph calculations for 2->2 processes at LO and NLO. The goal of this project to learn how to calculate the simplest 2->2 cross sections and display $1 / 2\pi p_{T} d\sigma / dp_{T} d_{y}$ from the MadGraph output at different energies. Use this repository as a self-contained MadGraph learning tool resource or as a complement to particle physics courses. 

# Requirements

- GCC(>=7) (for C++17 support)
- gfortran(>=4.6)
- python3 + python3-dev
- [ROOT6](https://root.cern/)
- [MadGraph5_aMC@NLO](https://launchpad.net/mg5amcnlo)+MadAnalysis
- [HEPMC](https://gitlab.cern.ch/hepmc/HepMC3/-/releases) 

ROOT6 and HEPMC have to be compiled with python3 if you want to use it in python interface. For more information see [Installation tutorial](INSTALLATION_TUTORIAL.md).

# Installation

```sh
git clone https://github.com/Sergeyir/mg5-crossec-course --depth=1
```

Install all requirements and configure environment variables described in [Installation tutorial](INSTALLATION_TUTORIAL.md)

Python environment should work fine after the last step. If you need to use C++ for this project run

```sh
cmake .
make -j
```

To update the repository to the newest version run in its root

```sh
git pull
```

<details>
<summary> Implementing your changes</summary>

Since the project may be updated you may need to pull the changes. This way implementing your changes to the code may cause conflict in git version. To circumvent this you can create a branch of this repo or just copy the contents of this repository to your directory and remove CMake files and cache:

```sh
rm -r CMakeFiles cmake_install.cmake CMakeCache.txt
```

</details>

# Examples of MadGraph usage

## LO example

After installing MadGraph and configuring $PATH variable (see [Installation tutorial](INSTALLATION_TUTORIAL.md)) run in the terminal

```sh
mg5_aMC
```

This will open the MadGraph interface in which you can configure the process you want to calculate and which looks like this (after all DEBUG messages):

```
INFO: Change particles name to pass to MG5 convention
Defined multiparticle p = g u c d s u~ c~ d~ s~
Defined multiparticle j = g u c d s u~ c~ d~ s~
Defined multiparticle l+ = e+ mu+
Defined multiparticle l- = e- mu-
Defined multiparticle vl = ve vm vt
Defined multiparticle vl~ = ve~ vm~ vt~
Defined multiparticle all = g u c d s u~ c~ d~ s~ a ve vm vt e- mu- ve~ vm~ vt~ e+ mu+ t b t~ b~ z w+ h w- ta- ta+
```

You can run "help" to see the list of available commands. In our case at this point we only want to generate the code for the computation of cross section. Note that the last line MadGraph printed contains defined particles (these also can be printed with "display particles"). Lets try generating $e^+ + e^- \rightarrow \gamma + \gamma$ (don't forget the spaces):

```
generate e+ e- > a a
```

Note that in MadGraph interface photon is defined as "a". After running this command you should see 

```
INFO: Checking for minimal orders which gives processes.
INFO: Please specify coupling orders to bypass this step.
INFO: Trying process: e+ e- > a a WEIGHTED<=4 @1
INFO: Process has 2 diagrams
1 processes with 2 diagrams generated in 0.002 s
Total: 1 processes with 2 diagrams
```

At this point you can run

```
display histograms
```

Which will open .eps file with drawn Feynman diagrams for our defined process. For the process in this example you should see at the bottom of histograms "QCD=0, QED=2". Do you know the meaning of this notation and why is number 2 instead of 1 present?. Weighted=4 in the upper left corner means the number of weight variations of events to be stored when calculation is launched. These weight variations are then used to estimate the systematic uncertainty of a cross section.

To generate the code that you can run to calculate the cross section run (lets save the code in this example in "ee_aa_LO" directory)

```
output ee_aa_LO
```

Then launch the calculation with

```
launch ee_aa_LO
```

You will be met by various switches for generation which we don't need in this example so just press enter. After you can modify event parameters. In this course the calculation of cross section at different energies is needed so let's change the energy (GeV) of incoming particles by running

```
set ebeam1 200
```

And

```
set ebeam2 200
```

Then press enter. At this points the code will be compiled and then executable that calculates the cross seciton will be run. After finishing the calculation MadGraph will create .html file containing event information, cross section calcuation and various differential cross-sections plots. You can view it by running

```
open index.html
```

Click at "Results and Event Database" to see the calculation result. Here you can also click on "MA5_report_analysis1" to see more information as well as different distributions of differential cross sections plotted on histograms.

## NLO example

Instructions will appear soon

<!--
The calculation is similar apart from the "generate command":

```
generate e+ e- > a a [QED]
```

Where \[QED\] adds QED loops and additional real photon emmisions. This command as well as command below will ask to install dependencies for NLO calculations when run for the first time (you can just press enter to start installation). The rest is similar to LO example:

```
output ee_aa_NLO
```

```
launch ee_aa_NLO
```

Don't forget to set the energy after launching
-->

# Using MadGraph output

Instructions will appear soon

<!--

After running the calcualtion unweighted_events.lhe.gz files should appear in ee_aa_LO/Events/run_01 and ee_aa_NLO/Events/run_01. These files contain all information about processed events.
-->

<!--
# Using this project for teaching

This is an open source public project which anyone can use. If you are teaching students programming/software in particle physics and would like to incorporate this project or a part of it, you can reach me at [antsupov0124@gmail.com](mailto:antsupov0124@gmail.com) so that I can send you a complete version of this repository. Complete version contains fully finished code which can be used to check the results obtained by students. Please do send the request from you university email address while stating the position, department, and university, so it would be easier for me to confirm your status.

Also this project by itself is not enough for someone to learn the underlying physics, programming, and HEP software. Supervision and assistance is required for students to have a fullest grasp of the subject and experience development.
-->

# Sources

1. [MadGraph Wiki](https://cp3.irmp.ucl.ac.be/projects/madgraph)
2. [MadGraph lectures and tutorials](https://cp3.irmp.ucl.ac.be/projects/madgraph/wiki/MGTutorial)
