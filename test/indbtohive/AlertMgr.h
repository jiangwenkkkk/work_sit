/*
 * =====================================================================================
 *
 *       Filename:  AlertMgr.hpp
 *
 *    Description:  告警输出模块
 *
 *        Version:  1.0
 *        Created:  2018年07月31日 19时43分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhongjie (), zhongjie@asiainfo.com
 *   Organization:
 *
 * =====================================================================================
 */
#pragma once
#include <string>
#include <chrono>


#include "common/util.h"
#include "common/ApplicationConfig.h"
#include "common/BolMqSubsystem.hpp"
#include "proto/LogAlertMessage.pb.h"


class AlertMgr
{
public:
    AlertMgr()
        : _condition( util_func::appConfig().getString( "condition.alert" ) ) {
        using util_func::appConfig;
        const auto &modeCode = Poco::format( "%d-%d-%d",
                                             appConfig().getInt( app_conf::FLOW_ID ),
                                             appConfig().getInt( app_conf::PROGRAM_ID ),
                                             appConfig().getInt( app_conf::INSTANCE_ID ) );
        _alertpb.set_modecode( modeCode );
        _alertpb.set_bolname( appConfig().getString( app_conf::BOLNAME ) );
    }

    bool send( LogAlertpb::Alert::AlertType alertType,
               const std::string &alertText ) {
        using std::chrono::system_clock;
        auto nowt = system_clock::to_time_t( system_clock::now() );
        _alertpb.set_alerttype( alertType );
        _alertpb.set_alerttime( nowt );
        _alertpb.set_alerttext( alertText );

        std::string msg;
        if ( !_alertpb.SerializeToString( &msg ) ) {
            FLOG << "failed to serialize to string "
                 << _alertpb.DebugString() << ENDL;
            return false;
        }

        auto &app = Poco::Util::Application::instance();
        auto &mqSubsystem = app.getSubsystem<BolMqSubsystem>();
        if ( !mqSubsystem.send( _condition, msg ) ) {
            FLOG << "failed to produce msg to topic by condition "
                 << _condition << ENDL;
            return false;
        }

        return true;
    }

private:
    LogAlertpb::Alert _alertpb;
    const std::string _condition;
};
