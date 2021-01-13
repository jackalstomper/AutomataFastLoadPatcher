#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main() {
    const std::vector<uint8_t> fastLoadCode = {
        0x41, 0x83, 0x09, 0x02,     // or dword ptr [r9],02; Sets the load to use the no text screen
        0x53,                       // push rbx; an instruction we overwrote to make the new jmp
        0x56,                       // push rsi; an instruction we overwrote to make the new jmp
        0xEB, 0x0B                  // jmp NieRAutomata.exe+51A734; Go back to original code
    };

    const std::vector<uint8_t> jumpCode = {
        0xEB, 0xED // jmp NieRAutomata.exe+51A721
    };

    cout << "This tool will modify NieRAutomata.exe for faster load screens.\n"
        << "It is recommended to backup your exe file before running this tool.\n"
        << "Do you want to continue? [y/N]" << endl;

    string input;
    cin >> input;
    if (input != "y") {
        cout << "Aborting." << endl;
        system("pause");
        return 0;
    }

    fstream file("NieRAutomata.exe", std::ios::binary | ios::in | ios::out);
    if (!file.is_open()) {
        cerr << "Failed to open NieRAutomata.exe" << std::endl;
        system("pause");
        return 1;
    }

    // Write new code
    file.seekp(0x519B21);
    file.write(reinterpret_cast<const char*>(fastLoadCode.data()), fastLoadCode.size());


    // Write jump to new code
    file.seekp(0x519B32);
    file.write(reinterpret_cast<const char*>(jumpCode.data()), jumpCode.size());

    cout << "Mod completed." << endl;
    system("pause");
	return 0;
}