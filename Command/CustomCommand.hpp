#pragma once
#include "Commander.hpp"

extern void optional(command_t* self) {
    if (self->arg != NULL) {
        cout << "Optional: " << self->arg << endl;
    }
    else {
        cout << "Optional: enabled" << endl;
    }
}

class CustomCommand : public Command
{
public:
    CustomCommand(const char* name, const char* version, bool verboseEnabled = false) :
        Command(name, version),
        verboseEnabled(verboseEnabled),
        required(nullptr)
    {}


    static void setVerbose(command_t* command) 
    {
        static_cast<CustomCommand*>(Command::self(command))->verboseEnabled = true;
    }

    static void setRequired(command_t* command)
    {
        static_cast<CustomCommand*>(Command::self(command))->required = command->arg;
    }

    const char* getRequired() 
    {
        return required;
    }

    bool isVerbose() 
    {
        return verboseEnabled;
    }

private:
    bool verboseEnabled;
    const char* required;
};