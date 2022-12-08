/**
* Coursework1 File Reader main file
* 
* modify the body of all procedures within this file to achieve the set task of opening/closing, loading and inspecting a given format textfile
* for that purpose, you will have to implement basic filereading from a textfile as well as parsing and storing capabilties
* 
* DO NOT modify the test.h file or the FileReader.h in any way but implement the bodies of the outlined procedures for a working
* file reader and pass all tests.
*/
#include "FileReader.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <regex>

std::vector<std::string> splitString(std::string toSplit, std::string delimiter) {
	std::vector<std::string> result = std::vector<std::string>();
	size_t start = 0;
	size_t end = toSplit.find(delimiter);
	while (end != std::string::npos) {
		result.push_back(toSplit.substr(start, end));
		toSplit = toSplit.substr(end + 1);
		start = end;
		end = toSplit.find(delimiter);
	}
	result.push_back(toSplit);
	return result;
}

constexpr auto POS_KEY = "pos";
constexpr auto SUBPOS_KEY = "subpos";
// Map to store regexes statically, keys in format {file-format}_{subject}
std::map<std::string, std::regex> regexMap{
	{ "obj_object", std::regex("o (.*)") },
	{ "obj_vertex", std::regex("v (.*)") },
	{ "obj_vertex-texture", std::regex("vt (.*)") },
	{ "obj_vertex-normal", std::regex("vn (.*)") },
	{ "obj_face", std::regex("f (.*)")},
	{ "gltf_mesh", std::regex("\"meshes\"\\s?:\\s?\\[[^]*?\\],")},
	{ "gltf_name", std::regex("\"name\"\\s?:\\s?\"(.*)\"")}
};

std::string getFileExtension(std::string* fileName) {
	return fileName->substr(fileName->find_last_of(".") + 1);
}

// Gets a regex for a given file and target subject
std::regex getRegex(std::string* fileName, std::string* subject) {
	std::string extension = getFileExtension(fileName);
	std::string key = extension + "_" + *subject;
	return regexMap[key];
}

FileReader::FileReader() {
	currentFileName = "";
	textFile = nullptr;
	streams = std::vector<std::ifstream>();
	storage = std::map<std::string, std::string>();
}

// Reads the full content from an IfStream to a string
std::string readFromIfstream(std::ifstream* ifstream) {
	std::stringstream strStream;
	strStream << ifstream->rdbuf();
	std::string content = strStream.str();
	ifstream->seekg(0, ifstream->beg);
	return content;
	
}


// returns an array of strings ideally one for each line in the file
bool FileReader::openFile(std::string fileName) {
	std::string extension = getFileExtension(&fileName);
	// Check if this file has already been opened and is an obj/gltf
	if (storage.count(fileName) == 1 && (extension != "obj" || extension != "gltf")) {
		return false;
	}

	std::ifstream fileStream(fileName, std::ifstream::in);
	if (fileStream.good()) {
		currentFileName = fileName;
		
		// TODO: Find some way to un-duplicate this
		storage["file"] = readFromIfstream(&fileStream);
		textFile = &storage["file"];
		streams.push_back(std::move(fileStream));
		std::string streamIndex = std::to_string(streams.size() - 1);
		// Add both ways around to facilitate "reverse" lookups - both keys should be already unique
		storage[fileName] = streamIndex;
		storage[streamIndex] = fileName;
		
		return true;
	}

	return false;
}

// Gets the name of the currently open file
std::string FileReader::currentFile() {
	
	return currentFileName;
}

// Gets the number of lines in the currently open file
int FileReader::lineCount()
{
	int currentIndex = 0;
	int lines = 0;
	while (currentIndex != - 1) {
		++lines;
		currentIndex = textFile->find('\n', currentIndex + 1);
	}
	return lines;
}

// Gets the index of the beginning of a line in a given string.
int getLineIndex(std::string* str, int lineNumber) {
	int currentIndex = 0;
	int lines = 0;
	while (currentIndex != -1 && lines < lineNumber) {
		++lines;
		currentIndex = str->find('\n', currentIndex + 1);
	}
	if (currentIndex != -1) {
		// Give the position for the beginning of the next line
		++currentIndex;
	}
	return currentIndex;
}

