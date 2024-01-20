#include "CustomCommand.hpp"

int main(int argc, char* argv[])
{
	CustomCommand command = CustomCommand("CustomCommand", "0.0.1");
	command.setUsage("[options] [ARG1 [ARG2 [ARG3]]");
	command.option("-v", "--verbose", "enable verbose stuff", CustomCommand::setVerbose);
	command.option("-r", "--required <arg>", "required arg", CustomCommand::setRequired);
	command.option("-o", "--optional [arg]", "optional arg", optional);
	command.parse(argc, argv);
	std::vector<const char*> args = command.additionalArgs();

	if (args.size() > 3)
	{
		cerr << "Too many command line arguments were specified" << endl;
		command.help();
	}
	else if (args.size())
	{
		cout << "Additional args:" << endl;
		for (vector<const char*>::iterator it = args.begin(); it != args.end(); ++it) {
			cout << "  - '" << *it << "'" << endl;
		}
	}
	else
	{
		cout << "No additional args" << endl;
	}

	if (command.getRequired() != nullptr)
	{
		cout << "Required is: " << command.getRequired() << endl;
	}
	cout << command.getUsage() << endl;
	cout << "Verbose status is " << ((command.isVerbose()) ? "enabled" : "disabled");
}
