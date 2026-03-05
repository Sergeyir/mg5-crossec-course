/** 
 *  @file   BasicReadLHE.cpp
 *  @brief  Contains simplest case that shows how the data can be generated with PYTHIA8 and LHAPDF6 and processed with FASTJET3 for jets selection 
 *
 *  This file is a part of a project mg5-crossec-course (https://github.com/Sergeyir/mg5-crossec-course).
 *
 *  @author Sergei Antsupov (antsupov0124@gmail.com)
 **/
#ifndef BASIC_READ_LHE_CPP
#define BASIC_READ_LHE_CPP

#include "BasicReadLHE.hpp"

int main(int argc, char **argv)
{
   // printing info on usage and exiting the program if number of parameters is incorrect
   if (argc != 2) 
   {
      std::cout << "\033[1m\033[31mError:\033[0m Expected 1 parameter while " + 
                   std::to_string(argc - 1) + " parameter(s) were provided.\n"\
                   "Usage: bin/BasicReadLHE input_file_name output_file_name" << std::endl;
      return 1;
   }

   // Checking if specified file exist
   if (!std::filesystem::exists(argv[1]))
   {
      std::cout << "\033[1m\033[31mError:\033[0m File " << argv[1] << " does not exist" << std::endl;
      return 1;
   }

   std::cout << "Reading from file " << argv[1] << std::endl;

   // Initializing reader for LHE file. Reader is used to access information stored in LHE file
   LHEF::Reader reader(argv[1]);

   // HepRup contains information about attributes of a run and events
   std::shared_ptr<HepMC3::HEPRUPAttribute> hepr = std::make_shared<HepMC3::HEPRUPAttribute>();

   // Initializing event attributes
   hepr->heprup = reader.heprup;

   // Initializing run-wide attributes
   hepr->tags = LHEF::XMLTag::findXMLTags(reader.headerBlock + reader.initComments);

   HepMC3::GenEvent evt;

   unsigned long numberOfEvents;
   while (reader.readEvent())
   {
      numberOfEvents++;

      if (numberOfEvents % 1000 == 0) std::cout << "Event " << numberOfEvents << "\r" << std::endl;

      std::shared_ptr<HepMC3::HEPEUPAttribute> hepe = std::make_shared<HepMC3::HEPEUPAttribute>();

      if (reader.outsideBlock.length())
      {
         // Each event may have non-standard information outside LHEF event 
         hepe->tags = LHEF::XMLTag::findXMLTags(reader.outsideBlock);
      }
      hepe->hepeup = reader.hepeup;

      // iterating over all particles in the current event
      for (int i = 0; i < hepe->hepeup.NUP; i++)
      {
         HepMC3::GenParticlePtr particle = 
            std::make_shared<HepMC3::GenParticle>(hepe->momentum(i), 
                                                  hepe->hepeup.IDUP[i], 
                                                  hepe->hepeup.ISTUP[i]);

         // GenParticle and FourVector methods can be seen here
         // https://dayabay.bnl.gov/dox/HepMC/html/classHepMC_1_1GenParticle.html
         HepMC3::FourVector fourVec = particle->momentum();
         std::cout << particle->pid() << " " << fourVec.e() << " " << fourVec.px() << " " << fourVec.py() << " " << fourVec.pz() << std::endl;
      }
   }
   
   // Find the measurement units for the total cross section
   std::cout << "Total cross section: " << ReadTotCrossSection(argv[1]) << std::endl;

   return 0;
}

double ReadTotCrossSection(const std::string& fileName)
{
   std::ifstream file(fileName);

   std::regex re(R"(^\s*#\s*Integrated weight \(pb\)\s*:\s*([0-9.+-eE]+))");

   std::string line;
   while (std::getline(file, line))
   {
      std::smatch m;
      if (std::regex_search(line, m, re))
      {
         return std::stod(m[1].str());
      }
      // stopping if header was passed
      if(line.find("<event") != std::string::npos) break;
   }
   throw std::runtime_error("cross-section comment not found");
}

#endif /* BASIC_READ_LHE_CPP */
