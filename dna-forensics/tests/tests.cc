#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch/catch.hpp>
#include <string>
#include <fstream>
#include "functions.hpp"
#include <map>
#include <iostream>

using namespace std;



TEST_CASE("A test case", "FindPerson") {
  string s = "AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGAGATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA";
  string s2 = "TATTATTATTATAACCCTGCGCGCGCGCGATCCAGCATTAGCTAGCATCAAGATGAGATGAGATGGAATTTCGAAATGAATGAATGAATGAATGAATGAATG";
  string s3 = "GGTACAGATGGCAAAGATGAGATGAGATGGTCGTCGAGCAATCGTTTCGATAATGAATGAATGAATGAATGAATGAATGACACACGTCGATGCTAGCGGCGGATCGTATATTATAACCCCTAG";

  map<string, vector<string>> m;
  ifstream ifs {"/home/vagrant/src/mp-dna-forensics-JustinXre2020/tests/ex-str-database-from-prompt.dat"};
  for(std::string line; std::getline(ifs, line); line = "") 
    m = ConvertDNA(utilities::GetSubstrs(line, ','), m);
  REQUIRE(FindPerson(m, s) == "Casey");
  REQUIRE(FindPerson(m, s2) == "Amani");
  REQUIRE(FindPerson(m, s3) == "No match");
}
