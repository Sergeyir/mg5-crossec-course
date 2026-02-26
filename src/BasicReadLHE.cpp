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
   // printing info on usage and exiting program if number of parameters is incorrect
   if (argc != 2) 
   {
      std::cout << "\033[1m\033[31mError:\033[0m Expected 1 parameter while " + 
                   std::to_string(argc - 1) + " parameter(s) were provided.\n"\
                   "Usage: bin/BasicReadLHE input_file_name output_file_name" << std::endl;
      return 1;
   }

   if (!std::filesystem::exists(argv[0]))
   {
      std::cout << "\033[1m\033[31mError:\033[0m File " << argv[0] << " does not exist" << std::endl;
   }
   LHEF::Reader reader(argv[0]);

   unsigned long numberOfEvents;
   while (reader.readEvent())
   {
      numberOfEvents++;
   }

   return 0;
}

#endif /* BASIC_READ_LHE_CPP */
