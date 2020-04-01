
#include <string>
#include <vector>

#include "common/BolApplication.h"
#include "common/BolMqSubsystem.hpp"
#include "IndbToHive.h"


#ifdef WITH_BOL
class IndbToHiveApp : public BolApplication
#else
class IndbToHiveApp: public BaseApplication
#endif
{
public:
    IndbToHiveApp() {
        // 添加队列子模块
        addSubsystem( new BolMqSubsystem );
    }

    virtual std::string helpFooter() 
    {
        return "帮助信息";
    }

    virtual std::string getVersion() 
    {
        return "版本号";
    }



    virtual int process() {
        try 
        {
						taskManager().start( new IndbToHiveTask );
        } 
        catch ( Poco::Exception & e ) 
        {
            FLOG << "exception: " << e.displayText() << ENDL;
            terminate();
        }

        waitForTerminationRequest();
        taskManager().cancelAll();
        taskManager().joinAll();
        return EXIT_OK;
    }
};

POCO_SERVER_MAIN(IndbToHiveApp);
