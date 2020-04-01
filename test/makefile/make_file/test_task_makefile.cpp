//
// Created by james on 2019-01-10.
//
//
// SampleServer.cpp
//
// This sample demonstrates the ServerApplication class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Task.h"
#include "Poco/TaskManager.h"
#include "Poco/DateTimeFormatter.h"
#include "make_bill_task.h"
#include <iostream>
#include "../log/log.h"

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Task;
using Poco::TaskManager;
using Poco::DateTimeFormatter;






class SampleServer : public ServerApplication {
public:
	SampleServer() : _helpRequested(false) {
	}

	~SampleServer() {
	}

protected:
	void initialize(Application &self) {
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
		logger().information("starting up");

		logger::initLogger(config().getString("application.baseName"), "");

		FLOG << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << ENDL;
		FLOG << config().getString( "application.baseName" ) << " started!"
			 << ENDL;
		std::string str;
		for ( const auto &a : this->argv() ) {
			str += a + ' ';
		}
		FLOG << "argv: " << str << ENDL;
		FLOG << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << ENDL;

	}


	void uninitialize() {
		logger().information("shutting down");
		ServerApplication::uninitialize();

		FLOG << config().getString( "application.baseName" ) << " stopped!"
			 << ENDL;
		logger::closeLogger();
	}

	void defineOptions(OptionSet &options) {
		ServerApplication::defineOptions(options);

		options.addOption(
				Option("help", "d", "display help information on command line arguments")
						.required(false)
						.repeatable(false)
						.callback(OptionCallback<SampleServer>(this, &SampleServer::handleHelp)));
		options.addOption(
				Option("ini", "f", "add file")
						.required(false)
						.argument("name=value")
						.repeatable(true)
						.callback(OptionCallback<SampleServer>(this, &SampleServer::loadfile)));
		options.addOption(
				Option("hello", "h", "show hello")
						.required(false)
						.argument("config")
						.repeatable(true)
						.callback(OptionCallback<SampleServer>(this, &SampleServer::handleHello)));
	}

	void handleHelp(const std::string &name, const std::string &value) {
		_helpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}

	void handleHello(const std::string &name, const std::string &value) {
		_helloRequested = true;
		sayHello();
		stopOptionsProcessing();
	}

	void displayHelp() {
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader(
				"A sample server application that demonstrates some of the features of the Util::ServerApplication class.");
		helpFormatter.format(std::cout);
	}

	void loadfile(const std::string &name, const std::string &value)
	{
		loadConfiguration( value );
	}

	void sayHello() {
		std::cout << "hello" << std::endl;
	}

	int main(const ArgVec &args) {
		if (!_helpRequested && !_helloRequested) {
			TaskManager tm;
			Poco::Util::AbstractConfiguration &config(Poco::Util::Application::instance().config());
			int num_visit_pro = config.getInt("file_setting.chose_how_many_visit_pro");

			for (int i = 0; i < num_visit_pro; ++i) {
				tm.start(new SampleTask);
			}
	//		waitForTerminationRequest();
			tm.cancelAll();
			tm.joinAll();
		}
		return Application::EXIT_OK;
	}

private:
	bool _helpRequested;
	bool _helloRequested;
};

int main(int argc, char **argv) {
	try {
		SampleServer app;
		return app.run(argc, argv);
	}
	catch (Poco::Exception &exc) {
		std::cerr << exc.displayText() << std::endl;
		return Poco::Util::Application::EXIT_SOFTWARE;
	}

}


//POCO_SERVER_MAIN(SampleServer)
