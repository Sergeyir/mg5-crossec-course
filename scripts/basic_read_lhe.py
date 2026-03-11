#!/usr/bin/env python3

#  @file   basic_read_lhe.py
#  @brief  Contains simplest example on how to read data from .lhe file obtained from MadGraph with HepMC3
#
#  This file is a part of a project genjets-course (https://github.com/Sergeyir/genjets-course).
#
#  @author Sergei Antsupov (antsupov0124@gmail.com)

import os
import re
import sys
import argparse

import ROOT
from pyHepMC3 import HepMC3, LHEF

"""
Returns the total cross section if the comment about it exists the specified .lhe file
Otherwise error will be printed and the program will be terminated
"""
def get_tot_cross_section(file_name: str) -> float:
    pattern = re.compile(r"^\s*#\s*Integrated weight \(pb\)\s*:\s*([0-9.+\-eE]+)")
    with open(file_name, 'r') as f:
        for line in f:
            m = pattern.search(line)
            if m:
                return float(m.group(1))
            if "<event" in line:
                break

    print(f"\033[1m\033[31mError:\033[0m cross-section comment not found in file {filename}", 
          file=sys.stderr)
    sys.exit(1)

def read_lhe(input_file_name : str) -> int :
    # checking if specified input file exists
    if not os.path.isfile(input_file_name):
        print(f"\033[1;31mError:\033[0m file {input_file_name} was not found")
        return 1

    # Initializing reader for .lhe file. Reader is used to access information in .lhe file
    reader = LHEF.Reader(input_file_name)

    number_of_events = 0

    while reader.readEvent() :
        number_of_events += 1

        if number_of_events % 1000 == 0 :
            print(f"Event {number_of_events}\r")

        # HepMC needs this object to store the event, tags, XML, and other data into
        hepe = HepMC3.HEPEUPAttribute()

        # Each event may have non-standard information outside LHEF event 
        if len(reader.outsideBlock) :
            hepe.tags = LHEF.XMLTag.findXMLTags(reader.outsideBlock)

        # Storing reader event data into HepMC3.HEPEUPAttribute object
        hepe.hepeup = reader.hepeup

        # Iteration over every particle in the current event
        for i in range(hepe.hepeup.NUP) :
            particle = HepMC3.GenParticle(hepe.momentum(i), 
                                          hepe.hepeup.IDUP[i], 
                                          hepe.hepeup.ISTUP[i])
            # GenParticle and FourVector methods can be seen here
            # https://dayabay.bnl.gov/dox/HepMC/html/classHepMC_1_1GenParticle.html
            four_vec = particle.momentum()

            print(particle.pid(), four_vec.e(), four_vec.px(), four_vec.py(), four_vec.pz())

    print("Total cross section:", get_tot_cross_section(input_file_name))
    return 0

if __name__ == "__main__":
    # parsing input arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input", type=str)

    args = parser.parse_args()
    input_file_name = args.input

    if not input_file_name:
        print('\033[1;31mError:\033[0m .lhe input file must be specified; use option -i or --input')
        sys(exit(1))

    sys.exit(read_lhe(input_file_name))
