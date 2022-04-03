#include <iostream>
#include <string>

const char* valid_license = "D4712E03-1B23-4DCF-AB99-8B68A49AF3DC";

bool validate(std::string license) {
    if (license == valid_license) {
        std::cout << "Validated successfully" << std::endl;
        return true;
    }
	std::cout << "Failed to validate license key" << std::endl;
    return false;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <license-key>" << std::endl;
        return 1;
    }
    std::cout << "Validating license key" << std::endl;

    return validate(argv[1]);
}
