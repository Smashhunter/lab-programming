#include <algorithm>
#include <boost/crc.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/system/detail/error_category.hpp>
#include <boost/throw_exception.hpp>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <stack>
#include <type_traits>

namespace fs = boost::filesystem;
namespace sys = boost::system;
namespace po = boost::program_options;

class Bayan
{
private:
    std::vector<fs::path> paths_; // Paths where to seek duplicies
    std::set<fs::path> excludes_; // Paths what needs to exclude from seeking
    bool scanningLevel_;
    size_t fileMinSize_;
    std::vector<boost::regex> masks_;
    const size_t blockSize_; // Block size for caching process
    std::vector<fs::path> files_; //Pool for unqie files
    std::vector<std::pair<std::string, std::string>> duplicates_;

public:
    Bayan(std::vector<fs::path>& paths,
        std::set<fs::path>& excludes,
        std::vector<boost::regex>& masks,
        size_t fileMinSize = 1,
        size_t blockSize = 1024,
        bool scanningLevel = 0)
    : paths_(paths)
    , excludes_(excludes)
    , scanningLevel_(scanningLevel)
    , fileMinSize_(fileMinSize)
    , masks_(masks)
    , blockSize_(blockSize)
    {}

    void process()
    {
        auto scan = [this](auto begin, auto end) {
            boost::smatch what;
            for (auto dir = begin; dir != end; ++dir) {
                if (!dir->is_regular_file())
                    continue;
                

                for (auto mask : masks_) {
                    if (!boost::regex_match(dir->path().string(), what, mask) ||
                        fs::file_size(*dir) < fileMinSize_)
                        continue;
                    

                    files_.push_back(dir->path().string());

                    for (size_t i = 0; i < files_.size()-1; ++i) {
                        if (hash(files_[i], dir->path())){
                            duplicates_.push_back({files_[i].string(), dir->path().string()});
                            break;
                        }
                    }
                }
            }
        };

        for (auto directory : paths_) {
            if(scanningLevel_){
                fs::recursive_directory_iterator dir(directory), end;
                scan(dir, end);
                continue;
            }
            fs::directory_iterator dir(directory), end;
            scan(dir, end);
        }

   
    }

    std::string result()
    {
        if (duplicates_.empty())
            return "There's nothing duplicates!\n";
        
        std::vector<std::set<std::string>> sets = findDuplicateGroups(duplicates_);
        std::string answer = "Duplicates:\n";

        for (auto& set : sets) 
        {
            for (const fs::path& p : set) {
                answer += p.string() + '\n';
            }
            answer += "\n";
        }
        return answer;
    
    }

private:
    std::uint32_t crc32(const std::string& s, size_t len)
    {
        boost::crc_32_type result;
        result.process_bytes(s.data(), len);
        return result.checksum();
    }

    bool hash(const fs::path& a, const fs::path& b)
    {
        if (fs::file_size(a) != fs::file_size(b))
        return false;

        std::ifstream first(a.string(), std::ios::binary);
        std::ifstream second(b.string(), std::ios::binary);


        std::vector<char> fBuffer(blockSize_);
        std::vector<char> sBuffer(blockSize_);

        while (first && second) {
        first.read(fBuffer.data(), blockSize_);
        second.read(sBuffer.data(), blockSize_);

        std::streamsize fSize = first.gcount(); // Amount of characters was readed actually
        std::streamsize sSize = second.gcount();

        if (fSize != sSize)
            return false;
        
        if (crc32(fBuffer.data(), fSize) != crc32(sBuffer.data(), sSize))
            return false;
        }
        return true;
    }

