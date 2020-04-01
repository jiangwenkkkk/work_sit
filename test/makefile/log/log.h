//
// Created by james on 2019-01-19.
//

#ifndef FIND_USE_LOG_H
#define FIND_USE_LOG_H
/*
 * =====================================================================================
 *
 *       Filename:  Logger.h
 *
 *    Description:  日志工具类
 *                  注意: Application::instance 不能为空, 必须是从Poco::Application
 *                  派生的应用才能调用该日志方法
 *
 *        Version:  1.0
 *        Created:  10/30/2017 04:46:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhongjie (), zhongjie@asiainfo.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <iostream>

#include "Poco/Format.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Channel.h"
#include "Poco/AsyncChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/LogStream.h"
#include "Poco/Util/Application.h"
#include "Poco/Path.h"
#include "Poco/File.h"


namespace logger
{

	const char* const LOGGER_PATH = "logger.path";
	const char* const LOGGER_FORMAT = "logger.format";
	const char* const LOGGER_LEVEL = "logger.level";
// 根据时间或者日志大小创建新的日志文件
	const char* const LOGGER_ROTATION = "logger.rotation";
// 归档文件命名格式
	const char* const LOGGER_ARCHIVE = "logger.archive";
// 最多文件数
	const char* const LOGGER_COUNT = "logger.count";


	inline void initLogger( const std::string& appName, const std::string& suffix )
	{
		auto &app = Poco::Util::Application::instance();
		const auto &config = app.config();

		Poco::Channel* pOutChnnel = nullptr;

		if ( config.hasOption( LOGGER_PATH ) ) {
			// 获取文件路径
			auto logPath = Poco::Path( config.getString( LOGGER_PATH ) );
			logPath.makeAbsolute();

			Poco::File filePath( logPath );
			if ( !filePath.exists() ) {
				filePath.createDirectories();
			}

			pOutChnnel = new Poco::FileChannel(
					Poco::format( "%s/%s%s.log", logPath.toString(), appName,
								  suffix ) );
			pOutChnnel->setProperty( "rotation",
									 config.getString( LOGGER_ROTATION, "99M" ) );
			pOutChnnel->setProperty( "archive",
									 config.getString( LOGGER_ARCHIVE, "number" ) );
			pOutChnnel->setProperty( "times", "local" );
			pOutChnnel->setProperty( "purgeCount",
									 config.getString( LOGGER_COUNT, "99" ) );
		} else {
			pOutChnnel = new Poco::ColorConsoleChannel;
		}


		// 获取日志格式
		const auto &format = config.getString( LOGGER_FORMAT,
											   "%Y%m%d %H:%M:%S.%c [%q] [%P] %t" );
		auto pFormat = new Poco::PatternFormatter( format );
		pFormat->setProperty( "times", "local" );
		auto pFormatChannel = new Poco::FormattingChannel( pFormat, pOutChnnel );

		// 打开写日志线程
		auto pAsyncChannel = new Poco::AsyncChannel( pFormatChannel );
		pAsyncChannel->open();

		Poco::Logger::root().setChannel( pAsyncChannel );

		// 设置日志等级
		const auto& logLevel = config.getString( LOGGER_LEVEL, "debug" );
		Poco::Logger::root().setLevel( logLevel );
	}

	inline void closeLogger()
	{
		auto *pAsyncChannel = static_cast<Poco::AsyncChannel*>
		( Poco::Logger::root().getChannel() );
		pAsyncChannel->close();
		auto *pFormatChannel = pAsyncChannel->getChannel();
		if ( pFormatChannel ) {
			pFormatChannel->close();
		}
		Poco::Logger::root().close();
	}

	namespace
	{
#define __LOG(level) \
    Poco::LogStream(Poco::Logger::root(), level) \
    << "[" << Poco::Path(__FILE__).getFileName() << ":" << __LINE__ << "::" << __func__ << "] "
	}

#define TLOG __LOG(Poco::Message::PRIO_TRACE)
#define DLOG __LOG(Poco::Message::PRIO_DEBUG)
#define ILOG __LOG(Poco::Message::PRIO_INFORMATION)
#define NLOG __LOG(Poco::Message::PRIO_NOTICE)
#define WLOG __LOG(Poco::Message::PRIO_WARNING)
#define ELOG __LOG(Poco::Message::PRIO_ERROR)
#define CLOG __LOG(Poco::Message::PRIO_CRITICAL)
#define FLOG __LOG(Poco::Message::PRIO_FATAL)

#define ENDL std::endl;
}
#endif

#endif //FIND_USE_LOG_H
