/* -----------------------------------------------------------------------------
 * 
 * Name:    commandline.h
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Syntax: None
 * 
 * Description: Stuff
 * 
 * Notes: None
 * 
 * -----------------------------------------------------------------------------
 */

/* Header guard */
#ifndef ARIA_COMMAND_LINE_H
#define ARIA_COMMAND_LINE_H

/* Includes */
#include "ariadef.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

ARIA_NAMESPACE

namespace commandline
{
    /* Argument type */
    enum argument_t
    {
        no_argument,
        required_argument,
        optional_argument,
        list_argument
    };

    /* Option information */
    typedef struct option option_t;

    struct option
    {
        std::string shortopt;
        std::string longopt;
        std::string name;
        argument_t  argument;
        std::string desc;

        bool operator== (const option_t& opt) {
            return ((opt.shortopt == this->shortopt)
                    && (opt.longopt == this->longopt)
                    && (opt.name == this->name)
                    && (opt.argument == this->argument));
        }
    };

    /* List of all possible options */
    typedef std::vector<option_t> optlist_t;

    /* List of all entered options and their values */
    typedef std::unordered_map<std::string, std::vector<std::string>> keyval_t;

    /* Command line interface */
    class interface
    {
    public:
        explicit interface(const optlist_t options);

        void usage(void);
        void parse(char** argv);
        void print(void);
        void set(std::string key, std::string value);
        std::string get(std::string opt);
        bool has(std::string opt);

    protected:
        char** parse_argument(const option_t* option, char** arg, bool& listflag);
        bool parse_list_argument(char** arg, std::string key, bool& listflag);
        const option_t* find_option(std::string opt);
        std::string extract(std::string opt, int field);
        std::string extract_option(std::string opt);
        std::string extract_value(std::string opt);
        std::string to_short_option(std::string opt);
        std::string to_long_option(std::string opt);
        bool is_option(std::string opt);
        bool is_option(const option_t* option, std::string opt);
        bool is_short_option(std::string opt);
        bool is_short_option(const option_t* option, std::string opt);
        bool is_long_option(std::string opt);
        bool is_long_option(const option_t* option, std::string opt);

        const optlist_t m_options;
        keyval_t m_table;
    };

}

ARIA_NAMESPACE_END

#endif /* ARIA_COMMAND_LINE_H */
