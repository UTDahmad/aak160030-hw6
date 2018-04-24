/*
 * Ahmed Khan
 * aak160030@utdallas.edu
 * CS 3377
 * Usage of CDK Matrix originally by Dr. Perkins
 *
 * 
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <stdint.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

//Class for header
class BinaryFileHeader
{
public:
uint32_t magicNumber; //(0xFEEDFACE)
  uint32_t versionNumber;
  uint64_t numRecords;
};


//Size of the fixed length buffer that records use
  const int maxRecordStringLength = 25;

//Class for Records
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix


  //Setting up a matrix, recall that the matrix starts at 1,1
  //Placeholders are used for 0,0

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  //Open binary file for input
  ifstream binaryFile ("cs3377.bin", ios::in | ios::binary);
  //If file is not found, output error and exit
  if (!binaryFile.is_open())
    {
      cout << "Error, could not file cs3377.bin\n";
      return 1;
    }

  //header object
  BinaryFileHeader *header = new BinaryFileHeader();

  //Read the header from file
  binaryFile.read((char*) header, sizeof(BinaryFileHeader));

  //Sets up stringstream to convert to a hex value
  stringstream hexConversion;

  hexConversion << hex <<uppercase  << header->magicNumber;
  
  //Prepare strings for output
  string magic = string("Magic: 0x" + hexConversion.str());
  string version = string("Version: " + to_string(header->versionNumber));
  string records = string("NumRecords: " + to_string(header->numRecords));
  //Output strings to respective cells
  setCDKMatrixCell(myMatrix, 1, 1, magic.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, records.c_str());

  //Initialize i to number of records
  int i = header->numRecords;
  //Prepare the maximum amount of record objects
  BinaryFileRecord *record1 = new BinaryFileRecord();
  BinaryFileRecord *record2 = new BinaryFileRecord();
  BinaryFileRecord *record3 = new BinaryFileRecord();
  BinaryFileRecord *record4 = new BinaryFileRecord();

  //If at least one record is present
  if(i>0)
    {
      //decrement counter
      i--;
      
      //Read information from file and output to respective cells
      binaryFile.read((char*)record1, sizeof(BinaryFileRecord));
      string length1 = string("strlen: " + to_string(record1->strLength));
      string buffer1 = string(record1->stringBuffer);
      setCDKMatrixCell(myMatrix, 2, 1, length1.c_str());
      setCDKMatrixCell(myMatrix, 2, 2, buffer1.c_str());
    }
  //If at least one more record is present
  if(i>0)
    {
      //decrement i
      i--;
      //Read information from file and output to respective cells
      binaryFile.read((char*)record2, sizeof(BinaryFileRecord));
      string length2 = string("strlen: " + to_string(record2->strLength));
      string buffer2 = string(record2->stringBuffer);
      setCDKMatrixCell(myMatrix, 3, 1, length2.c_str());
      setCDKMatrixCell(myMatrix, 3, 2, buffer2.c_str());
    }
  //If at least one more record is present
  if(i>0)
    {
      //decrement i
      i--;
      //Read information from file and output to respective cells
      binaryFile.read((char*)record3, sizeof(BinaryFileRecord));
      string length3 = string("strlen: " + to_string(record3->strLength));
      string buffer3 = string(record3->stringBuffer);
      setCDKMatrixCell(myMatrix, 4, 1, length3.c_str());
      setCDKMatrixCell(myMatrix, 4, 2, buffer3.c_str());
    }
  //If fourth file record is present
  if(i>0)
    {
      //decrement i
      i--;
      //Read information from file and output to respective cells
      binaryFile.read((char*)record4, sizeof(BinaryFileRecord));
      string length4 = string("strlen: " + to_string(record4->strLength));
      string buffer4 = string(record4->stringBuffer);
      setCDKMatrixCell(myMatrix, 5, 1, length4.c_str());
      setCDKMatrixCell(myMatrix, 5, 2, buffer4.c_str());
    }


  //Draw the matrix
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;


  delete record1;
  delete record2;
  delete record3;
  delete record4;
  delete header;
  binaryFile.close();
  // Cleanup screen
  endCDK();
}
