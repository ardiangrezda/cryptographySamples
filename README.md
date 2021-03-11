# cryptographySamples
Find some C++ files regarding implementing basic encryption and cryptography. There were part of the lectures in "Information security" that was organised from 2004-2010 in University of Prishtina, Kosovo

These .cpp files are command-line based.

  EEA.CPP - Function for Extended Euclidian Algorithm is created and also tested with values

  Erastotheni_1.cpp - This program creates simple numbers based on eratosthenes sieve. Used by algorithms which use public/private keys

  GCD.CPP - Algorithm which implements greatest common divisor for two numbers

  encBlock.cpp - Encrypt and decrypt files such that blocks are replaced with with other blocks.
                n block are taken as input and byte 0 is replaced by byte n-1, byte 1 with byte n -1, byte 2 with byte n - 3, etc
                
  encPolyAlphabetic.cpp - Encrypts and decrypts files with n different keys which are inputed by the user

  encSimple.cpp - Encrypts and decrypts files using simple substitute algorithm

  transpos.cpp - Encrypts and decrypts files using transposition algorithm


Folder Kripto_1 is an C++ application which uses MFC (Microsoft Foundation Clasess) and uses above mentioned algoritm for encrypting and decrypting files

