/** 
 *  @file   BasicReadLHE.cpp
 *  @brief  Contains simplest example on how to read data from .lhe file obtained from MadGraph with HepMC3
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

   // Initializing reader for LHE file. Reader is used to access information stored in .lhe file
   LHEF::Reader reader(argv[1]);

   unsigned long numberOfEvents = 0;
   while (reader.readEvent())
   {
      numberOfEvents++;

      if (numberOfEvents % 1000 == 0) std::cout << "Event " << numberOfEvents << "\r" << std::endl;

      // HepMC needs this object to store the event, tags, XML, and other data into
      std::shared_ptr<HepMC3::HEPEUPAttribute> hepe = std::make_shared<HepMC3::HEPEUPAttribute>();

      if (reader.outsideBlock.length())
      {
         // Each event may have non-standard information outside LHEF event 
         hepe->tags = LHEF::XMLTag::findXMLTags(reader.outsideBlock);
      }
      // Storing reader event data into HepMC3::HEPEUPAttribute object
      hepe->hepeup = reader.hepeup;

      if (numberOfEvents == 1)
      {
         // Iterating over every particles in the current event
         for (int i = 0; i < hepe->hepeup.NUP; i++)
         {
            HepMC3::GenParticlePtr particle = 
               std::make_shared<HepMC3::GenParticle>(hepe->momentum(i), 
                                                     hepe->hepeup.IDUP[i], 
                                                     hepe->hepeup.ISTUP[i]);

            // GenParticle and FourVector methods can be seen here
            // https://dayabay.bnl.gov/dox/HepMC/html/classHepMC_1_1GenParticle.html
            HepMC3::FourVector fourVec = particle->momentum();

            std::cout << particle->pid() << " " << fourVec.e() << " " << 
                         fourVec.px() << " " << fourVec.py() << " " << fourVec.pz() << std::endl;
         }
      }
   }
   
   // Find the measurement units for the total cross section
   std::cout << "Total cross section: " << GetTotCrossSection(argv[1]) << std::endl;

   return 0;
}

double GetTotCrossSection(const std::string& fileName)
{
   std::ifstream file(fileName);

   std::regex re(R"(^#\s*Integrated weight \(pb\)\s*:\s*([0-9.+-eE]+))");

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

   std::cout << "\033[1m\033[31mError:\033[0m cross-section comment "\
                "not found in file" + fileName << std::endl;
   exit(1);
}

#endif /* BASIC_READ_LHE_CPP */
