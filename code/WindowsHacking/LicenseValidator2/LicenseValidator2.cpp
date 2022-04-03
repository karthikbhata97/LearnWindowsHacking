#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

const char* valid_license = "OTE2NjY5MDktRDcxOS00Nzc1LTk1NDUtRERCMENBMkNCMTM3";

std::string base64_encode(const std::string input) {
	DWORD required_size = 0;
	auto success = CryptBinaryToStringA((BYTE*)input.c_str(), (DWORD)input.length(), CRYPT_STRING_BASE64, NULL, &required_size);
	if (!success || required_size == 0) {
		return {};
	}

	std::vector<char> output(required_size);
	DWORD actual_size = required_size;
	success = CryptBinaryToStringA((BYTE*)input.c_str(), (DWORD)input.length(), CRYPT_STRING_BASE64, output.data(), &actual_size);
	if (!success) {
		return {};
	}

	return std::string{ output.begin(), output.end() - 3 };
}

bool validate(std::string license) {
	auto result = base64_encode(license);
	if (result == valid_license) {
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
