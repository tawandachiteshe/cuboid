#include <D3NGINE/utils/IO/FileSystem.h>

namespace D3G
{

	const std::string FileSystem::ReadFileAsText(const std::string& path)
	{
		std::ifstream inputStream(path);

		std::string line;
		std::stringstream src;
		while (std::getline(inputStream, line))
		{
			src << line << "\n";
		}
		return src.str();

	}

} /* namespace D3G */
