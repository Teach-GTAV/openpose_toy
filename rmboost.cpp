#include <iostream>
#include <fstream>
#include <algorithm>
#include <dirent.h>
#include <cstring>
#include <memory>
#include <unistd.h>

#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif


namespace op
{

    void mkdirectory (const std::string& directoryPath)
    {
        try
        {
            if (!directoryPath.empty())
            {
                #if defined _MSC_VER
                _mkdir(directoryPath.data());
                #elif defined __GNUC__
                mkdir(directoryPath.data(), S_IRUSR | S_IWUSR | S_IXUSR);
                #endif
            }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    bool isDirectory(const std::string& directoryPath)
    {
        try
        {
            DIR* dir = opendir(directoryPath.c_str());

            if (dir != NULL)
            {
                closedir(dir);
                return true;
            }
            else
            {
                return false;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return false;
        }
    }


    std::string formatAsDirectory(const std::string& directoryPathString)
    {
        try
        {
            std::string directoryPath = directoryPathString;
            if (!directoryPath.empty())
            {
                std::replace(directoryPath.begin(), directoryPath.end(), '\\', '/'); // replace all '\\' to '/';
                if (directoryPath.back() != '/')
                    directoryPath = directoryPath + "/";
            }
            return directoryPath;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return "";
        }
    }

    std::string getFileNameAndExtension(const std::string& fullpath)
    {
        try
        {
            size_t sep = fullpath.find_last_of("\\/");
            if (sep != std::string::npos)
                return fullpath.substr(sep+1, fullpath.size() - sep - 1);
            else
                return fullpath;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return "";
        }
    }

    std::string getFileNameNoExtension(const std::string& fullPath)
    {
        try
        {
            std::string nameExt = getFileNameAndExtension(fullPath);

            size_t dot = nameExt.find_last_of(".");
            if (dot != std::string::npos)
                return nameExt.substr(0, dot);
            else
                return nameExt;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return "";
        }
    }

    std::string getFileExtension(const std::string& fullPath)
    {
        try
        {
            std::string nameExt = getFileNameAndExtension(fullPath);

            size_t dot = nameExt.find_last_of(".");
            if (dot != std::string::npos)
                return nameExt.substr(dot+1, nameExt.size()-dot-1);
            else
                return "";
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return "";
        }
    }


    bool existDir(const std::string& directoryPath)
    {
        try
        {
            DIR* dir = opendir(directoryPath.c_str());

            if (dir != NULL)
            {
                closedir(dir);
                return true;
            }
            else
            {
                return false;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    bool existFile(const std::string& filePath)
    {
        try
        {
            if (auto* file = fopen(filePath.c_str(), "r"))
            {
                fclose(file);
                return true;
            }
            else
                return false;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return false;
        }
    }


    std::vector<std::string> getFilesOnDirectory(const std::string& directoryPath)
    {
        try
        {
            std::string format_path = formatAsDirectory(directoryPath);
            // Check folder exits
            if (!existDir(format_path))
                std::cout << "No such folder" << std::endl;

            // Read images
            std::vector<std::string> filePaths;
            std::shared_ptr<DIR> directory_ptr(opendir(format_path.c_str()), [](DIR* format_path){ format_path && closedir(format_path); });
            struct dirent *dirent_ptr;

            while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr)
            {
                std::string tmp_path = format_path + dirent_ptr->d_name;
                if ((strncmp(dirent_ptr->d_name, ".", 1) ==0)||(isDirectory(tmp_path) == 1))
                        continue;
                filePaths.push_back(tmp_path);
            }

            // Check #files > 0
            if (filePaths.empty())
                std::cout << "No such file" << std::endl;

            // Sort alphabetically
            std::sort(filePaths.begin(), filePaths.end());

            return filePaths;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return {};
        }
    }

}


int main(void)
{
    std::string path_windows1 = "c:/dir1/dir2/fileee.ext";
    std::string path_windows2 = "fileaasdext";
    std::string path_unix     = "/s/d/s/s/s/s/fissle.ext";

    std::string files_path1    = "/home/maxtom/code_test/openpose_toy/dir/";
    std::string files_path2    = "/home/maxtom/code_test/openpose_toy/dir";

    std::cout << "current path " << path_windows1 << std::endl;
    std::cout << op::getFileNameAndExtension(path_windows1) << std::endl;
    std::cout << op::getFileNameNoExtension(path_windows1) << std::endl;
    std::cout << op::getFileExtension(path_windows1) << std::endl;
    std::cout << "current path " << path_windows2 << std::endl;
    std::cout << op::getFileNameAndExtension(path_windows2) << std::endl;
    std::cout << op::getFileNameNoExtension(path_windows2) << std::endl;
    std::cout << op::getFileExtension(path_windows2) << std::endl;
    std::cout << "current path " << path_unix << std::endl;
    std::cout << op::getFileNameAndExtension(path_unix) << std::endl;
    std::cout << op::getFileNameNoExtension(path_unix) << std::endl;
    std::cout << op::getFileExtension(path_unix) << std::endl;

    std::cout << std::endl << files_path1 << std::endl;
    std::vector<std::string> files1 = op::getFilesOnDirectory(files_path1);
    for (int i=0; i < files1.size(); i++)
    {
        std::cout << files1[i] << std::endl;
    }

    std::cout << std::endl << files_path2 << std::endl;
    std::vector<std::string> files2 = op::getFilesOnDirectory(files_path2);
    for (int i=0; i < files2.size(); i++)
    {
        std::cout << files2[i]<< std::endl;
    }


    std::string tmp_dir    = "~/test/ok1/ok2";
    op::mkdirectory(tmp_dir);


    return 0;
}
