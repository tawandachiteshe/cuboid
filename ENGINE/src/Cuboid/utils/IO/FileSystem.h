
#ifndef ENGINE_SRC_CUBOID_UTILS_IO_FILESYSTEM_H_
#define ENGINE_SRC_CUBOID_UTILS_IO_FILESYSTEM_H_

namespace Cuboid
{

	class FileSystem
	{
		public:
			static const std::string ReadFileAsText(const std::string& path);
			FileSystem();
			virtual ~FileSystem();
	};

}

#endif
