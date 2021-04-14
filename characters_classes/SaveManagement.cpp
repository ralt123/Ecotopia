#ifndef SAVEMANAGEMENT
#define SAVEMANAGEMENT

#include <fstream>
#include <stdexcept>

/* Returns boolean to indicate saving success or failure
saveFileId - ID of save file
fileName - name of save file
saveData - an array containing the data to be saved
Use of template to allow arrays containing differing data types to be saved*/
template<typename TYPE>
bool general_save_data(int saveFileId, std::string fileName, TYPE saveData)
{
	// Try statement used to deal with runtime errors that may arise due variables outside my control (such as invalid permissions)
	try
	{
		// Opens text file to write data to said file
		std::ofstream saveFile;
		saveFile.open(fileName + std::to_string(saveFileId) + ".txt");
		// Wrties data to text file and closes file
		for (int i=0; i<saveData.size(); i++)
		{
			saveFile << saveData[i] << ",";
		}
		// Closes file and returns true to signify success
		saveFile.close();
		return true;
	}
	// Error whilst saving file and storing attributes, return false
	// This catch statement is most likely ran due to insufficient rights
	catch(...)
	{
		return false;
	}
}

// Data is loaded in the same order as it was saved

/* Returns boolean to indicate saving success or failure
saveFileId - ID of save file
fileName - name of save file
arrayPointer - an array pointer used to contain the loaded data, must be of same type as the array used to store the data
Use of template to allow arrays containing differing data types to be saved*/
template <typename TYPE>
bool general_load_data(int loadFileId, std::string fileName, TYPE arrayPointer)
{
	// Try statement used to deal with runtime errors that may arise due to user incompetence
	try
	{
		// Opens file to input data from the file
		std::ifstream saveFile;
		saveFile.open(fileName + std::to_string(loadFileId) + ".txt");
		std::string savedData;
		// File not found thus false is returned
		if (not saveFile.is_open())
		{
			return false;
		}
		// Retrieves data and closes file
		std::getline(saveFile, savedData);
		saveFile.close();
		int separatorPos;
		int dataPos = 0;
		for (int i=0; i<arrayPointer->size(); i++)
		{
			// Gets position of separator
			separatorPos = savedData.substr(dataPos).find(",") + dataPos;
			// Save file was edited by a third party or corrupted, false is returned
			if (separatorPos == -1)
			{
				return false;
			}
			// Converts the extracted string attribute to an integer
			(*arrayPointer)[i] = std::stoi(savedData.substr(dataPos, separatorPos));
			dataPos = separatorPos+1;
		}
		return true;
	}
	// Error whilst loading file and setting attributes, return false
	// This catch statement is most likely ran due to the save file being altered after the last save
	catch(...)
	{
		return false;
	}
}
#endif

