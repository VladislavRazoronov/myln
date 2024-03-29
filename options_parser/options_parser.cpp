// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "options_parser.h"

namespace po = boost::program_options;

command_line_options_t::command_line_options_t() {
    opt_conf.add_options()
        ("help,h",
                "Show help message")
        ("symlink,soft",
                "Create a symbolic link to given destination "
                "i.e the link doesn't require destination to exist")
        ("hardlink,hard",
                "Create hard link to given destination ensuring that it exists")
        ;
}

command_line_options_t::command_line_options_t(int ac, char **av):
        command_line_options_t() // Delegate constructor
{
    parse(ac, av);
}

void command_line_options_t::parse(int ac, char **av) {
    try {
        po::parsed_options parsed = po::command_line_parser(ac, av).options(opt_conf).allow_unregistered().run();
        po::store(parsed, var_map);
        filenames = po::collect_unrecognized(parsed.options, po::include_positional);
        if (var_map.count("help")) {
            std::cout << opt_conf << "\n";
            exit(EXIT_SUCCESS);
        }
        S_link = var_map.count("symlink");
        H_link = var_map.count("hardlink");
        po::notify(var_map);
    } catch (std::exception &ex) {
        throw OptionsParseException(ex.what()); // Convert to our error type
    }
}