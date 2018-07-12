#include "Editor.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <cstdlib>

#include "utils.h"
#include "Commands/Command.h"
#include "Commands/HelpCommand.h"
#include "Commands/QuitCommand.h"
#include "Commands/EdgeAddCommand.h"
#include "Commands/EdgeRemoveCommand.h"
/*#include "Commands/GraphCloseCommand.h"
#include "Commands/GraphDeleteCommand.h"
#include "Commands/GraphDisplayCommand.h"
#include "Commands/GraphListCommand.h"
#include "Commands/GraphNewCommand.h"
#include "Commands/GraphOpenCommand.h"*/
#include "Commands/VertexAddCommand.h"
#include "Commands/VertexEditCommand.h"
//#include "Commands/VertexInfoCommand.h"
#include "Commands/VertexRemoveCommand.h"
#include "Commands/AttributeAdd.h"
#include "Commands/AttributeRemove.h"
#include "Commands/AttributeSet.h"

#include "collabdata/custom/SimpleGraph.h"
#include "SimpleGraphOperationObserver.h"

Editor::Editor()
{
    this->running = false;
    ///////////////////  Editor commands loading  ///////////////////
    Command *command_;
    command_ = new QuitCommand(this);
    this->commands[command_->getName()] = command_;
    command_ = new EdgeAddCommand();
    this->commands[command_->getName()] = command_;
    command_ = new HelpCommand(&(this->commands));
    this->commands[command_->getName()] = command_;
    command_ = new EdgeRemoveCommand();
    this->commands[command_->getName()] = command_;
    command_ = new AttributeAdd();
    this->commands[command_->getName()] = command_;
    command_ = new AttributeRemove();
    this->commands[command_->getName()] = command_;
    command_ = new AttributeSet();
    this->commands[command_->getName()] = command_; 
    command_ = new VertexAddCommand();
    this->commands[command_->getName()] = command_;
    command_ = new VertexRemoveCommand();
    this->commands[command_->getName()] = command_;    
    ///////////////////  Editor commands loading end ///////////////////
}

int Editor::startRunning()
{
    if (commands.empty())
    {
        std::cerr << "Error : No commands available in the editor." << std::endl;
        return -1;
    }

    this->running = true;
    collab::SimpleGraph dataStructure = collab::SimpleGraph();
    SimpleGraphOperationObserver opObserver = SimpleGraphOperationObserver();
    dataStructure.addOperationObserver(opObserver);

    std::cout << "***********************************************************************" << std::endl
              << "***********  Welcome in the collaborative CLI graph editor  ***********" << std::endl
              << "***********************************************************************"
              << std::endl;
    std::cout << std::endl
              << "Create and edit your graph by tipping the appropriate command" << std::endl;
    std::cout << "To display the help, type help" << std::endl;
    std::cout << "***********************************************************************"
              << std::endl
              << std::endl;

    std::string word;
    std::string arguments;
    std::vector<std::string> argumentsList;
    utils::config conf = utils::config();
    conf.setDataStructure(dataStructure);
    conf.flipLoaded();
    while (this->running)
    {
        std::cout << "=> ";
        std::cin >> word;
        argumentsList.clear();
        if (commands.count(word) == 1)
        {
            std::getline(std::cin, arguments);
            argumentsList = utils::split_no_quotes(arguments.begin(), arguments.end());
            commands[word]->exec(conf, argumentsList);
        }
        else
        {
            std::getline(std::cin, arguments);
            std::cout << "Undefined command. To see all available commands, type \"help\"." << std::endl;
        }
    }

    return 0;
}

int Editor::stopRunning()
{
    this->running = false;
    return 0;
}


Editor::~Editor()
{
    for (auto const &command : this->commands)
    {
        free(command.second);
    }
}