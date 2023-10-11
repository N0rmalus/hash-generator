#include "libs.h"

string readBinaryFromFile(string& seed) { // Inputas skaitomas iš failo
    string binaryRepresentation;
    string file;
    char symbol;

    do {
        cout << "Failu sarasas: ";
        system("ls *.dat *.txt");
        cout << "Pasirinkite faila: ";
        getline(cin, file);

        ifstream read(file);
        if(!read.is_open()) {
            cout << "Klaida: tokio failo [" << file << "] nera." << endl;
        } else {
            while(read.get(symbol)) {
                // Simbolis konvertuojamas į dvejetainį
                bitset<8> binary(symbol);
                binaryRepresentation += binary.to_string();
            }
            read.close();
            seed = binaryRepresentation;

            break;
        }
    } while(true);

    return binaryRepresentation;
}

string convertTextToBinary(string& seed) { // Inputas įvedamas ranka
    string binaryRepresentation;
    string textInput;

    cout << "Iveskite norima teksta: ";
    getline(cin, textInput);
    seed = textInput;

    for(char c : seed) {
        // Simbolis konvertuojamas į dvejetainį
        bitset<8> binary(c);
        binaryRepresentation += binary.to_string();
    }

    return binaryRepresentation;
}

string padBinaryRepresentationShort(string binaryRepresentation, int targetLength) {
    while(binaryRepresentation.length() < targetLength) {
        // Pridėti randominius simbolius
        char padChar = 'a' + (binaryRepresentation.length() % targetLength);
        binaryRepresentation += bitset<8>(padChar).to_string();
    }
    return binaryRepresentation;
}
string padBinaryRepresentationLong(string binaryRepresentation, int targetLength) {
    for(int i = 0; i < targetLength / 8; i++) {
        // Pridėti randominius simbolius
        char padChar = 'a' + (binaryRepresentation.length() % targetLength);
        binaryRepresentation += bitset<8>(padChar).to_string();
    }
    return binaryRepresentation;
}

string generateHexadecimalRepresentation(string binaryRepresentation, const string& seed) {
    // Dabartinio laiko ir inputo kombinacija kaip sydas mt19937 generatoriui
    random_device rd;
    mt19937 mt(rd());
    for(char c : seed)
        mt.seed(mt() ^ static_cast<unsigned int>(c));

    // Indeksų kiekis nustatomas pagal dvejetainio kodo ilgį
    int indexAmount = binaryRepresentation.length() / 8;
    vector<int> indexes(indexAmount);
    for(int i = 0; i < indexAmount; i++) {
        indexes[i] = i;
    }

    // Indeksai maišomi pagal mt19937 atsitiktinių skaičių generatorių
    shuffle(indexes.begin(), indexes.end(), mt);

    // Dvejetainiai konteineriai pertvarkomi pagal išmaišytus indeksus
    vector<bitset<8>> rearrangedBinaryArray(indexAmount);
    for(int i = 0; i < indexAmount; i++) {
        rearrangedBinaryArray[indexes[i]] = bitset<8>(binaryRepresentation.substr(i * 8, 8));
    }

    // Pertvarkytas dvejetainis kodas konvertuoajamas į hex
    stringstream hexStream;
    for(const auto &binaryByte : rearrangedBinaryArray) {
        hexStream << setw(2) << setfill('0') << hex << static_cast<int>(binaryByte.to_ulong());
    }

    // Hex kodas nukerpamas iki 64 simbolių
    return hexStream.str().substr(0, 64);
}

