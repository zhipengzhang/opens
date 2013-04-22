#include "./PreComputation/FileHandle.h"

namespace PreCmpt{

DFHandle::DFHandle ()
{
	isOpen = false;
	fileName = NULL;
	fPointer = NULL;
	currTid = 1;
}

DFHandle::~DFHandle ()
{
	if (isOpen) 
		Close ();
}

bool DFHandle::Open (const char *file)
{
	if (isOpen)
		Close();

	fileName = strdup (file);
	fPointer = fopen (fileName, "r");
	if (fPointer == NULL)
	{
		perror ("fopen error!");
		return false;
	}
	// Now the file has been successfully opened.
	isOpen = true;

	return true;
}

bool DFHandle::Close ()
{
	if (!isOpen) return false;

	if (fclose (fPointer) == EOF)
	{
		perror ("fclose error!");
		return false;
	}

	free (fileName);
	fileName = NULL;
	fPointer = NULL;
	currTid = 1;
	isOpen = false;
	
	return true;
}

bool DFHandle::ReWind ()
{
	if (!isOpen) return false;

	rewind (fPointer);
	return true;
}

// pre:  tHandle is a reference to a TupleHandle object, 
//       which must have been created by the client.
// post: A newly fetch tuple stored in tHandle.
//       Returns false if some error occurs.
bool DFHandle::GetNextTuple (TupleHandle &tHandle)
{
	if (!isOpen) return false;

	static char tData[MAXTUPLELEN];
	// Get next tuple in data file.
	if (fgets (tData, MAXTUPLELEN, fPointer) != NULL)
	{
		// strip '\n'
		tData[strlen (tData) - 1] = '\0';
		tHandle.Open (tData, sizeof (tData), currTid);
		currTid++;
		return true;
	}
	return false;
}

TupleHandle::TupleHandle (const char *delim)
{
	assert (delim);
	currFid = 0;
	isValid = false;
	isFirstCall = true;
	Delimiter = strdup(delim);
}

TupleHandle::~TupleHandle () 
{
	free (Delimiter);
}

void TupleHandle::Open (const char * const pData, size_t length, TID tid)
{
	assert (length <= MAXTUPLELEN);
	strcpy (tData, pData);
	Tid = tid;
	isValid = true;
	isFirstCall = true;
	currFid = 0;
}

bool TupleHandle::GetTid (TID &tid) const
{
	if (!isValid) return false;
	tid = this->Tid;
	return true;
}

bool TupleHandle::GetData (const char *&pData) const
{
	if (!isValid) return false;

	pData = &tData[0];
	return true;
}

bool TupleHandle::GetNextField (char * const pField, 
								 size_t length, FID &fid)
{
	assert (pField != NULL);
	assert (length > 0);

	if (!isValid) return false;

	char *ptr = NULL;
	if (isFirstCall)
	{
		ptr = strtok (tData, Delimiter);
		isFirstCall = false;
	}
	else
		ptr = strtok (NULL, Delimiter);
		
	if (ptr)
	{
		size_t len = strlen (ptr);
		// Keep a character for '\0'
		length--;
		// If length <= len, only copy the first length characters.
		len = length > len ? len : length;
		strncpy (pField, ptr, len);
		pField[len] = '\0';
		fid = currFid++;
		return true;
	}
	return false;
}

}
