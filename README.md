# qfx-file-modifier-in-c++

This is my original C++ parser of the qfx (variant of .ofx) format file.  It was made to rip out the visa transaction idetification number from the beginning of visa debit card transactions.  The visa transaction number prevented retailers of the same name from being categoriezed and reported together because each visa transaction number made each retailer with the same name a completely different retailer.  I created this command c++ line program to save me the trouble of manually removing each of these transaction numbers when I imported the data into Quicken Essentials for Mac.  

Please note I see this code as hard to read because of the heavy use of pointers.  It was an excercise in utilizing c++ pointers, but I understand it is not the most readable style code, which I would normally employ to help others follow along in what is happening with my code. 
