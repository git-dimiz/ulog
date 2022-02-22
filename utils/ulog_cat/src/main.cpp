#include "nlohmann/json.hpp"
#include "CLI/CLI.hpp"
#include "ulog_decoder.hpp"

#include <cstdio>
#include <deque>
#include <algorithm>
#include <memory>
#include <string>

using json = nlohmann::json;

static void ulog_message_vfprintf(std::FILE* file, char const* fmt, std::vector<ulog_arg>& va_list)
{
    char const* start = NULL;
    char const* end = NULL;
    int i = 0;
    const std::vector<char> sym = {
        'd', 'i', 'u', '%',
        'o', 'x', 'X', 'f',
        'F', 'e', 'E', 'g',
        'G', 'c', 's', 'p',
    };

    while (*fmt)
    {
        if ('%' == *fmt)
        {
            start = fmt;

            for (char const* itr = fmt + 1; *itr && NULL == end; itr++)
            {
                for (size_t i = 0; i < sym.size() && NULL == end; i++)
                {
                    if (*itr == sym[i])
                    {
                        end = itr;
                    }
                }
            }

            if (NULL != start && NULL != end)
            {
                if ('%' == *start && '%' == *end)
                {
                    std::fputc('%', file);
                }
                else if(i < va_list.size())
                {
                    std::string sub_fmt(start, (end + 1) - start);
                    std::fprintf(file, sub_fmt.c_str(), va_list[i].value());
                    i++;
                }
                else
                {
                    std::string sub_fmt(start, (end + 1) - start);
                    std::fprintf(file, "%s", sub_fmt.c_str());
                }

                fmt += (end - start);
                start = NULL;
                end = NULL;
            }
            else
            {
                std::fputc(*fmt, file);
            }
        }
        else
        {
            std::fputc(*fmt, file);
        }

        fmt++;
    }
}

int main(int argc, char const *argv[])
{
    std::array<std::uint8_t, 1024> buffer;
    std::deque<std::uint8_t> raw_message_queue;
    ulog_decoder message_decoder;
    std::FILE* input_file = NULL;
    std::FILE* output_file = NULL;
    std::FILE* json_file = NULL;
    json message_map_json;
    std::unordered_map<int, std::string> message_map;
    int decoded = 1;
    int success = 0;

    CLI::App app{"ulog_cat"};

    std::string output_file_name;
    std::string input_file_name;
    std::string json_file_name;
    app.add_option("-j,--json", json_file_name, "JSON file with message mapping")->required()->check(CLI::ExistingFile);
    app.add_option("-i,--input-file", input_file_name, "file to process")->check(CLI::ExistingFile);
    app.add_option("-o,--output-file", output_file_name, "file to output after processing");

    CLI11_PARSE(app, argc, argv);

    if (0 < input_file_name.length())
    {
        input_file = std::fopen(input_file_name.c_str(), "rb");
        if (NULL == input_file)
        {
            std::fprintf(stderr, "could not open %s\n", input_file_name.c_str());
            success = -1;
        }
    }
    else
    {
        input_file = stdin;
    }

    if (0 == success && 0 < output_file_name.length())
    {
        output_file = std::fopen(output_file_name.c_str(), "w+");
        if (NULL == output_file)
        {
            std::fprintf(stderr, "could not open %s\n", output_file_name.c_str());
            success = -1;
        }
    }
    else
    {
        output_file = stdout;
    }

    if (0 == success && 0 < json_file_name.length())
    {
        json_file = std::fopen(json_file_name.c_str(), "r");
        if (NULL != json_file)
        {
            std::string json_str;
            std::fseek(json_file, 0, SEEK_END);
            json_str.resize(std::ftell(json_file));
            std::rewind(json_file);
            std::fread(&json_str[0], 1, json_str.size(), json_file);
            std::fclose(json_file);

            message_map_json = json::parse(json_str);

            try
            {
                for (size_t i = 0; i < message_map_json[".ulog_rodata"].size(); i++)
                {
                    message_map[message_map_json[".ulog_rodata"][i]["tag"]] = message_map_json[".ulog_rodata"][i]["text"];
                }
            }
            catch(const std::exception& e)
            {
                success = -1;
            }

            if (0 != success || 0 >= message_map.size())
            {
                std::fprintf(stderr, "invalid json\n");
                success = -1;
            }            
        }
        else
        {
            std::fprintf(stderr, "could not open %s\n", json_file_name.c_str());
            success = -1;
        }
    }

    if (0 == success)
    {
        do
        {   
            size_t read = std::fread(buffer.data(), 1, buffer.size(), input_file);
            if (read)
            {
                std::copy(std::begin(buffer), std::begin(buffer) + read, std::back_inserter(raw_message_queue));
            }

            while (0 < raw_message_queue.size() && 0 < decoded)
            {
                decoded = message_decoder.decode(raw_message_queue);

                if (0 < decoded)
                {
                    ulog_message& msg = message_decoder.message();
                    if (std::end(message_map) != message_map.find(msg.tag()))
                    {
                        ulog_message_vfprintf(output_file, message_map[msg.tag()].c_str(), msg.va_list());
                    }
                    raw_message_queue.erase(std::begin(raw_message_queue), 
                                            std::begin(raw_message_queue) + decoded);
                } else if (0 > decoded)
                {
                    raw_message_queue.erase(std::begin(raw_message_queue), 
                                            std::begin(raw_message_queue) + (decoded * -1));
                }
            }
        } while (std::ferror(input_file) && !std::feof(input_file));
    }

    if (NULL != input_file)
    {
        std::fclose(input_file);
    }
    if (NULL != output_file)
    {
        std::fclose(output_file);
    }

    return success;
}