// Gets a 0-indexed line of the currently open file
std::string FileReader::getLine(int line)
{
	int lineIndex = getLineIndex(textFile, line);
	std::istringstream strStream(*textFile);
	strStream.seekg(lineIndex);
	std::string lineString;
	std::getline(strStream, lineString);
	return lineString;
}

// Gets a 0-indexed range of lines of the currently open file
std::vector<std::string> FileReader::getLines(int start, int end)
{
	std::vector<std::string> strVector = std::vector<std::string>();
	if (textFile == nullptr) {
		return strVector;
	}
	int fileLineCount = lineCount();
	// Minus 1 for 0-indexing
	end = (end < fileLineCount) ? end : fileLineCount - 1;
	// Plus 1 for 0-indexing
	int range = end + 1 - start;

	int startPos = (start == 0) ? 0 : getLineIndex(textFile, start);
	std::istringstream strStream(*textFile);
	strStream.seekg(startPos);
	std::string lineStr;
	for (int i = 0; i < range; i++)
	{
		std::getline(strStream, lineStr);
		strVector.push_back(lineStr);
	}

	return strVector;
}

// Gets the content of an element and moves POS_KEY to its position. Use timesToMoveCursor to skip results before the value is read and position set. Set to 0 to read the current without moving.
std::vector<std::string> getElementHelper(std::string* subject, int timesToMoveCursor, std::map<std::string, std::string> *storage, std::string *textFile, std::string *fileName) {
	
	std::vector<std::string> strVector = std::vector<std::string>();

	if (textFile == nullptr) {
		strVector.push_back("");
		return strVector;
	}
	
	int pos = storage->count(POS_KEY) == 0 ? 0 : std::stoi(storage->at(POS_KEY));

	std::regex regex = getRegex(fileName, subject);
	std::smatch match;
	std::string::const_iterator iterator = textFile->cbegin() + pos;
	for (int i = 0; i < timesToMoveCursor; i++)
	{
		if (std::regex_search(iterator, textFile->cend(), match, regex)) {
			
			iterator = match.suffix().first;
			pos = match.position() + match.length() + pos;
		}
		storage->erase(SUBPOS_KEY);
	}

	if (std::regex_search(iterator, textFile->cend(), match, regex)) {
		// MAtch position is relative to the start of the iterator (pos)
		pos = match.position() + pos;
		strVector.push_back(match.str(1));
	}
	else {
		strVector.push_back("");
	}

	// No entry is considered starting from 0, do not waste memory
	if (pos != 0) {
		storage->operator[](POS_KEY) = std::to_string(pos);
	}

	return strVector;
}

// Gets the content of an attribute and moves SUBPOS_KEY to its position, starting from POS_KEY. Use timesToMoveCursor to skip results before the value is read and position set. Set to 0 to read the current without moving.
std::string getAttributeHelper(std::string* subject, int timesToMoveCursor, std::map<std::string, std::string>* storage, std::string* textFile, std::string* fileName) {
	if (textFile == nullptr) {
		return "";
	}
	

	int pos = storage->count(POS_KEY) == 0 ? 0 : std::stoi(storage->at(POS_KEY));
	int subPos = storage->count(SUBPOS_KEY) == 0 ? 0 : std::stoi(storage->at(SUBPOS_KEY));

	std::regex regex = getRegex(fileName, subject);
	std::smatch match;
	std::string::const_iterator iterator = textFile->cbegin() + pos + subPos;
	for (int i = 0; i < timesToMoveCursor; i++)
	{
		if (std::regex_search(iterator, textFile->cend(), match, regex)) {

			iterator = match.suffix().first;
			subPos = match.position() + match.length() + subPos;
		}
	}

	std::string result = "";

	if (std::regex_search(iterator, textFile->cend(), match, regex)) {
		// MAtch position is relative to the start of the iterator (pos)
		subPos = match.position() + subPos;
		// TODO: Get all matches, not just first using match length
		result = match.str(1);
	}

	// No entry is considered starting from 0, do not waste memory
	if (subPos != 0) {
		storage->operator[](SUBPOS_KEY) = std::to_string(subPos);
	}

	return result;
}

// Gets the current element.
std::vector<std::string> FileReader::getElement(std::string elemType)
{
	return getElementHelper(&elemType, 0, &storage, textFile, &currentFileName);
}

