/**
 * @file FileHandle.h
 *
 * 文本文件处理类文件
 *
 * @author DBNCLab
 * Copyright(c) 2007 by School Of Computer Science & Engineering, South China University of Technology, Guangzhou, Guangdong, P.R.C. 
 *
 */

#ifndef _FILEHANDLE_H_INCLUDE__
#define _FILEHANDLE_H_INCLUDE__

#include "Common.h"

namespace PreCmpt{

// Define tuple id type.
typedef unsigned int TID;
// Define field id type.
typedef unsigned int FID;
// Maximum length of a tuple.
const unsigned int MAXTUPLELEN = 4096;

/*
 * The TupleHandle class defines tuple objects. To materialize a tuple, a
 * client creates an instance of this class and passes it to DFHandle methods
 * that reads a tuple.
 */
class TupleHandle
{
private:
	// Is this tuple Handle valid?
	bool isValid;
	// The tuple ID.
	TID Tid;
	// Current Field ID. Start from 0.
	FID currFid;
	// The tuple data.
	char tData[MAXTUPLELEN];
	// Field delimiter.
	char *Delimiter;
	// First call to GetNextField?
	bool isFirstCall;
public:
	TupleHandle (const char *delim);
	~TupleHandle ();

	void Open (const char * const pData, size_t length, TID tid);
	// Return this tuple ID.
	bool GetTid (TID &tid) const;
	// Set pData points to tData.
	bool GetData (const char *&pData) const;
	// Make a copy of next Field to pFiled.
	bool GetNextField (char * const pField, size_t length, FID &fid);
};

class DFHandle
{
private:
	// Is the file handle open?
	bool isOpen;
	// Name of the data file.
	char *fileName;
	// The opened FILE pointer.
	FILE *fPointer;
	// Current tuple id, start from 1.
	TID currTid;
	
public:
	DFHandle ();
	~DFHandle ();

	// Attaches a file to this handle
	bool Open (const char* file);
	// Detaches file from this handle
	bool Close ();
	// Reposition the file stream to the beginning of the file.
	bool ReWind ();
	// Fetch next tuple in data file.
	bool GetNextTuple (TupleHandle &tHandle);
};

}

#endif
