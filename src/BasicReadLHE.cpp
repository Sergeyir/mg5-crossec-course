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
   if (!std::filesystem::exists(argv[0]))
   {
      std::cout << "\033[1m\033[31mError:\033[0m File " << argv[0] << " does not exist" << std::endl;
      return 1;
   }

   // Initializing reader for LHE file. Reader is used to access information stored in LHE file
   LHEF::Reader reader(argv[0]);

   // HepRup contains information about attributes of a run and events
   std::shared_ptr<HepMC3::HEPRUPAttribute> hepr = std::make_shared<HepMC3::HEPRUPAttribute>();

   // Initializing event attributes
   hepr->heprup = reader.heprup;

   // Initializing run-wide attributes
   hepr->tags = LHEF::XMLTag::findXMLTags(reader.headerBlock + reader.initComments);

   // run-level metadata that provides context info for interpreting events
   std::shared_ptr<HepMC3::GenRunInfo> runinfo = std::make_shared<HepMC3::GenRunInfo>();

   // adding HepRup to runinfo
   runinfo->add_attribute("HEPRUP", hepr);

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

      for (int i = 0; i < hepe->hepeup.NUP; i++)
      {
         HepMC3::GenParticlePtr particle = 
            std::make_shared<HepMC3::GenParticle>(hepe->momentum(i), 
                                                  hepe->hepeup.IDUP[i], 
                                                  hepe->hepeup.ISTUP[i]);

         std::cout << particle << std::endl;
      }

   }

   return 0;
}

#endif /* BASIC_READ_LHE_CPP */
