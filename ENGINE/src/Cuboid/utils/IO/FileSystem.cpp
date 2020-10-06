#include <Cuboid/utils/IO/FileSystem.h>

namespace Cuboid
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

} /* namespace Cuboid */
