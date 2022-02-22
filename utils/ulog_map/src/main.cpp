#include "elfio/elfio.hpp"
#include "nlohmann/json.hpp"
#include "CLI/CLI.hpp"
#include <cstdio>
#include <string>
#include "ulog/ulog_hash.h"

using namespace ELFIO;
using json = nlohmann::json;

int main(int argc, char const *argv[])
{
    elfio elf_file;
    json json_file;
    json::array_t rodata_strings;
    std::FILE* output_file = NULL;
    int success = 0;

    CLI::App app{"ulog_map"};

    std::string output_file_name;
    std::string elf_file_name;
    app.add_option("-e,--elf-file", elf_file_name, "elf file to process")->required()->check(CLI::ExistingFile);
    app.add_option("-o,--output-file", output_file_name, "file to output after processing");

    CLI11_PARSE(app, argc, argv);

    if (0 < output_file_name.length())
    {
        output_file = std::fopen(output_file_name.c_str(), "w+");
        if (NULL == output_file)
        {
            success = -1;
            std::fprintf(stderr, "cannot open file %s\n", output_file_name.c_str());
        }
    }
    else
    {
        output_file = stdout;
    }

    if (0 == success && true == elf_file.load(elf_file_name))
    {
        for(section* sec : elf_file.sections)
        {
            if (0 == sec->get_name().compare(".ulog_rodata"))
            {
                char const* section_data = sec->get_data();
                Elf_Xword section_size = sec->get_size();
                size_t start = 0;
                size_t end = 0;
                for (Elf_Xword i = 0; i < section_size; i++)
                {
                    if (0 != section_data[i] && 0 == start)
                    {
                        start = i + 1;
                        end = 0;
                    }
                    else if (0 == section_data[i] && 0 == end)
                    {
                        end = i;
                    }
                    
                    if (0 != start && 0 != end)
                    {
                        std::string msg {section_data + start - 1, end - start + 1};
                        auto tag = ulog_hash(msg.c_str(), msg.length());
                        rodata_strings.push_back({
                            {"tag", tag},
                            {"text", msg}
                        });
                        start = 0;
                    }
                }
                break;
            }
        }

        json_file[".ulog_rodata"] = rodata_strings;

        std::fprintf(output_file, "%s\n", json_file.dump(4).c_str());
    }
    else
    {
        std::fprintf(stderr, "invalid elf file %s\n", elf_file_name.c_str());
        success = -1;
    }

    if (NULL != output_file)
    {
        std::fclose(output_file);
    }
        
    return success;
}
