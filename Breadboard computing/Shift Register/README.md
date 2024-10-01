This is a 4 bit, bidirectional, signed fill barrel shifter. I know that they are often made with diode arrays, but this one gives me control over direction. This is a scaled down version of the shift register I designed for my 32 bit MIPS CPU. 

The IC I used is a 4 to 1 MUX made by TI: the CD4512BE.

I have included an image of the circuit and a Logisim simulation screenshot to match. In the images, the data DIP switches are asserting 0'b1010, and I have shifted once to the right for an output of 0'b1101.
