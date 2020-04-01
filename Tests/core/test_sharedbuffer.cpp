#include "../IPTestAdministrator.h"

#include <gtest/gtest.h>
#include <core/core.h>

namespace WPEFramework {
namespace Tests {

    void CleanUpBuffer(char bufferName[], int buffSize)
    {
       // TODO: shouldn't this be done producer-side?
       char systemCmd[1024];
       string command = "rm -f ";
       snprintf(systemCmd, command.size()+buffSize+1, "%s%s", command.c_str(),bufferName);
       system(systemCmd);
       string ext = ".admin";
       snprintf(systemCmd, command.size()+buffSize+ext.size()+1, "%s%s%s", command.c_str(),bufferName,ext.c_str());
       system(systemCmd);
    }

    TEST(Core_SharedBuffer, simpleSet)
    {
       IPTestAdministrator::OtherSideMain otherSide = [](IPTestAdministrator & testAdmin) {
           char bufferName[] = "testbuffer01";
           int buffSize = sizeof(bufferName)/sizeof(bufferName[0]);
           CleanUpBuffer(bufferName, buffSize);

           uint16_t administrationSize = 64;
           uint32_t bufferSize = 8 * 1024;
           uint32_t result;

           Core::SharedBuffer buff01(bufferName,
               Core::File::USER_READ    |
               Core::File::USER_WRITE   |
               Core::File::USER_EXECUTE |
               Core::File::GROUP_READ   |
               Core::File::GROUP_WRITE  |
               Core::File::OTHERS_READ  |
               Core::File::OTHERS_WRITE,
               bufferSize,
               administrationSize);
           result = buff01.RequestProduce(Core::infinite);
           EXPECT_EQ(result, Core::ERROR_NONE);

           testAdmin.Sync("setup producer");

           testAdmin.Sync("setup consumer");

           uint8_t * buffer = buff01.Buffer();
           EXPECT_EQ(buff01.Size(), bufferSize);

           buffer[0] = 42;
           buffer[1] = 43;
           buffer[2] = 44;

           result = buff01.Produced();
           EXPECT_EQ(result, Core::ERROR_NONE);

           testAdmin.Sync("consumer done");
       };

       // This side (tested) acts as client (consumer).
       IPTestAdministrator testAdmin(otherSide);
       {
           // In extra scope, to make sure "buff01" is destructed before producer.
           testAdmin.Sync("setup producer");

           char bufferName[] = "testbuffer01";
           uint32_t bufferSize = 8 * 1024;
           uint32_t result;
           Core::SharedBuffer buff01(bufferName);

           testAdmin.Sync("setup consumer");

           result = buff01.RequestConsume(Core::infinite);
           EXPECT_EQ(result, Core::ERROR_NONE);

           uint8_t * buffer = buff01.Buffer();
           EXPECT_EQ(buff01.Size(), bufferSize);

           EXPECT_EQ(buffer[0], 42);
           EXPECT_EQ(buffer[1], 43);
           EXPECT_EQ(buffer[2], 44);

           buff01.Consumed();
           EXPECT_EQ(result, Core::ERROR_NONE);
       }

       testAdmin.Sync("consumer done");

       Core::Singleton::Dispose();
    }
} // Tests
} // WPEFramework
