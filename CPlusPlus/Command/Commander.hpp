#pragma once
#include <iostream>
#include <vector>
extern "C" 
{
    #include "CommanderCore.h"
}
using namespace std;

class Command
{
public:
    Command(const char* name, const char* version) 
    {
        command = new command_t();
        command_init(command, name, version);
        command->data = static_cast<void*>(this);
    }

    ~Command() 
    {
        command_free(command);
        delete command;
    }

    void help() const 
    {
        command_help(command);
    }

    void option(const char* shortOpt, const char* longOpt, const char* usage, command_callback_t cb) 
    {
        command_option(command, shortOpt, longOpt, usage, cb);
    }

    void parse(int argc, char* argv[]) 
    {
        command_parse(command, argc, argv);
    }

    std::vector<const char*> additionalArgs() const 
    {
        std::vector<const char*> args(command->argc);
        args.assign(command->argv, command->argv + command->argc);
        return args;
    }

    const char* setUsage(const char* usage) 
    {
        const char* previousUsage = command->usage;
        command->usage = usage;
        return previousUsage;
    }

    const char* getUsage() const 
    {
        return command->usage;
    }

protected:
    static Command* self(command_t* command) 
    {
        return static_cast<Command*>(command->data);
    }
    command_t* command;
};