void processBinaryInput(bool fromFile) {
    std::chrono::high_resolution_clock::time_point sHashing, eHashing;
    std::chrono::duration<double> tHashing;

    string binaryRepresentation;
    string seed;

    if(fromFile) { // Skaitoma iš failo
        binaryRepresentation = readBinaryFromFile(seed);
    } else { // Įvedimas ranka
        binaryRepresentation = convertTextToBinary(seed);
    }

    sHashing = std::chrono::high_resolution_clock::now();
    if(binaryRepresentation.length() < 256) { // Dvejetainis kodas trumpesnis, nei 256 simboliai
        binaryRepresentation += "1"; // Pridedamas vienetas į galą
        binaryRepresentation = padBinaryRepresentationShort(binaryRepresentation, 256);
    } else { // Dvejetainis kodas ilgesnis, nei 256 simboliai
        binaryRepresentation = padBinaryRepresentationLong(binaryRepresentation, 512);
    }
    eHashing = std::chrono::high_resolution_clock::now();
    tHashing = eHashing - sHashing;

    string hexadecimalRepresentation = generateHexadecimalRepresentation(binaryRepresentation, seed);

    cout << endl << "Isvestis: " << hexadecimalRepresentation << endl;
    // cout << "Laikas: " << tHashing.count() << "s." << endl;
}
void differenceCalcByte(string firstInput, string secondInput, double& minDiff, double& maxDiff) {
    int identicalCharacters = 0;
    for (size_t i = 0; i < firstInput.length(); i++)
        if (firstInput[i] == secondInput[i])
            identicalCharacters++;

    if(identicalCharacters > maxDiff)
        maxDiff = identicalCharacters;
    if(identicalCharacters < minDiff)
        minDiff = identicalCharacters;
} void differenceCalcHex(string firstInput, string secondInput, double& minDiff, double& maxDiff) {
    int identicalCharacters = 0;
    for (size_t i = 0; i < firstInput.length(); i++)
        if (firstInput[i] == secondInput[i])
            identicalCharacters++;

    if(identicalCharacters > maxDiff)
        maxDiff = identicalCharacters;
    if(identicalCharacters < minDiff)
        minDiff = identicalCharacters;
}
void readAndConvertBinaryFromFile() {
    string file;
    string firstInput, secondInput;
    string firstInputBinary, secondInputBinary;
    string seed, seed2;
    int differentPairs = 0, identicalCharacters = 0;
    double minDiffByte = 64, maxDiffByte = 0;
    double minDiffHex = 64, maxDiffHex = 0;
    
    do {
        cout << "Failu sarasas: ";
        system("ls *.dat *.txt");
        cout << "Pasirinkite faila: ";
        getline(cin, file);

        ifstream read(file);
        if(!read.is_open()) {
            cout << "Klaida: tokio failo [" << file << "] nera." << endl;
        } else {
            cout << "-----------------------------------------------------------------------" << endl;
            while (getline(read, firstInput) && getline(read, secondInput)) {
                // Pirmoji įvestis konvertuojama į dvejetainę
                firstInputBinary = "";
                for (char c : firstInput) {
                    bitset<8> binary(c);
                    firstInputBinary += binary.to_string();
                }

                // Antroji įvestis konvertuojama į dvejetainę
                secondInputBinary = "";
                for (char c : secondInput) {
                    bitset<8> binary(c);
                    secondInputBinary += binary.to_string();
                }

                seed = firstInputBinary; // Sydas atsitikrinių skaičių generatoriui
                seed2 = secondInputBinary; // Antras sedas atsitikrinių skaičių generatoriui

                if(firstInputBinary.length() < 256) { // Dvejetainis kodas trumpesnis, nei 256 simboliai
                    // Pridedamas vienetas į galą
                    firstInputBinary += "1"; secondInputBinary += "1";
                    
                    firstInputBinary = padBinaryRepresentationShort(firstInputBinary, 256);
                    secondInputBinary = padBinaryRepresentationShort(secondInputBinary, 256);
                } else { // Dvejetainis kodas ilgesnis, nei 256 simboliai
                    firstInputBinary = padBinaryRepresentationLong(firstInputBinary, 512);
                    secondInputBinary = padBinaryRepresentationLong(secondInputBinary, 512);
                }
            
                string firstHexadecimalRepresentation = generateHexadecimalRepresentation(firstInputBinary, seed);
                string secondHexadecimalRepresentation = generateHexadecimalRepresentation(secondInputBinary, seed2);

                // Suskaičiuoti, kiek yra išvestų vienodų porų
                if (firstHexadecimalRepresentation == secondHexadecimalRepresentation)
                    differentPairs++;

                differenceCalcByte(firstInputBinary, secondInputBinary, minDiffByte, maxDiffByte);
                differenceCalcHex(firstHexadecimalRepresentation, secondHexadecimalRepresentation, minDiffHex, maxDiffHex);

                cout << firstHexadecimalRepresentation << " : " << secondHexadecimalRepresentation << endl;
            }
            read.close();
            cout << "-----------------------------------------------------------------------" << endl;
            cout << "Koliziju skaicius: " << differentPairs << endl;

            int columnWidth = 15;
            cout << left << setw(columnWidth) << "Min (HEX / BIT)" << right << setw(columnWidth) << minDiffHex / 64 * 100 << "% / ";
            cout << minDiffByte / firstInputBinary.length() * 100 << "%" << endl;

            cout << left << setw(columnWidth) << "Max (HEX / BIT)" << right << setw(columnWidth) << maxDiffHex / 64 * 100 << "% / ";
            cout << maxDiffByte / firstInputBinary.length() * 100 << "%" << endl;

            cout << left << setw(columnWidth) << "Avg (HEX / BIT)" << right << setw(columnWidth) << (minDiffHex / 64 * 100 + maxDiffHex / 64 * 100) / 2 << "% / ";
            cout << (minDiffByte / firstInputBinary.length() * 100 + maxDiffByte / firstInputBinary.length() * 100) / 2 << "%" << endl;

            break;
        }
    } while(true);
}