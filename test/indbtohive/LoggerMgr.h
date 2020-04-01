/*
 * =====================================================================================
 *
 *       Filename:  LoggerMgr.hpp
 *
 *    Description:  云管控日志模块
 *
 *        Version:  1.0
 *        Created:  2018年07月30日 15时27分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhongjie (), zhongjie@asiainfo.com
 *   Organization:
 *
 * =====================================================================================
 */
#pragma once
#include <map>

#include "Poco/Exception.h"
#include "Poco/Util/Application.h"
#include "common/BolMqSubsystem.hpp"
#include "proto/LogAlertMessage.pb.h"

const int INDBTOHIVE=6;

class LoggerMgr
{
public:
    struct Offset {
        int64_t start;
        int64_t stop;
    };

    using OffsetMap = std::map<int, Offset>;

    LoggerMgr()
        : _condition( util_func::appConfig().getString( "condition.logger" ) )
        , _billCount( 0 ), _startTime( 0 ) {
    }

    bool send( LogAlertpb::Log::LogType logType,
               const std::string &outputFileName ) {
        using util_func::appConfig;
        const auto &modeCode = Poco::format( "%d-%d-%d",
                                             appConfig().getInt( app_conf::FLOW_ID ),
                                             appConfig().getInt( app_conf::PROGRAM_ID ),
                                             appConfig().getInt( app_conf::INSTANCE_ID ) );

        LogAlertpb::Log logpb;
        logpb.set_modecode( modeCode );
        logpb.set_bolname( appConfig().getString( app_conf::BOLNAME ) );

        using std::chrono::system_clock;
        auto nowt = system_clock::to_time_t( system_clock::now() );

        logpb.set_logtype( logType );
        // logpb.set_creattime( _createTime );
        logpb.set_outputfile( outputFileName );
        logpb.set_billcount( _billCount );
        logpb.set_appmode(LogAlertpb::Log::EXPORT);
        logpb.set_starttime(_startTime);
        logpb.set_stoptime(nowt);

        // 分区消费信息
        for ( const auto &pa : _offsetMap ) {
            auto *offset = logpb.add_partitionoffsets();
            offset->set_partition( pa.first );
            offset->set_offsetstart( pa.second.start );
            offset->set_offsetstop( pa.second.stop );
        }

        std::string msg;
        if ( !logpb.SerializeToString( &msg ) ) {
            FLOG << "failed serialize to string, "
                 << logpb.DebugString() << ENDL;
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

    void updateOffset( int partition, int64_t offset ) {
        ++ _billCount;

        if ( _offsetMap.count( partition ) ) {
            _offsetMap[partition].stop = offset;
        } else {
            _offsetMap[partition].start = offset;
        }
    }

    void reset() {
        _offsetMap.clear();
        _billCount = 0;
        _startTime = 0;
    }

    void startTime( time_t t ) {
        _startTime = t;
    }



private:
    const std::string       _condition;         // 生产的条件
    OffsetMap               _offsetMap;         // 分区便宜映射
    int                     _billCount;         // 计算话单数量
    time_t                  _startTime;         // 下发文件创建时间

};
