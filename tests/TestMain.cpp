#include <gtest/gtest.h>

#include "RealEngine.h"

using namespace RealEngine;

int main(int argc, char** argv) {
    Logger::Init();

	// Set both loggers to flush immediately for testing purposes
	Logger::GetCoreLogger()->set_immediate_flush(true);
	Logger::GetClientLogger()->set_immediate_flush(true);

    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}