    std::vector<std::set<std::string>> findDuplicateGroups(const std::vector<std::pair<std::string, std::string>>& pairs) {
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, int> rank;
    
    // Функция поиска с path compression
    std::function<std::string(const std::string&)> find = [&](const std::string& x) -> std::string {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    // Объединение
    auto unite = [&](const std::string& a, const std::string& b) {
        std::string ra = find(a);
        std::string rb = find(b);
        
        if (ra != rb) {
            if (rank[ra] < rank[rb]) {
                parent[ra] = rb;
            } else if (rank[ra] > rank[rb]) {
                parent[rb] = ra;
            } else {
                parent[rb] = ra;
                rank[ra]++;
            }
        }
    };
    
    // Объединяем все пары
    for (const auto& [a, b] : pairs) {
        unite(a, b);
    }
    
    // Группируем результаты
    std::unordered_map<std::string, std::set<std::string>> groups;
    for (const auto& [file, _] : parent) {
        std::string root = find(file);
        groups[root].insert(file);
    }
    
    // Преобразуем в вектор
    std::vector<std::set<std::string>> result;
    for (auto& [_, group] : groups) {
        result.push_back(move(group));
    }
    
    return result;
}

};

std::string
wildcard_to_regex(const std::string& pattern)
{
    std::string rx;
    rx.reserve(pattern.size() * 2);
    rx += "^"; // Symbol for starting line

    for (char c : pattern) {
        switch (c) {
            case '*':
                rx += ".*";
                break;
            case '?':
                rx += ".";
                break;
            case '.':
                rx += "\\.";
                break;
            case '\\':
                rx += "\\\\";
                break;
            default:
                if (std::isalnum(c))
                rx += c;
                else {
                rx += "\\";
                rx += c;
                }
        }
    } 

    rx += "$"; //Symbol for end of line
    return rx;
}

int main(int argc, char* argv[]) {
    try
    {
        // Init program options
        po::options_description desc("Programm for searching duplicates");
        desc.add_options()
            ("help,h", "Show help")
            ("directories,d", po::value<std::vector<std::string>>()->multitoken(), "Directories for scan")
            ("excludes,e", po::value<std::vector<std::string>>()->multitoken(), "Directories for excluding from scanning")
            ("level,l", po::value<bool>()->default_value(0), "Level of scanning. 1 - scan all directories, 0 - scan without nested dirs")
            ("min-size,s", po::value<size_t>()->default_value(1), "Minimum size (Bytes) of file for scanning")
            ("masks,m", po::value<std::vector<std::string>>()->multitoken(), "Masks for file")
            ("block-size,b", po::value<boost::uintmax_t>()->default_value(1024), "Size of block for reading file");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        // Tokens used in algorithm
        std::vector<fs::path> paths;
        std::set<fs::path> excludes;
        bool scanningLevel = vm["level"].as<bool>();
        size_t fileMinSize = vm["min-size"].as<size_t>();
        std::vector<boost::regex> masks;
        size_t blockSize = vm["block-size"].as<size_t>();

        // Process options
        if (vm.count("help") || vm.count("h")) {
            std::cout << desc;
            return 0;
        }
        if (!vm["directories"].empty()) {
            std::vector<std::string> rawPaths = vm["directories"].as<std::vector<std::string>>();
            paths.reserve(rawPaths.size());
            for (size_t i = 0; i < rawPaths.size(); ++i)
                paths.push_back(fs::absolute(rawPaths[i]));
        } else {
            paths = { fs::absolute("") };
        }
        if (!vm["excludes"].empty()) {
            std::vector<std::string> rawExcludes = vm["excludes"].as<std::vector<std::string>>();
            for (size_t i = 0; i < rawExcludes.size(); ++i)
                excludes.insert(fs::absolute(rawExcludes[i]));
        }
        if (!vm["masks"].empty()) {
            std::vector<std::string> rawMasks = vm["masks"].as<std::vector<std::string>>();
            masks.reserve(rawMasks.size());
            for (const std::string& mask : rawMasks)
                masks.push_back(boost::regex(wildcard_to_regex(mask), boost::regex::icase));
        } else {
            masks = { boost::regex("^.*$") }; // All possible file names
        }

        Bayan b(paths, excludes, masks, fileMinSize, blockSize, scanningLevel);
        b.process();
        std::cout << b.result();

    } catch (const boost::wrapexcept<po::unknown_option>& e) 
    {
        std::cout << "Unrecognized option. Try «bayan --help» or «bayan -h»";
        return 1;
    } catch (const boost::wrapexcept<po::invalid_command_line_syntax>& e) 
    {
        std::cout << "Arguments not provided for " << e.get_option_name();
        return 1;
    }

    return 0;
}