std::vector<std::string> FileReader::getElement(std::string elemType, int id)
{
	storage.erase(POS_KEY);
	return getElementHelper(&elemType, id, &storage, textFile, &currentFileName);
}

// Moves the cursor to the next element and gets it.
std::vector<std::string> FileReader::getNextElement(std::string elemType)
{
	storage.erase(SUBPOS_KEY);
	return getElementHelper(&elemType, 1, &storage, textFile, &currentFileName);
}

// Resets the element cursor to the beginning of the file.
void FileReader::resetElement(std::string elemType)
{
	storage.erase(POS_KEY);
	storage.erase(SUBPOS_KEY);
}

// Gets the current element-attribute.
std::string FileReader::getElementAttribute(std::string elemType, std::string attrib)
{
	getElementHelper(&elemType, 0, &storage, textFile, &currentFileName);
	return getAttributeHelper(&attrib, 0, &storage, textFile, &currentFileName);
}

// Moves the cursor to the next element-attribute and gets it..
std::string FileReader::getNextElementAttribute(std::string elemType, std::string attrib)
{
	getElementHelper(&elemType, 0, &storage, textFile, &currentFileName);
	return getAttributeHelper(&attrib, 1, &storage, textFile, &currentFileName);
}

std::string FileReader::getElementAttribute(std::string elemType, int id, std::string attrib)
{
	getElementHelper(&elemType, 0, &storage, textFile, &currentFileName);
	return getAttributeHelper(&attrib, id, &storage, textFile, &currentFileName);
}

std::string FileReader::getNextElementAttribute(std::string elemType, int id, std::string attrib)
{
	//Your code here
	// You also need to modify the return value
	return std::string();
}

// Resets the attribute cursor to the beginning of the current element.
void FileReader::resetElementAttribute(std::string elemType, std::string attrib)
{
	storage.erase(SUBPOS_KEY);
}

// Prints given lines to stdout
void FileReader::printDataToCMD(std::string* lines)
{
	std::cout << *lines << std::endl;
}

// Switches the currently open file to another currently open file. The new file *must* already be open. Returns true on success, false if file is not found.
bool FileReader::switchCurrentFile(std::string fileName) {
	if (storage.count(fileName) == 0) {
		return false;
	}

	currentFileName = fileName;
	int streamIndex = std::stoi(storage[fileName]);
	// TODO: Find some way to un-duplicate this
	storage["file"] = readFromIfstream(&streams[streamIndex]);
	textFile = &storage["file"];
	storage.erase(POS_KEY);
	storage.erase(SUBPOS_KEY);
	return true;
}

bool FileReader::overrideCurrentFile(std::string fileName, std::string* lines) {

	//Your code here
	// You also need to modify the return value
	return false;
}

// Closes a file. Returns true when file is successfully closed, false when no open file can be found.
bool FileReader::closeFile(std::string fileName) {

	if (storage.count(fileName) == 0) {
		return false;
	}

	if (streams.size() <= 1) {
		if (streams.size() == 1) {
			// TODO: Find some way to un-duplicate this
			storage.erase(fileName);
			storage.erase("0");
			storage.erase("file");
			streams.pop_back();
		}
		currentFileName = "";
		textFile = nullptr;
	}

	else {
		std::string stringIndex = storage[fileName];
		int streamIndex = std::stoi(stringIndex);
		int lastIndex = streams.size() - 1;
		std::string stringLastIndex = std::to_string(lastIndex);

		// If the file to close is not the last entry in the vector
		if (streamIndex != lastIndex) {
			// Overwrite the stream to remove with the current last stream
			streams[streamIndex] = std::move(streams[lastIndex]);

			// Update storage indexes
			std::string movedFilename = storage[stringLastIndex];
			storage[stringIndex] = movedFilename;
			storage[movedFilename] = stringIndex;
		}

		// TODO: Find some way to un-duplicate this
		storage.erase(fileName);
		storage.erase(stringLastIndex);
		storage.erase("file");
		streams.pop_back();

		currentFileName = storage["0"];
		// TODO: Find some way to un-duplicate this
		storage["file"] = readFromIfstream(&streams[0]);
		textFile = &storage["file"];
	}
	storage.erase(POS_KEY);
	storage.erase(SUBPOS_KEY);

	return true;
}

bool FileReader::closeCurrentFile() {
	return closeFile(currentFileName);
}
