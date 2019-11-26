  MedGarble is the software demo for the following article:<br/><br/>
  Dong X, Randolph D, Wang X. *The Feasibility of Garbled Circuits for Cross-Site Clinical Data Analytics*,
  to appear in Proceedings of AMIA 2020 Informatics Summit, Houston, TX, March, 2020.
  <br/>
  # Installation
  <br/>
  Set up EMP-Toolkit, in this demo we use the semi-honest mode instance - emp-sh2pc. 
  <br/>Follow the instruction from: https://github.com/emp-toolkit/emp-sh2pc
  <br/><br/>
  1) Add pci-ca.cpp into ~/emp-toolkit/emp-sh2pc/test/
  <br/>
  2) Put "add_test (psi-ca)" at the bottom of ~/emp-toolkit/emp-sh2pc/CMakeLists.txt 
  <br/>
  3) Create a folder "psi-ca" inside the ~/emp-toolkit/emp-sh2pc/data/, and place two private set 36.1.data and 36.2.data inside
  <br/>
  4) These two files contain the integer representations of the 36 bit hashing results (site1-hash-36bit.txt, site2-hash-36bit.txt) of the two private sets
  <br/>
  5) Open a terminal and type ~/emp-toolkit/emp-sh2pc/build$make
  <br/>
  6) Open two terminals, and type:
  <br/>
  ~/emp-toolkit/emp-sh2pc/build$ ./bin/psi-ca 1 12345 36
  <br/>
  ~/emp-toolkit/emp-sh2pc/build$ ./bin/psi-ca 2 12345 36
  <br/>
