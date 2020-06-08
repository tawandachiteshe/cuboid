
#ifndef ENGINE_SRC_D3NGINE_UTILS_IO_FILESYSTEM_H_
#define ENGINE_SRC_D3NGINE_UTILS_IO_FILESYSTEM_H_

namespace D3G
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
