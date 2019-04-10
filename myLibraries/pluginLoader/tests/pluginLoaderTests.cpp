/*!
 * @brief unit tests for pluginLoader.cpp
 *
 * @author harry marcks
 *
 * @date 09/04/2019
 *
 * @addtogroup pluginLoader
 * @{
 * @addtogroup tests
 * @{
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <pluginLoader/pluginLoader.h>
#include <logger/LogHandler.h>

class pluginLoaderFixture
    : public ::testing::Test
{
protected:
    pluginLoader::PluginLoader* PL;
    void SetUp() final
    {
        auto foo = logger::LogHandler::GetInstance(1
                                               , ".").OpenNewLog("TEST"
                                                                 , logger::StrategyEnums::STDOUT);

        PL = new pluginLoader::PluginLoader(foo);
    }
    void TearDown() final
    {
        logger::LogHandler::GetInstance(1
                                               , ".").CloseAllLogs();
        delete PL;
    }
};

TEST_F(pluginLoaderFixture
       , Constructor)
{
    ASSERT_TRUE(true);
}

TEST_F(pluginLoaderFixture
       , scanForPlugins)
{
    PL->ScanForComms(".");
}

/*! @} @} */