/** 
 *  @file   BasicReadLHE.hpp
 *  @brief  Contains simplest example on how to read data from .lhe file obtained from MadGraph with HepMC3
 *
 *  This file is a part of a project mg5-crossec-course (https://github.com/Sergeyir/mg5-crossec-course).
 *
 *  @author Sergei Antsupov (antsupov0124@gmail.com)
 **/
#ifndef BASIC_READ_LHE_HPP
#define BASIC_READ_LHE_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>

#include "HepMC3/LHEFAttributes.h"
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"

#include "TFile.h"
#include "TH1D.h"

/// Returns the cross section from the specified .lhe file
double GetTotCrossSection(const std::string& fileName);

#endif /* BASIC_READ_LHE_HPP */
